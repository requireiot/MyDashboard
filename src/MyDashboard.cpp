/**
 * @file 		  MyDashboard.cpp
 *
 * Author		: Bernd Waldmann
 * Created		: 01-Mar-2022
 * Tabsize		: 4
 * 
 * This Revision: $Id: MyDashboard.cpp 1554 2023-10-29 13:34:03Z  $
 */

/*
   Copyright (C) 2022,2023 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public License, 
   v. 2.0. If a copy of the MPL was not distributed with this file, You can 
   obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

/**
 * @brief Dashboard e-Ink display for OpenHAB based home automation, using an ESP8266 module.
 * 
 */

/* Pinout
  D0 = GPIO16 connect to RST via 1N5817 diode, also 'USER' key on NodeMCU
  D1 = GPIO5  = BUSY  =           
  D2 = GPIO4  = Power to e-Ink display
  D3 = GPIO0  = DC    = 'FLASH' key, pull-up
  D4 = GPIO2  = CS    = Blue LED, pull-up,   
  D5 = GPIO14 = SCK               
  D6 = GPIO12 = MISO              
  D7 = GPIO13 = MOSI              
  D8 = GPIO15 = RESET via 2N7000 (inverted): S=GND, G=D8, D=RESET
  D9 = GPIO3  = Rx0
  D10= GPIO1  = Tx0
*/

//==============================================================================

//----- C standard headers
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>

//----- Arduino and libraries
#include <Arduino.h>            // LGPLv2.1+ license
#include <SPI.h>                // LGPLv2.1+ license
#include <ESP8266WiFi.h>        // LGPLv2.1+ license
#include <ESP8266HTTPClient.h>  // LGPLv2.1+ license
#include <user_interface.h>
#include <LittleFS.h>           // LGPLv2.1+ license
#include <WiFiUdp.h>            // LGPLv2.1+ license
#include <TimeLib.h>            // LGPLv2.1+ license
#include <ArduinoOTA.h>         // LGPLv2.1+ license, https://github.com/jandrassy/ArduinoOTA
#include <ArduinoJSON.h>        // MIT license, https://github.com/bblanchon/ArduinoJson
#include <NTPClient.h>          // MIT license, https://github.com/arduino-libraries/NTPClient
#include <Array.h>              // 3-clause BSD License, https://github.com/janelia-arduino/Array 
#include <RegExp.h>             // generous license, https://github.com/nickgammon/Regexp

#include <TFT_eSPI.h>
#include <epd2in9b.h>
#include "../fonts/DejaVuSans13pt7b.h"
#include "../fonts/DejaVuSansBold13pt7b.h"
#include "../fonts/DejaVuSans24pt7b.h"

//----- my headers
#include <ansi.h>
#include "MyWifi.h"
#include "ota.h"

ADC_MODE(ADC_VCC);

//==============================================================================
#pragma region Preferences

//----- OpenHAB REST API server
#define OPENHAB_SERVER "ha-server"
#define OPENHAB_PORT 8080

//----- some OH item names
#define OH_ITEM_OTA "EnableOTA"
#define OH_ITEM_VCC "Dashboard2_VCC"

//----- Timing definitions
#define SECONDS		* 1000uL
#define MINUTES 	* 60uL SECONDS
#define HOURS 		* 60uL MINUTES
#define DAYS		* 24uL HOURS

// minimum time between refreshes
const unsigned long REPORT_INTERVAL = 60 MINUTES;   // max is ca 70min, ESP8266 limit

#pragma endregion
//==============================================================================
#pragma region Global constants

//#define USE_NTP

#define POWER_PIN   D2  // this pin powers the e-Ink display module

// "colors" for e-Ink display
#define COLORED     0   // black or red
#define UNCOLORED   1   // white

//----- serial output
#define MY_BAUD_RATE 230400uL

 #define FONT_NORMAL DejaVuSans13pt7b
 #define FONT_BOLD   DejaVuSansBold13pt7b
 #define FONT_LARGE  DejaVu_Sans_Bold_24

// max # of dashboard fields
const int MAX_DASH_FIELDS = 50;

#pragma endregion
//==============================================================================
#pragma region Global variables

bool emergencyMode = false; // if true, then don't go to sleep, wait for OTA request
bool validLayoutFile = false;
bool validConfig = false;

char msgbuf[256];

WifiState wifiConfig;
WiFiUDP udpClient;
HTTPClient httpc;

#ifdef USE_NTP
 NTPClient ntpClient(udpClient);
#endif

 Epd ePaper;
 TFT_eSPI    glc = TFT_eSPI();               // Invoke the graphics library class
 TFT_eSprite blkFrame = TFT_eSprite(&glc);   // canvas for black content
 TFT_eSprite redFrame = TFT_eSprite(&glc);   // canvas for red content
 uint8_t* blkFramePtr = nullptr;                 
 uint8_t* redFramePtr = nullptr; 

//------------------------------------------------------------------------------
#pragma endregion
//==============================================================================
#pragma region Little helpers

/**
 * @brief Copy string with limited length, always terminate wih NUL
 * 
 * @param dst   the source string
 * @param src   the destination buffer
 * @param size  size of destination buffer
 */
static void _safe_copy( char* dst, const char* src, size_t size )
{ 
    if (src != NULL) {
        strncpy(dst,src,size); 
        dst[size-1] = '\0';
    } else {
        *dst = '\0'; 
    }
}
#define safe_copy(dst,src) _safe_copy(dst,src,sizeof(dst))

/* to profile certain code segments, insert STOPWATCH_BEGIN before segment,
   and STOPWATCH:END("comment") after segment.
   Will print duration in ms to Serial
*/
static uint32_t _t1, _t2;
#define STOPWATCH_BEGIN    _t1=millis();     
#define STOPWATCH_END(txt) _t2=millis(); \
                           Serial.printf("::: (" txt ": %d ms)\n", (uint32_t)(_t2-_t1));  

//---------------------------------------------------------------------
#pragma endregion
//==============================================================================
#pragma region OpenHAB REST API access

/**
 * @brief  Get something from OpenHAB REST API
 * 
 * @param  uri       path to the OpenHAB REST API server, e.g. "/rest/items/bubu"
 * @param  response  string to be filled with the response
 * @return int       HTTP return code, 200 is ok
 */
int getRestResponse( const String& uri, String& response )
{
    httpc.begin( wifiClient, OPENHAB_SERVER, OPENHAB_PORT, uri );
    int ok = httpc.GET();

    if (ok==200) {
        response = httpc.getString();
    } else {
        Serial.printf( "REST: " ANSI_RED "%d" ANSI_RESET "\n", ok );
    }
    return ok;
}


/**
 * @brief  Get an item description JSON from OpenHAB REST API
 * 
 * @param itemName  OpenHAB Item name
 * @param response  string to be filled with the response
 * @return int      HTTP return code, 200 is ok
 */
int getOpenHABItem( const char* itemName, String& response )
{
    String uri = String("/rest/items/") + String(itemName);
    return getRestResponse( uri, response );
}


/**
 * @brief  Change value of OpenHAB item through REST API
 * 
 * @param itemName  OpenHAB Item name
 * @param value     new value
 * @return int      HTTP return code, 200 is ok
 */
int postOpenHabItem( const char* itemName, String value )
{
    String uri = String("/rest/items/") + String(itemName);
    httpc.begin( wifiClient, OPENHAB_SERVER, OPENHAB_PORT, uri );
    httpc.addHeader("Content-Type", "text/plain");
    int ok = httpc.POST(value);
    String payload = httpc.getString();
    return ok;
}


/**
 * @brief  Get item state from OpenHAB REST API
 * 
 * @param itemName  OpenHAB Item name
 * @param response  string to be filled with the response
 * @return int      HTTP return code, 200 is ok
 */
int getOpenHABItemState( const char* itemName, String& response )
{
    String uri = String("/rest/items/") + String(itemName) + String("/state");
    return getRestResponse( uri, response );
}

#pragma endregion
//==============================================================================
#pragma region Dashboard field

/**
 * @brief All information required to display one item on TFT or e-Ink display.
 * 
 */
struct DashboardField 
{
    /**
     * @brief Types of dashboard items, determines how they are displayed
     * 
     */
    enum Type : uint8_t {
        DT_UNKNOWN=0,   // unknown type
        DT_LABEL,       // static label text, no online updates needed
        DT_CONTACT,     // OpenHAB Contact item, can be "OPEN" or "CLOSED"
        DT_SWITCH,      // OpenHAB Switch item, can be "ON" or "OFF"
        DT_INT,         // OpenHAB Integer item
        DT_FLOAT        // OpenHab Float item, format string in `format_`
    };
    static constexpr const char* type_names_ [] = {
        "Unknown", "Label", "Contact", "Switch", "Integer", "Float"
    };

    unsigned  row_;         ///< Y position, character row, 1..n
    unsigned  col_;         ///< X position, chararcter column, 1..n
    bool      hot_;         ///< highlight
    Type      type_;        ///< data type
    uint8_t   align_;       ///< text align. one of TL_DATUM, TR_DATUM, TC_DATUM
    struct {
        bool large : 1;
        bool green : 1;
    } attr_;
    unsigned  width_;
    char      text_[16];     ///< current textual representation
    char      name_[32];    ///< openHAB item name, may be empty
    char      format_[16];

    void create( JsonObject& json );    
    void refresh();
    void draw();
    void dump();
    Type inferType( const char* type, const char* format );
    const char* get_type_name() { return type_names_[(int)type_]; }
};


/**
 * @brief Dump all fields to Serial, for debugging
 * 
 */
void DashboardField::dump()
{
    Serial.printf( ANSI_BLUE "%s" ANSI_RESET ": ", name_ );
    Serial.printf( "%d,%d ", row_, col_ );
    Serial.printf( "'" ANSI_BOLD "%s" ANSI_RESET "' ", text_ );
    Serial.printf( "(Type %s ", get_type_name() );
    Serial.printf( "'%s') ", format_ );
    Serial.print( hot_ ? ANSI_BOLD ANSI_RED "HOT" ANSI_RESET : "hot" );
    Serial.println();
}


/**
 * @brief infer the data type of a dashboard field from other info
 * 
 * @param type ... the type string provided by OpenHAB, may be null or "\0"
 * @param format ... formating string provided by OpenHAB, may be null or "\0"
 * @return one of DashboardField::Type 
 */
DashboardField::Type DashboardField::inferType( const char* ohtype, const char* format )
{
    //Serial.printf("item='%s' type='%s' format='%s'\n", itemName, ohtype, format );

    // if we don't have an OpenHAB item name, then this is a static label
    if ( *name_==0 ) return DT_LABEL;

    // if OpenHAB didn't provide a type name, then we give up
    if ( ohtype==NULL || *ohtype==0 ) return DT_UNKNOWN;

    if (!strcasecmp_P(ohtype,PSTR("Switch"))) return DT_SWITCH;
    if (!strcasecmp_P(ohtype,PSTR("Contact"))) return DT_CONTACT;
    // Number items could also have a type like "Number:Temperature"
    if (!strncasecmp_P(ohtype,PSTR("Number"),6)) {    
        if (format==NULL || *format==0) return DT_INT;
        MatchState ms;
        char s[20];
        safe_copy(s,format);
        ms.Target(s);
        if (ms.Match(R"!!!(.*(%%[%d]*%.[%d]*[fg]).*)!!!")==REGEXP_MATCHED) 
            return DT_FLOAT;
        return DT_INT;
    }
    return DT_UNKNOWN;
}


/**
 * @brief Populate member fields from info provided in config JSON. 
 * If necessary, get additional info from OpenHAB REST API
 * 
 * @param jo  parsed json information from config text
 */
void DashboardField::create( JsonObject& jo )
{
    memset(this,0,sizeof(DashboardField));
    align_ = TC_DATUM;
    //----- 1st phase: fill members based on dash config info
    row_ = jo["row"]; 
    col_ = jo["col"]; 
    safe_copy( name_, jo["item"].as<const char*>() ); 
    safe_copy( text_, jo["label"].as<const char*>() ); 
    //Serial.printf("Create %s %s\n", name_, text_ );

    char sattr[40];
    safe_copy( sattr, jo["attr"].as<const char*>() );
    char* tok = strtok(sattr,",");
    while (tok) {
        if (!strcasecmp_P(tok,"right")) align_ = TR_DATUM;
        else if (!strcasecmp_P(tok,"left")) align_ = TL_DATUM;
        else if (!strcasecmp_P(tok,"center")) align_ = TC_DATUM;
        else if (!strcasecmp_P(tok,"large")) attr_.large = true;
        else if (!strcasecmp_P(tok,"green")) attr_.green = true;
        else Serial.printf("Unknown attribute: '%s'\n", tok);
        tok = strtok(NULL,",");
    }

    //----- try to retrieve further information from OpenHAB
    if (*name_=='\0') {
        type_ = DT_LABEL;
        align_ = TL_DATUM;
        return;
    }
    String json;
    if (200 != getOpenHABItem( name_, json)) return;

    StaticJsonDocument<512> jItem;
    DeserializationError error = deserializeJson(jItem, json);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    //----- 2nd phase: fill members based on OpenHAB information
    JsonObject oh = jItem.as<JsonObject>();        
    safe_copy( format_, oh["stateDescription"]["pattern"].as<const char*>()); 
    const char* ohtype = oh["type"].as<const char*>();
    type_ = inferType( ohtype, format_ );
}


/**
 * @brief Refresh current visualization by asking OpenHAB for state
 * 
 */
void DashboardField::refresh()
{
    if (*name_==0) return;   // just a label, nothing to do

    String state;
    if (200 != getOpenHABItemState(name_,state)) return;     

    switch (type_) {
        case DT_CONTACT:
            hot_ = (state == "OPEN"); 
            break;
        case DT_SWITCH:
            hot_ = (state == "ON");
            break;
        case DT_INT:
            snprintf( text_, sizeof(text_), format_, (int)state.toInt() );
            break;
        case DT_FLOAT:
            snprintf( text_, sizeof(text_), format_, state.toFloat() );
            break;
        default:
            return;
    }
    return;
}


#define Canvas TFT_eSprite

/**
 * @brief Ugly hack: if UTF-8 string contains degree symbol, then 
 * manually draw a little circle, because TFT_eSPI fonts are only 7-bit ASCII.
 * This works _only_ for top left aligned strings.
 * 
 * @param canvas reference to TFT_eSprite used for drawing
 * @param text   the string
 * @param x      origin, left
 * @param y      origin, top
 */
int16_t draw_with_degrees( Canvas& canvas, const char* text, int32_t x, int32_t y )
{
    char buf[20];
    memset(buf,0,sizeof(buf));
    safe_copy( buf, text );
    char* deg = strstr( buf, "°" );

    if (deg==NULL) {
        return canvas.drawString( text, x, y );
    }

    int16_t w=0;
    int r = canvas.textWidth("o")/4;    // radius of degree symbol
    *deg = '\0';
    if (canvas.getTextDatum()==TL_DATUM) {             // left to right }
        w = canvas.drawString( buf, x, y );
        x += w;
        canvas.drawCircle( x+r+1, y+r+1, r, canvas.textcolor );
        w += 2*r + 3;
        x += 2*r + 3;
        w += canvas.drawString( deg+2, x, y );
    } else if (canvas.getTextDatum()==TR_DATUM) {      // right to left
        w = canvas.drawString( deg+2, x, y );
        x -= w;
        canvas.drawCircle( x-r-1, y+r+1, r, canvas.textcolor );
        w += 2*r + 3;
        x -= 2*r + 3;
        w += canvas.drawString( buf, x, y );
    }
    return w;
}


void DashboardField::draw()
{
	TFT_eSprite* ptft = &blkFrame;
    ptft->setFreeFont( &FONT_NORMAL );
    unsigned fh = ptft->fontHeight()-1;
    unsigned fw = ptft->textWidth("H");
    unsigned x = (col_-1)*(fw+2) + 1;
    unsigned y = (row_-1)*(fh) + 1;

    // use bold font for static labels and for highlighted=inverse fields
    if (*name_==0) {
    	ptft->setFreeFont( &FONT_BOLD );
    	ptft->setTextColor( COLORED, UNCOLORED );
    } else if (hot_) {
    	ptft = &redFrame;
        ptft->setFreeFont( &FONT_BOLD );
        ptft->setTextColor( UNCOLORED, COLORED );
    } else if (attr_.green) {
    	ptft = &redFrame;
        ptft->setFreeFont( &FONT_LARGE );
        ptft->setTextColor( COLORED, UNCOLORED );
    } else {
        ptft->setFreeFont( &FONT_NORMAL );
    	ptft->setTextColor( COLORED, UNCOLORED );
    }
	ptft->setTextDatum( align_ );
    //ptft->fillRect( x-1, y-1, width_+2, fh, ptft->textbgcolor );
    unsigned tw = draw_with_degrees( *ptft, text_, x, y );
    if (width_ < tw) width_ = tw;
}

#pragma endregion
//==============================================================================
#pragma region LayoutConfig: an Array of dashboard fields

#define PERSIST_PATH "/persist.bin"

#define LAYOUT_CONFIG_VERSION 101

/**
 * @brief Complete screen layout configuration, i.e. a collection of 
 * layout fields, and methods to persist the configuration in Flash
 * 
 */
struct LayoutConfig 
{
    uint32_t    crc_;       ///< CRC over the JSON spec used to create this
    uint32_t    version_;   ///< version number, increment to force re-download of layout info from OpenHAB
    Array<DashboardField,MAX_DASH_FIELDS> dashItems_;

    bool load()
        {
            crc_ = 0;
            File f = LittleFS.open( PERSIST_PATH, "r");
            if (!f) return false;
            int nread = f.read( (uint8_t*)this, sizeof(*this));
            f.close();
            if (version_ != LAYOUT_CONFIG_VERSION) return false;
            return (nread > 0);
        }
    void save()
        {
            File f = LittleFS.open( PERSIST_PATH, "w");
            if (!f) return;
            version_ = LAYOUT_CONFIG_VERSION;
            f.write( (const uint8_t*)this, sizeof(*this));
            f.close();
        }
};

LayoutConfig layoutConfig;
#define dashItems layoutConfig.dashItems_

#pragma endregion
//=====================================================================
#pragma region Layout definition

/*
    For now, the JSON dashboard configuration string lives in Flash memory. 
    In the future, this could be read from an SD card, or from FFS,
    or from an OpenHAB variable
 */

const char layoutDefinition[] PROGMEM = 
R"!!!( {
  items: [
    { row:1, col:25,               item:"Temp_Han", attr:"right,green" },

    { row:1, col: 1, label:"Kitchen"   },
    { row:1, col: 8, label:"Fan",  item:"KitchenL_Fan_Stat" },
    { row:1, col:11, label:"Li=",  item:"KitchenL_CabinetLight_Stat" },
    { row:1, col:14, label:"Li^",  item:"KitchenL_CeilingLight_Stat" },

    { row:2, col: 1, label:"Dining"   },
    { row:2, col: 8, label:"[L]",  item:"EZ_Door_L" },
    { row:2, col:11, label:"[R]",  item:"EZ_Door_R" },
    { row:2, col:14, label:"Li^",  item:"DR_CeilingLight" },

    { row:3, col: 1, label:"Living"   },
    { row:3, col: 8, label:"(l)",  item:"WZ_Window_L" },
    { row:3, col:11, label:"(r)",  item:"WZ_Window_R" },
    { row:3, col:20,               item:"WZ_Temp", attr:"right" },

    { row:4, col: 1, label:"M.Bath"   },
    { row:4, col: 8, label:"Fan",  item:"BRL_Fan_Stat" },
    { row:4, col:11, label:"Li=",  item:"BRL_VanityLight_Stat" },
    { row:4, col:14, label:"Li^",  item:"BRL_CeilingLight_Stat" },
    { row:4, col:20,               item:"BRL_Temp", attr:"right" },

    { row:5, col: 1, label:"G.Bath"   },
    { row:5, col: 8, label:"Fan",  item:"BRR_Fan_Stat" },
    { row:5, col:11, label:"Li=",  item:"BRR_VanityLight_Stat" },
    { row:5, col:14, label:"Li^",  item:"BRR_CeilingLight_Stat" },

    { row:6, col: 1, label:"Laundry"   },
    { row:6, col: 8, label:"Fan",  item:"nWK_Fan_Stat" },
    { row:6, col:11, label:"Lit",  item:"nWK_Light_Stat" },
    { row:6, col:20,               item:"WK_Temp", attr:"right" },

    { row:7, col: 1, label:"G.BR"   },
    { row:7, col: 8, label:"(l)",  item:"GZ_Window" },
    { row:7, col:11, label:"(r)",  item:"GZ_Window_R" },
    { row:7, col:20,               item:"GZ_Temp", attr:"right" },

    { row:8, col: 1, label:"Office" },
    { row:8, col: 8, label:"(l)",  item:"AZ_L_Window" },
    { row:8, col:11, label:"[L]",  item:"AZ_Door_L" },
    { row:8, col:14, label:"[R]",  item:"AZ_Door_R" },
    { row:8, col:17, label:"Iron", item:"Sonoff_E_Proxy" },
    { row:8, col:20, label:"Sew",  item:"Sonoff_P_Proxy" },

    { row:7, col:24, label:"C.PC", item:"Cynthia_online" },
    { row:8, col:24, label:"B.PC", item:"Audio14_online" },

    { row:4, col:24, label:"Was",  item:"Washer_Stat" },
    { row:5, col:24, label:"Dry",  item:"Tumbler_Stat" }
  ]
 } )!!!";


StaticJsonDocument<8192> jLayout; 

bool parseLayoutDefinition( const char* json /* PROGMEM */ )
{
    DeserializationError error = deserializeJson( 
        jLayout, (const __FlashStringHelper*)json 
    );

    if (error) 
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return false;
    }

    int iitem=0;
    dashItems.clear();
    for (JsonObject item : jLayout["items"].as<JsonArray>()) 
    {
        if (++iitem > MAX_DASH_FIELDS) return false;

        DashboardField di;
        di.create(item);
        dashItems.push_back(di);
        yield();
    }

    Serial.println("parsed layout definition");
    return true;
}

//---------------------------------------------------------------------
#pragma endregion
//=====================================================================
#pragma region Display stuff

/**
 * @brief Draw everything that can be drawn without a Wifi connection
 * 
 */
void drawStaticContent()
{
    STOPWATCH_BEGIN
    for (DashboardField& item : dashItems)
    {
        yield();
        if (item.name_[0]=='\0')
            item.draw();
    }
    STOPWATCH_END("draw static")
}


/**
 * @brief Draw everything that needs to be refreshed
 * 
 */
void drawDynamicContent()
{
    STOPWATCH_BEGIN
    for (DashboardField& item : dashItems)
    {
        yield();
        if (item.name_[0])
            item.draw();
    }
    STOPWATCH_END("draw dynamic")
}


void initDisplay()
{
    STOPWATCH_BEGIN

    if (ePaper.Init() != 0) {
        Serial.print("ePaper init failed");
        return;
    }
    blkFrame.setColorDepth(1);          redFrame.setColorDepth(1);
    blkFramePtr = (uint8_t*) blkFrame.createSprite(EPD_WIDTH, EPD_HEIGHT);
    redFramePtr = (uint8_t*) redFrame.createSprite(EPD_WIDTH, EPD_HEIGHT);
    memset( blkFramePtr, UNCOLORED ? 0xFF : 0, EPD_HEIGHT * EPD_WIDTH / 8 );
    memset( redFramePtr, UNCOLORED ? 0xFF : 0, EPD_HEIGHT * EPD_WIDTH / 8 );
    blkFrame.setRotation(1);            redFrame.setRotation(1);
    blkFrame.setFreeFont(&FONT_NORMAL); redFrame.setFreeFont(&FONT_NORMAL);
    blkFrame.setTextColor( COLORED );   redFrame.setTextColor( COLORED );

    STOPWATCH_END("tft.Init")
}


#pragma endregion
//==============================================================================
#pragma region Power management


void prepareShutdown()
{
    SPI.end();

#ifdef POWER_PIN
    digitalWrite( POWER_PIN, LOW );
#endif
}


void preinit()
{
#ifdef POWER_PIN
    pinMode( POWER_PIN, OUTPUT );
    digitalWrite( POWER_PIN, HIGH );
#endif
}


void wakeupCallback() 
{
    static volatile int count;
    count++;

    Serial.println("... callback ...");
    Serial.flush();
}


// for timer-based light sleep to work, the os timers need to be disconnected
extern os_timer_t *timer_list;

void light_sleep( unsigned ms )
{
    timer_list = nullptr;
    wifi_set_opmode(NULL_MODE);
    wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
    wifi_fpm_open();
    wifi_fpm_set_wakeup_cb(wakeupCallback);  // set wakeup callback
    wifi_fpm_do_sleep( ms * 1000uLL );   
    delay( ms + 1 );            
}


#pragma endregion
//==============================================================================
#pragma region Arduino standard functions


/**
 * @brief Do things that can be done without a Wifi connection, 
 * whiel waiting for the Wifi connection to become established
 * 
 */
void doThingsWithoutWifi()
{
    initDisplay();

    // try to read persistent dashboard layout from FFS -----------------------
    STOPWATCH_BEGIN
    validLayoutFile = layoutConfig.load();
    STOPWATCH_END("FFS")
    yield();

    drawStaticContent();
}


/**
 * @brief Standard Arduino framework function, called after power-on 
 * or after waking up from deep sleep.
 * 
 */
void setup()
{
    /*  Reset reasons: 0=power on, 1=HW watchdog 2=exception, 
        3=SW watchdog, 4=SW restart, 5=wakeup, 6=ext.reset */
  	rst_info *resetInfo = ESP.getResetInfoPtr();
    //emergencyMode = true;
    uint32_t t_setup_start = millis();

    pinMode( LED_BUILTIN, OUTPUT);
    digitalWrite( LED_BUILTIN, HIGH );  // LED off

    Serial.begin(MY_BAUD_RATE);
    while (!Serial) {}

    LittleFS.begin();

    Serial.printf( 
        "\n\nReset:%d  Heap:%d  Chip id:%X  Flash id:%X (%d KB)  Core:%s  SDK:%s\n", 
        resetInfo->reason,
        ESP.getFreeHeap(),
        ESP.getChipId(),
        ESP.getFlashChipId(),
        (int)(ESP.getFlashChipSize() / 1024),
        ESP.getCoreVersion().c_str(),
        ESP.getSdkVersion()
    );
    yield();

//----- try to read saved configuration from RTC RAM ---------------------------

    bool validConfig;
    validConfig = readWifiConfig( &wifiConfig, sizeof(wifiConfig) );
	if (!validConfig) 
	    validConfig = readWifiConfigFFS( wifiConfig );

//----- turn on Wifi -----------------------------------------------------------

    digitalWrite( LED_BUILTIN, LOW );
    bool wifiOk = setupWifi( &wifiConfig, validConfig, doThingsWithoutWifi );
    digitalWrite( LED_BUILTIN, HIGH );

    if (wifiOk) {
    	writeWifiConfig( &wifiConfig, sizeof(wifiConfig) );
    	writeWifiConfigFFS( wifiConfig );
	}

//----- initialize services that depend on UDP ---------------------------------

    time_t epoch;
    struct tm *tminfo;
#ifdef USE_NTP
    ntpClient.begin();
    yield();
    ntpClient.update();
    yield();

    setenv("TZ","CET-1CEST,M3.5.0,M10.5.0/3",1);    // Europe/Berlin
    tzset();

    epoch = ntpClient.getEpochTime();
    tminfo = localtime(&epoch);
    strftime(msgbuf, sizeof msgbuf, "%Y-%m-%dT%H:%M:%SZ", tminfo);
    Serial.println(msgbuf);
#else
    epoch = 0;
#endif

//----- get/set some OpenHAB values --------------------------------------------

    String s;
    int ok = getOpenHABItemState( OH_ITEM_OTA, s);
    if ( (200==ok) && (s == "ON")) {    
        emergencyMode = true;
        postOpenHabItem(OH_ITEM_OTA,"OFF");
        setupOTA(); 
        digitalWrite( LED_BUILTIN,LOW); // turn on the light to show we are awake
        return;
    }

    unsigned batt = ESP.getVcc();
    Serial.printf(" Battery: %u mV \n", batt);
    postOpenHabItem(OH_ITEM_VCC,String(batt));

//----- wrap up basic setup ----------------------------------------------------

    uint32_t t_basic_setup_end = millis();
    Serial.printf(
        "  setup(): " ANSI_BOLD "%u" ANSI_RESET " ms. ", 
        (unsigned)(t_basic_setup_end-t_setup_start)
    );
    if (emergencyMode) Serial.print("OTA enabled. ");

    Serial.printf(
        "JSON %d b  "
        "Layout %d b (%d x %d b) \n"
        ,
        (int)strlen_P(layoutDefinition),
        (int)sizeof(layoutConfig),
        (int)layoutConfig.dashItems_.size(),
        (int)sizeof(DashboardField)
    ); 

    Serial.println(F("------------------------"));
    yield();

//----- see if layout definition has changed, parse if necessary ------------

    bool validLayout = false;
    uint32_t layoutLen = strlen_P(layoutDefinition);
    uint32_t layoutCRC = calculateCRC32_P( layoutDefinition, layoutLen );
    //Serial.printf("crc:%08X file:%08X\n", layoutCRC, layoutConfig.crc_);
    if (
        !validLayoutFile             // if there was no layout file in FFS ...
        || (layoutConfig.crc_ != layoutCRC)   // or the layout file was stale
        ) {
        Serial.println("Parsing layout definition");
        STOPWATCH_BEGIN
        validLayout = parseLayoutDefinition(layoutDefinition);
        STOPWATCH_END("parse JSON")
        if (validLayout) {
            layoutConfig.crc_ = layoutCRC;
            layoutConfig.save();
            drawStaticContent();
            yield();
        } 
    } else {
        validLayout = true;
        Serial.println("Re-using layout definition");
    }

//----- refresh all OH items, then turn off Wifi -------------------------------

    STOPWATCH_BEGIN
    for (DashboardField& item : dashItems)
    {
        item.refresh();
        yield();
    }
    STOPWATCH_END("refresh")

    // turn off Wifi now if we intend to go to sleep later
    if (!emergencyMode) {
        WiFi.disconnect();
        WiFi.mode(WIFI_OFF);
        yield();
        //WiFi.forceSleepBegin(); 
    }

    LittleFS.end();

//----- update display ---------------------------------------------------------

	drawDynamicContent();

    STOPWATCH_BEGIN
    ePaper.WaitUntilIdle();
    ePaper.DisplayFrame( blkFramePtr, redFramePtr, true );  // Update 3 colour display
    STOPWATCH_END("DisplayFrame")

    light_sleep(18000);
    STOPWATCH_BEGIN
    ePaper.WaitUntilIdle();
    STOPWATCH_END("WaitUntilIdle")

//----- now enter deep sleep ---------------------------------------------------

    uint32_t t_setup_end = millis();
    Serial.printf(
        "Ran for " ANSI_BOLD "%u" ANSI_RESET " ms, turning OFF now.\n", 
        (unsigned)(t_setup_end-t_setup_start)
    );
    Serial.flush();

    prepareShutdown();
    ESP.deepSleepInstant( 
        REPORT_INTERVAL * 1000ull ,
        // WAKE_RF_DISABLED 
        RF_NO_CAL 
    );
    // module goes into deep sleep here
}


void loop()
{
    if (!emergencyMode) return;
    if (loopWifi()) return;
	ArduinoOTA.handle();

#ifdef USE_NTP
    ntpClient.update();
#endif

    delay(1000);
}

//---------------------------------------------------------------------
#pragma endregion

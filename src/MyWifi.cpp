/**
 * @file        wifi.cpp
 * Author		: Bernd Waldmann
 * Created		: 9-Feb-2020
 * Tabsize		: 4
 * 
 * This Revision: $Id: MyWifi.cpp 1511 2023-05-18 18:24:47Z  $
 */

/*
   Copyright (C) 2022 Bernd Waldmann

   This Source Code Form is subject to the terms of the Mozilla Public 
   License, v. 2.0. If a copy of the MPL was not distributed with this 
   file, You can obtain one at http://mozilla.org/MPL/2.0/

   SPDX-License-Identifier: MPL-2.0
*/

/**
 * @brief  Connect or re-connect to Wifi AP, supports fast re-connection
 * using previously obtained parameters (after waking up from deep sleep).
 * Wifi connection parameters can be made persistent via RTC RAM.
 * 
 * Just call setupWifi(), it will handle 3 cases:
 * 1. Wifi was automatically reconnected by Espressif firmware
 * 2. re-connect to same Wifi network as last time, and re-use IP address etc
 *    received from DHCP server last time
 * 3. if (1) or (2) failed, connect to a Wifi network for the first time,
 *    and save connection parameters for next time
 */

#include <Arduino.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include "MyWifi.h"
#include "myauth.h" // defines WIFI_SSID, WIFI_PASSWORD

#define WIFI_CONFIG_VERSION 100

WiFiClient wifiClient;


//#define USE_BUILTIN_LED

#ifdef USE_BUILTIN_LED
 #define WIFI_LED_ON   digitalWrite(LED_BUILTIN,LOW)
 #define WIFI_LED_OFF  digitalWrite(LED_BUILTIN,HIGH)
#else
 #define WIFI_LED_ON
 #define WIFI_LED_OFF
#endif

//----------------------------------------------------------------------------

const char* iptoa( const IPAddress& ip )
{
    static char s[16];
    snprintf( s, sizeof(s), "%hd.%hd.%hd.%hd", ip[0], ip[1], ip[2], ip[3] );
    return s;
}

//----------------------------------------------------------------------------

/**
 * @brief Fill WiFi config struct (for RTC RAM) with currect WiFi parameters.
 * 
 * @param pState  points to WiFi parameters struct to be filled
 */
static void _fillConfig( WifiState* pState )
{
    pState->channel = WiFi.channel();           
    memcpy( pState->bssid, WiFi.BSSID(), 6 );
    pState->ip = WiFi.localIP();
    pState->gateway = WiFi.gatewayIP();
    pState->subnet = WiFi.subnetMask();
    pState->dns = WiFi.dnsIP();
    yield();
}

//----------------------------------------------------------------------------

static void _printConfig( WifiState* pState ) 
{
    Serial.println();
    Serial.print( "BSSID   : ");
    for (int i=0; i<6; i++) Serial.printf("%02X ", pState->bssid[i]);
    Serial.println();
    Serial.printf("Channel : %d \n", pState->channel ); 
    Serial.printf("IP      : %s \n", iptoa(pState->ip) ); 
    Serial.printf("Gateway : %s \n", iptoa(pState->gateway) ); 
    Serial.printf("Subnet  : %s \n", iptoa(pState->subnet) ); 
    Serial.printf("DNS     : %s \n", iptoa(pState->dns) ); 
}

//----------------------------------------------------------------------------

void onWiFiEvent(WiFiEvent_t event) {
    Serial.printf(" [WiFi:%d] ", event);

    switch(event) {
        case WIFI_EVENT_STAMODE_GOT_IP:
            Serial.print(" got IP ");
            //Serial.print("IP address: ");
            //Serial.print(WiFi.localIP());
            break;
        case WIFI_EVENT_STAMODE_DISCONNECTED:
            Serial.print(" lost connection ");
            break;
        case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
            Serial.print(" authmode change ");
            break;
        case WIFI_EVENT_STAMODE_CONNECTED:
            Serial.print(" connected ");
            break;

    }    
}

/**
 * @brief Try to re-connect to same WiFi AP as before.
 * 
 * @param   pState  points to struct with WiFi parameters
 * @return  true if connection was successful, else app should try _freshConnect
 */
static bool _reconnectWifi( WifiState* pState, void (*cb)(void) )
{
    const uint32_t timeout = 5000;      // 5 seconds
    bool blink = false;
    uint32_t t1, t2;

    Serial.printf("re-connect Wifi ch %d ", pState->channel);
    uint32_t t_start = millis();

    //WiFi.onEvent(onWiFiEvent);
    WiFi.config( pState->ip, pState->gateway, pState->subnet, pState->dns, pState->dns );
    WiFi.begin( WIFI_SSID, WIFI_PASSWORD, pState->channel, pState->bssid, true );

    delay(200);
    if (cb) cb();

    t1 = millis();
    int wfs;
    
    while( (wfs=WiFi.status()) != WL_CONNECTED ) {
        Serial.print(".");
        if (blink) { WIFI_LED_ON; } else { WIFI_LED_OFF; } blink = !blink;   
    
        if (wfs == WL_CONNECT_FAILED) {
            Serial.println("Failed to connect");
            return false;
        }

        if ((uint32_t)(millis() - t_start) > timeout) {
            WIFI_LED_OFF;
            Serial.print("ERROR  ");
            WiFi.disconnect();
            yield();
            WiFi.forceSleepBegin();
            yield();
            WiFi.forceSleepWake();
            yield();
            return false;
        }

        delay(50);
    }
    
    t2 = millis();
    Serial.printf(" wait:%u ms ", (unsigned)(t2-t1));

    WIFI_LED_OFF;
    Serial.print(" ok. ");
    return true;
}

//----------------------------------------------------------------------------

/**
 * @brief  Try to connect to WiFi AP
 * 
 * @return true  if connection was successful
 * @return false  if not
 */
static bool _freshConnectWifi()
{
    const uint32_t timeout = 20000; // 20 seconds
    bool blink = false;

    Serial.printf("Connect to Wifi ... ");
    uint32_t t_start = millis();

    WiFi.begin( WIFI_SSID, WIFI_PASSWORD );
    yield();

    while( WiFi.status() != WL_CONNECTED ) {
        Serial.print("*");
        if (blink) { WIFI_LED_ON; } else { WIFI_LED_OFF; } blink = !blink;
        delay(200);
        if ((uint32_t)(millis() - t_start) > timeout) {
            WIFI_LED_OFF;
            Serial.print("ERROR  ");
            WiFi.disconnect();
            delay( 1 );
            //WiFi.mode( WIFI_OFF );
            return false;
        }
    }
    WIFI_LED_OFF;
    yield();
    Serial.print(" ok. ");
    return true;
}

//----------------------------------------------------------------------------

/**
 * @brief Connect or reconnect to WiFi. WiFi parameters (channel, bssid etc.)
 * taken from/stored to a struct which can be held in RTC RAM.
 * 
 * @param pState     points to config struct with WiFi parameters
 * @param reconnect  if true, first try to reconnect using info in pStruct
 * @param cb         callback function, called while waiting for WiFi to connect
 *                   This function is guaranteed to be called exactly once,
 *                   independent of the success of the WiFi connection
 * @return true  if connection was successful
 * @return false  if reconnect and fresh connect failed
 */
bool setupWifi( WifiState* pState, bool reconnect, void (*cb)(void) )
{
    bool ok = false;
    uint32_t t_start = millis();

    WiFi.persistent( false );
    WiFi.mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    yield();

    if (WiFi.waitForConnectResult(10) == WL_CONNECTED) {
        Serial.println("Wifi already connected.");
        ok = true;
        if (cb) cb();
    } 
    if (!ok && reconnect && pState) {
        //_printConfig(pState);
        ok = _reconnectWifi( pState, cb );
    }
    if (!ok) {
        ok = _freshConnectWifi();
        if (cb) cb();
    }

    uint32_t t_stop = millis();
    Serial.printf(" total WiFi: %u ms\n", t_stop-t_start );

    if (!ok) 
        return false;

    //----- report MAC address
    char msgbuf[80];
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(msgbuf,sizeof(msgbuf),"MAC %02X:%02X:%02X:%02X:%02X:%02X",
        mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	Serial.print(msgbuf);

    //----- report IP address
    IPAddress ip;
    ip=WiFi.localIP();
    snprintf(msgbuf,sizeof(msgbuf)," IP %d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3] );
	Serial.println(msgbuf);

    if (pState) {
        //_printConfig(pState);
        _fillConfig(pState);
    }
    return true;
}


/**
 * @brief Refresh WiFi connection if necessary
 * 
 * @return true  had to refresh WiFi connection
 * @return false  WiFi was still connected
 */
bool loopWifi()
{
    if (WiFi.status() != WL_CONNECTED) {
        delay(1);
        setupWifi();
        return true;
    }
    return false;
}


static uint32_t _crc32( uint32_t crc, uint8_t by )
{
    for (uint32_t i = 0x80; i > 0; i >>= 1) {
        bool bit = crc & 0x80000000;
        if (by & i) {
            bit = !bit;
        }
        crc <<= 1;
        if (bit) {
            crc ^= 0x04c11db7;
        }
    }
    return crc;
}


/**
 * @brief Calculate CRC-32 for a byte array in RAM
 * 
 * @param data       byte array
 * @param length     length in bytes
 * @return uint32_t  CRC-32 value
 */
uint32_t calculateCRC32(const uint8_t* data, size_t length) 
{
    uint32_t crc = 0xffffffff;
    while (length--) 
        crc = _crc32( crc, *data++ );
    return crc;
}


/**
 * @brief Calculate CRC-32 for a byte array in flash memory (PROGMEM)
 * 
 * @param dataP      pointer to byte array in flash memory
 * @param length     length in bytes
 * @return uint32_t  CRC-32 value
 */
uint32_t calculateCRC32_P( const void* dataP /* PROGMEM */, size_t length ) 
{
    uint32_t crc = 0xffffffff;
    const uint8_t* data = (const uint8_t*) dataP;
    while (length--)
        crc = _crc32(crc, pgm_read_byte( data++ ));
    return crc;
}


/**
 * @brief Read Wifi (and possibly more) config information from RTC RAM 
 * to struct `cfg`
 * 
 * @param cfg    pointer to config struct (WifiState or derived type)
 * @param size   size of config struct 
 * @return       true if RTC RAM contained a valid config struct
 */
bool readWifiConfig( WifiState* cfg, size_t size ) 
{
    ESP.rtcUserMemoryRead(0, (uint32_t*) cfg, size);
    uint32_t crc = calculateCRC32( ((uint8_t *)cfg+4), size-4);
    return (crc == cfg->crc32) && (cfg->version == WIFI_CONFIG_VERSION);
}


/**
 * @brief Write Wifi (and possibly more) config information from struct `cfg` 
 * to RTC RAM
 * 
 * @param cfg   pointer to config struct (WifiState or derived type)
 * @param size  size of config struct 
 */
void writeWifiConfig( WifiState* cfg, size_t size )
{
    cfg->crc32 = calculateCRC32( ((uint8_t*)cfg)+4, size-4);
    cfg->version = WIFI_CONFIG_VERSION;
    ESP.rtcUserMemoryWrite(0, (uint32_t*) cfg, size);
}


static const char DEFAULT_PATH [] = "WIFIDATA.BIN";

/**
 * @brief Read Wifi config information from FFS to struct.
 * Use this after power-on, when RTC RAM is not valid
 * 
 * @param ws    ref to struct with Wifi state parameters
 * @param path  pathname or NULL to use default path
 * @return true  if read was successful
 */
bool readWifiConfigFFS( WifiState& ws, const char* path )
{
    if (path==NULL) path = DEFAULT_PATH;
    File f = LittleFS.open( path, "r");
    if (!f) return false;
    memset( &ws, 0, sizeof(WifiState) );
    int nread = f.read( (uint8*)&ws, sizeof(WifiState) );
    f.close();
    // Serial.printf("readWifiConfigFFS()=%d %s\n",nread, (nread==sizeof(WifiState)) ? "OK" : "ERROR" );
    return (nread == sizeof(WifiState)) && (ws.version==WIFI_CONFIG_VERSION);
}


/**
 * @brief Write Wifi config information from struct to FFS.
 * Will write only if the Wifi config is different from current file contents, 
 * or if file does not exist.
 * 
 * @param ws   ref to struct with Wifi state parameters
 * @param path pathname or NULL to use default path
 */
void writeWifiConfigFFS( WifiState& ws, const char* path ) 
{
    if (path==NULL) path = DEFAULT_PATH;
    ws.version = WIFI_CONFIG_VERSION;

    WifiState wsr;
    File f = LittleFS.open( path, "r");
    if (f) {    // file exists, let's see if content has changed
        int nread = f.read( (uint8*)&wsr, sizeof(WifiState) );
        f.close();
        if ((nread == sizeof(WifiState)) && (ws==wsr)) {
            // Serial.print(" no need for writeWifiConfigFFS() ");
            return;   // no need to write, equal
        }
    }

    f = LittleFS.open( path, "w");
    if (!f) {
        Serial.println("Error opening FFS file for write");
        return;
    }
    int nwr = f.write( (uint8*)&ws, sizeof(WifiState) );
    f.close();
    // Serial.printf("writeWifiConfigFFS(%d)\n", nwr );
    return;
}

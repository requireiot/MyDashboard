/**
 *  @filename   :   epdif.cpp
 *  @brief      :   Implements EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epdif.h"
#include <SPI.h>

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
    digitalWrite(pin, value);
}

int EpdIf::DigitalRead(int pin) {
    return digitalRead(pin);
}

void EpdIf::DelayMs(unsigned int delaytime) {
    delay(delaytime);
}

void EpdIf::SpiTransfer(unsigned char data) {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
}

void EpdIf::SpiTransferBurst(const unsigned char *data, unsigned int size) {
    digitalWrite(CS_PIN, LOW);
    SPI.writeBytes(data,size);
    digitalWrite(CS_PIN, HIGH);
}


int EpdIf::IfInit(void) {
    pinMode(CS_PIN, OUTPUT);
    //pinMode(RST_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT_PULLUP); 
#ifdef PIN_RESET
    pinMode(PIN_RESET,OUTPUT);
#endif
#ifdef PIN_NRESET
    pinMode(PIN_NRESET,OUTPUT);
#endif
    //Serial.printf("SPI %d MHz\n", (int)(EPAPER_SPI_FREQUENCY/1e6));
    SPI.beginTransaction(SPISettings(EPAPER_SPI_FREQUENCY, MSBFIRST, SPI_MODE0));
    SPI.begin();
    return 0;
}


void EpdIf::IfExit()
{
    pinMode(CS_PIN, INPUT);
    pinMode(DC_PIN, INPUT);
    pinMode(BUSY_PIN, INPUT); 
}


void EpdIf::IfReset() 
{
  #ifdef PIN_RESET
    DigitalWrite( PIN_RESET, LOW );
  #endif
  #ifdef PIN_NRESET
    DigitalWrite( PIN_NRESET, HIGH );
  #endif

    DelayMs(10); // was DelayMs(200);

  #ifdef PIN_RESET
    DigitalWrite( PIN_RESET, HIGH );
  #endif
  #ifdef PIN_NRESET
    DigitalWrite( PIN_NRESET, LOW );
  #endif

    DelayMs(10); // was DelayMs(200);
}

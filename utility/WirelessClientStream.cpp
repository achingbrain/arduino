/*
  WirelessClientStream.cpp
  An Arduino-Stream that wraps an instance of Client reconnecting to
  the remote-ip in a transparent way. A disconnected client may be
  recognized by the returnvalues -1 from calls to peek or read and
  a 0 from calls to write.

  Copyright (C) 2014 Alex Potsides. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  formatted using the GNU C formatting and indenting
 */

#include "WirelessClientStream.h"
#include <Arduino.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

WirelessClientStream::WirelessClientStream(uint8_t ce_pin, uint8_t csn_pin, uint8_t channel, uint8_t speed, uint8_t power, const char* rx_addr, const char* tx_addr)
: ce_pin(ce_pin),
  csn_pin(csn_pin),
  speed(speed),
  power(power),
  channel(channel),
  rx_addr(rx_addr),
  tx_addr(tx_addr)
{

}

void WirelessClientStream::begin()
{
  Mirf.cePin = ce_pin;
  Mirf.csnPin = csn_pin;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)rx_addr);

  Mirf.channel = channel;
  Mirf.payload = sizeof(int);

  Mirf.configRegister(RF_SETUP, RF_2Mbps | RF_0dBm);
  Mirf.config();
}

int WirelessClientStream::available()
{
  return Mirf.dataReady();
}

int WirelessClientStream::read()
{
  if(!Mirf.dataReady()) {
    return -1;
  }

  int incoming;

  Mirf.getData((byte *)&incoming);

  return incoming;
}

int WirelessClientStream::peek()
{
  return -1;
}

void WirelessClientStream::flush()
{

}

size_t WirelessClientStream::write(uint8_t c)
{
  Mirf.setTADDR((byte *)tx_addr);
  Mirf.send(&c);

  while(Mirf.isSending()) {
    // do nothing while we send
  }

  delay(15);

  return 1;
}

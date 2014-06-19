/*
  WirelessClientStream.h
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

#ifndef WIRELESSCLIENTSTREAM_H
#define WIRELESSCLIENTSTREAM_H

#include <inttypes.h>
#include <stdio.h>
#include <Stream.h>

class WirelessClientStream : public Stream
{
public:
  WirelessClientStream(uint8_t ce_pin, uint8_t csn_pin, uint8_t channel, uint8_t speed, uint8_t power, const char* rx_addr, const char* tx_addr);
  void begin();
  int available();
  int read();
  int peek();
  void flush();
  size_t write(uint8_t);

private:
  uint8_t ce_pin;
  uint8_t csn_pin;
  uint8_t channel;
  uint8_t speed;
  uint8_t power;
  const char* rx_addr;
  const char* tx_addr;
};

#endif

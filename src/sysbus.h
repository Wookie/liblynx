/*
 * sysbus.h
 * Copyright (C) David Huseby 2009 <dave@linuxprogrammer.org>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with main.c; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#ifndef _SYSBUS_H_
#define _SYSBUS_H_

/* there are three sources of the bus request signal.  Mikey does a logical OR
 * of the bus request signals when setting the bus request line.  I separated
 * the bus request sources into flags so that it is possible to always see the
 * source of the current bus request. */
typedef enum bus_request_e
{
    BUS_REQUEST_VIDEO   = 0x01,
    BUS_REQUEST_REFRESH = 0x02,
    BUS_REQUEST_CPU     = 0x03
} bus_request_t;

typedef struct sysbus_private_s * sysbus_private_t;

typedef struct sysbus_s
{
    bool            abus_active;        /* whether the address bus is being driven or not */
    bool            dbus_active;        /* whether the data bus is being driven or not */
    uint16_t        address;            /* the current system bus address value */
    uint8_t         data;               /* the current system bus data value */
    bus_request_t   bus_request;        /* the bus request signal state */
    bool            bus_grant;          /* the bus grant signal state */

    sysbus_private_t private;

} sysbus_t;

bool sysbus_init(sysbus_t * const bus, msg_q_t q);
bool sysbus_deinit(sysbus_t * const bus);



#endif


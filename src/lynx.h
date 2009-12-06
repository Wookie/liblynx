/*
 * lynx.h
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

#ifndef _LYNX_H_
#define _LYNX_H_

typedef enum lynx_log_lvl_e 
{
    LYNX_LOG,
    LYNX_WARNING,
    LYNX_ERROR

} lynx_log_lvl_t;

/* lynx log callback signature */
typedef void (*lynx_log_fn)(lynx_log_lvl_t const lvl, char const * const msg);

/* declare opaque pointer to lynx private data */
typedef struct lynx_private_s * lynx_private_t;

/* declare the lynx state structure, this is public along with the public 
 * subsystem states structures so that client applications can inspect the
 * state directly. this saves me from having to write get/set functions
 * for every piece of state. */
typedef struct lynx_s
{
    sysclock_t      clock;
    sysbus_t        bus;
    rom_t           rom;
    ram_t           ram;
    mikey_t         mikey;
    cpu_t           cpu;
    suzy_t          suzy;

    lynx_private_t  private;        /* private lynx data */

} lynx_t;

/* set up and tear down the lynx */
bool lynx_init(lynx_t * const lynx, char const * const rom, 
               char const * const cart, lynx_log_fn fn);
bool lynx_deinit(lynx_t * const lynx);

/* make another clock tick happen */
void lynx_update(lynx_t * const lynx);


#endif


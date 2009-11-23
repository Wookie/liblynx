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

typedef enum {
    LYNX_LOG,
    LYNX_WARNING,
    LYNX_ERROR
} LYNX_LOG_LEVEL;

/* lynx log callback signature */
typedef void (*lynx_log_fn)(LYNX_LOG_LEVEL const lvl, char const * const msg);

/* declare opaque pointer to lynx private data */
typedef struct lynx_private_s * lynx_private_t;

/* declare the lynx state structure, this is public along with the public 
 * subsystem states structures so that client applications can inspect the
 * state directly. this saves me from having to write get/set functions
 * for every piece of state. */
typedef struct lynx_s
{
    cpu_t           cpu;
    rom_t *         rom;
/*
    mikey_t         mikey;
    suzie_t         suzie;
    ram_t           ram;
    input_t         input;
*/

    lynx_private_t  private;        /* private lynx data */

} lynx_t;

/* allocate and free lynx state */
lynx_t * lynx_new();
void lynx_delete(lynx_t * const lynx);

/* set log callback for given log level */
bool lynx_set_log_callback(lynx_t * const lynx, lynx_log_fn fn);

/* set up and tear down the lynx */
void lynx_init(lynx_t * const lynx, char const * const rom);
void lynx_deinit(lynx_t * const lynx);

/* initialize the cart to execute */
void lynx_set_cart(lynx_t * const lynx, char const * const cart);

/* reset the lynx */
void lynx_reset(lynx_t * const lynx);

/* read a byte from the lynx memory, this presents the cpu's view on memory
 * and is subject to the memory mapping register state */
uint8_t lynx_peek(lynx_t * const lynx, uint16_t const address);

/* write a byte to the lynx memory, this presents the cpu's view on memory
 * and is subject to the memory mapping register state */
bool lynx_poke(lynx_t * const lynx, uint16_t const address, uint8_t const data);

/* set input button states */
/*void lynx_set_input(lynx_t * const lynx, input_t const * const input); */

/* make another clock tick happen */
void lynx_tick(lynx_t * const lynx);


#endif


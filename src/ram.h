/*
 * ram.h
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

#ifndef _RAM_H_
#define _RAM_H_


typedef struct ram_private_s * ram_private_t;

typedef struct ram_s
{
    uint8_t         data[ZERO_PAGE_SIZE + RAM_SIZE];        /* the RAM data */

    ram_private_t   private;                                /* RAM private data */

} ram_t;

bool ram_init(ram_t * const ram, msg_q_t * const q);
bool ram_deinit(ram_t * const ram);

/* NOTE: these are for debugging purposes */
bool ram_peek(ram_t * const ram, uint16_t const address, uint8_t * const data);
bool ram_poke(ram_t * const ram, uint16_t const address, uint8_t const data);

#endif


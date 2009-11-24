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

#define ZERO_PAGE_SIZE          (0x0100)
#define ZERO_PAGE_START         (0x0000)
#define ZERO_PAGE_END           (0x00FF)
#define IS_ZERO_PAGE_ADDRESS(a) ((a >= ZERO_PAGE_START) && (a <= ZERO_PAGE_END))
#define MAIN_RAM_SIZE           (0xFF00)
#define MAIN_RAM_START          (0x0100)
#define MAIN_RAM_END            (0xFEFF)
#define IS_MAIN_RAM_ADDRESS(a)  ((a >= RAM_START) && (a <= RAM_END))
#define RAM_SIZE                (0xFFFF)
#define RAM_START               (0x0000)
#define RAM_END                 (0xFFFF)
#define IS_RAM_ADDRESS(a)       ((a != 0xFFF8) && (a != 0xFFF9))


typedef struct ram_private_s * ram_private_t;

typedef struct ram_s
{
    uint8_t         data[ZERO_PAGE_SIZE + RAM_SIZE];        /* the RAM data */

    ram_private_t   private;                                /* RAM private data */
} ram_t;

bool ram_init(ram_t * const ram, log_fn fn);
bool ram_deinit(ram_t * const ram);

/* NOTE: these are for debugging purposes */
bool ram_peek(ram_t * const ram, uint16_t const address, uint8_t * const data);
bool ram_poke(ram_t * const ram, uint16_t const address, uint8_t const data);

#endif


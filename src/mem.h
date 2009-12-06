/*
 * mem.h
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

#ifndef _MEM_H_
#define _MEM_H_

typedef enum memmap_flags_e
{
    SEQ_ACCESS_DISABLE  = 0x80,
    RESERVED_1          = 0x40,
    RESERVED_2          = 0x20,
    RESERVED_3          = 0x10,
    VECTORS_ENABLE      = 0x08,
    ROM_ENABLE          = 0x04,
    MIKEY_ENABLE        = 0x02,
    SUZY_ENABLE         = 0x01

} memmap_flags_t;

typedef struct mem_s
{
    memmap_flags_t      ctrl;       /* memory map control register */

    ram_t               *ram;
    suzy_t              *suzy;
    mikey_t             *mikey;
    rom_t               *rom;

} mem_t;


bool mem_init(mem_t * const m, ram_t * const ram, suzy_t * const suzy,
              mikey_t * const mikey, rom_t * const rom);
bool mem_deinit(mem_t * const m);

bool mem_read(mem_t * const m, source_t const src, 
              uint16_t const address, uint8_t * const data);
bool mem_write(mem_t * const m, source_t const src,
               uint16_t const address, uint8_t const data);

#endif


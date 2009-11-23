/*
 * rom.h
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

#ifndef _ROM_H_
#define _ROM_H_

typedef struct rom_s
{
    uint8_t*    rom;        /* ROM data loaded from the rom file */
    size_t      size;       /* size of the ROM space */

} rom_t;

bool rom_init(rom_t * const rom, char const * const romfile, log_fn log);
bool rom_deinit(rom_t * const rom, log_fn log);

#endif


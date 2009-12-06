/*
 * memmap.h
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

#ifndef _MEMMAP_H_
#define _MEMMAP_H_

/* defining the various sources of things */
typedef enum source_e
{
    VIDEO,
    REFRESH,
    CPU,
    SUZY,
    MIKEY,
    RAM,
    ROM
} source_t;

/* main memory definitions */
#define RAM_SIZE                (0xFFFF)
#define SUZY_SIZE               (0x0100)
#define MIKEY_SIZE              (0x0100)
#define ROM_SIZE                (0x0200)

#define RAM_START               (0x0000)
#define RAM_END                 (0xFFFF)
#define SUZY_START              (0xFC00)
#define SUZY_END                (0xFCFF)
#define MIKEY_START             (0xFD00)
#define MIKEY_END               (0xFDFF)
#define ROM_START               (0xFE00)
#define ROM_END                 (0xFFFF)

#define IS_RAM_ADDRESS(a)       ((a != 0xFFF8) && (a != 0xFFF9))
#define IS_SUZY_ADDRESS(a)      ((a >= SUZY_START) && (a <= SUZY_END))
#define IS_MIKEY_ADDRESS(a)     ((a >= MIKEY_START) && (a <= MIKEY_END))
#define IS_ROM_ADDRESS(a)       ((a >= ROM_START) && (a <= ROM_END))

/* these are just for diagnostic information */
#define ZERO_PAGE_START         (0x0000)
#define ZERO_PAGE_END           (0x00FF)
#define MAIN_RAM_START          (0x0100)
#define MAIN_RAM_END            (0xFEFF)
#define INTVEC_START            (0xFFFA)
#define INTVEC_END              (0xFFFF)

#define ZERO_PAGE_SIZE          (0x0100)
#define MAIN_RAM_SIZE           (0xFF00)

#define IS_ZERO_PAGE_ADDRESS(a) ((a >= ZERO_PAGE_START) && (a <= ZERO_PAGE_END))
#define IS_MAIN_RAM_ADDRESS(a)  ((a >= RAM_START) && (a <= RAM_END))
#define IS_INTVEC_ADDRESS(a)    ((a >= INTVEC_START) && (a <= INTVEC_END))

#endif


/*
 * 65SC02.h
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

#ifndef _65SC02_H_
#define _65SC02_H_

/* 65SC02 status register bits */
typedef enum {
    NEGATIVE    = 0x80,
    OVERFLOW    = 0x40,
    ONE         = 0x20,
    BREAK       = 0x10,
    DECIMAL     = 0x08,
    MASK_INT    = 0x04,
    ZERO        = 0x02,
    CARRY       = 0x01
} STATUS_FLAGS;

/* create opaque pointer to private cpu state */
typedef struct cpu_private_s * cpu_private_t;

/* 65SC02 state struct */
typedef struct cpu_s
{
    uint8_t         PS;         /* Processor status register    */
    uint8_t         A;          /* Accumulator                  */
    uint8_t         X;          /* X index register             */
    uint8_t         Y;          /* Y index register             */
    uint8_t         SP;         /* Stack Pointer                */
    uint16_t        PC;         /* Program Counter              */

    cpu_private_t   private;    /* private internal CPU state   */

} cpu_t;

bool cpu_init(cpu_t * const cpu, log_fn fn);
bool cpu_deinit(cpu_t * const cpu);

bool cpu_tick(cpu_t * const cpu);
int cpu_get_remaining_ticks(cpu_t const * const cpu);


#endif


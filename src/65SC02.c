/*
 * 65SC02.c
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

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "65SC02.h"

struct cpu_private_s
{
    log_fn      lfn;                /* cpu logging function */

    int         remaining_ticks;    /* ticks remaining in current instruction */
    
    uint8_t     opcode;             /* opcode read from memory */
    uint8_t     operands[2];        /* operands read from memory */

    int8_t      relative_address;   /* relative address scratch space */
    uint8_t     zeropage_address;   /* zero page address scatch space */
    uint16_t    absolute_address;   /* absolute address scratch space */

    bool        page_cross_penalty; /* page crossing tick penalty? */
};



bool cpu_init(cpu_t * const cpu, log_fn fn)
{
    if(!cpu)
        return false;

    /* clear out the cpu struct memory */
    memset(cpu, 0, sizeof(cpu_t));

    /* allocate the private memory area */
    cpu->private = calloc(1, sizeof(struct cpu_private_s));

    /* store the logging function */
    cpu->private->lfn = fn;

    return true;
}



bool cpu_deinit(cpu_t * const cpu)
{
    if(!cpu)
        return false;

    if(cpu->private)
        free(cpu->private);

    return true;
}



bool cpu_tick(cpu_t * const cpu)
{
    return true;
}



int cpu_get_remaining_ticks(cpu_t const * const cpu)
{
    if(!cpu)
        return -1;

    return cpu->private->remaining_ticks;
}


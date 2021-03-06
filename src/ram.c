/*
 * ram.c
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

#include "memmap.h"
#include "msg.h"
#include "log.h"
#include "ram.h"

struct ram_private_s
{
    msg_q_t     q;
};


bool ram_init(ram_t * const ram, msg_q_t q)
{
    if(!ram || !q)
        return false;

    /* zero out the ram struct */
    memset(ram, 0, sizeof(ram_t));

    /* allocate the private struct */
    ram->private = calloc(1, sizeof(struct ram_private_s));

    /* store msg q pointer */
    ram->private->q = q;

    return true;
}



bool ram_deinit(ram_t * const ram)
{
    if(!ram)
        return false;

    if(ram->private)
        free(ram->private);

    return true;
}



bool ram_peek(ram_t * const ram, uint16_t const address, uint8_t * const data)
{
    if(!ram || !ram->private)
        return false;

    if(!data)
    {
        LERR(ram->private->q, RAM, "ram_peek(): NULL data pointer");
        return false;
    }
    
    if(!IS_RAM_ADDRESS(address))
    {
        LERR(ram->private->q, RAM, "ram_peek(): reading from invalid RAM address 0x%04x", address);
        return false;
    }

    /* read the byte */
    (*data) = ram->data[address];

    return true;
}



bool ram_poke(ram_t * const ram, uint16_t const address, uint8_t const data)
{
    if(!ram || !ram->private)
        return false;

    if(!IS_RAM_ADDRESS(address))
    {
        LERR(ram->private->q, RAM, "ram_poke(): writing to invalid RAM address 0x%04x", address);
        return false;
    }
    
    /* write the byte */
    ram->data[address] = data;

    return true;
}





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

#include "log.h"
#include "ram.h"

#define RAM_LOG(a, ...) if((a->private) && (a->private->lfn)) LLOG(a->private->lfn, __VA_ARGS__)
#define RAM_WARN(a, ...) if((a->private) && (a->private->lfn)) LWARN(a->private->lfn, __VA_ARGS__)
#define RAM_ERR(a, ...) if((a->private) && (a->private->lfn)) LERR(a->private->lfn, __VA_ARGS__)



struct ram_private_s
{
    log_fn  lfn;
};



bool ram_init(ram_t * const ram, log_fn fn)
{
    if(!ram)
        return false;

    /* zero out the ram struct */
    memset(ram, 0, sizeof(ram_t));

    /* allocate the private struct */
    ram->private = calloc(1, sizeof(struct ram_private_s));

    /* store the log function */
    ram->private->lfn = fn;

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
        RAM_ERR(ram, "ram_peek(): NULL data pointer");
        return false;
    }
    
    if(!IS_RAM_ADDRESS(address))
    {
        RAM_ERR(ram, "ram_peek(): reading from invalid RAM address 0x%04x", address);
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
        RAM_ERR(ram, "ram_poke(): writing to invalid RAM address 0x%04x", address);
        return false;
    }
    
    /* write the byte */
    ram->data[address] = data;

    return true;
}





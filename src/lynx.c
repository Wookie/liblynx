/*
 * lynx.c
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

#include "misc.h"
#include "log.h"
#include "65SC02.h"
#include "ram.h"
#include "mikey.h"
#include "suzy.h"
#include "rom.h"
#include "intvec.h"
#include "lynx.h"

#define LYNX_LOG(a, ...) if((a->private) && (a->private->lfn)) LLOG(a->private->lfn, __VA_ARGS__)
#define LYNX_WARN(a, ...) if((a->private) && (a->private->lfn)) LWARN(a->private->lfn, __VA_ARGS__)
#define LYNX_ERR(a, ...) if((a->private) && (a->private->lfn)) LERR(a->private->lfn, __VA_ARGS__)


/* private lynx data struct */
struct lynx_private_s
{
    log_fn      lfn;            /* log callbacks for each log level */
};



bool lynx_init(lynx_t * const lynx, char const * const rom,
               char const * const cart, lynx_log_fn fn)
{
    if(!lynx || !rom || !cart)
        return false;

    /* zero out lynx struct memory */
    memset(lynx, 0, sizeof(lynx_t));

    /* allocate the private struct */
    lynx->private = calloc(1, sizeof(struct lynx_private_s));

    /* store the lynx log callback */
    lynx->private->lfn = (log_fn)fn;

    /* initialize rom */
    rom_init(&lynx->rom, rom, (log_fn)fn);

    /* initialize ram */
    ram_init(&lynx->ram, (log_fn)fn);

    /* initialize mikey */
    /* mikey_init(&lynx->mikey, fn); */

    /* initialize suzie */

    /* initialize input */

    return true;
}



bool lynx_deinit(lynx_t * const lynx)
{
    if(!lynx)
        return false;

    /* deinitialize input */
    
    /* deinitialize mikey */

    /* deinitialize suzie */

    /* deinitialize ram */
    ram_deinit(&lynx->ram);

    /* deinitialize rom */
    rom_deinit(&lynx->rom);

    if(lynx->private)
        free(lynx->private);

    return true;
}



void lynx_set_cart(lynx_t * const lynx, char const * const cart)
{
}



void lynx_reset(lynx_t * const lynx)
{
}



/* read a byte from the lynx memory, this presents the cpu's view on memory
 * and is subject to the memory mapping register state */
bool lynx_peek(lynx_t * const lynx, uint16_t const address, uint8_t * const data)
{
    if(!lynx || !lynx->private)
        return false;

    if(!data)
    {
        LYNX_ERR(lynx, "lynx_peek(): NULL data pointer");
        return false;
    }

    if(IS_ZERO_PAGE_ADDRESS(address))
    {
        /* zero page access to RAM */
        ram_peek(&lynx->ram, address, data);
    }
    else if(IS_MAIN_RAM_ADDRESS(address))
    {
        /* main RAM */
        ram_peek(&lynx->ram, address, data);
    }
    else if(IS_SUZY_ADDRESS(address) && IS_BIT_SET(lynx->mem_map_ctrl, SUZY))
    {
        /* suzy access */
    }
    else if(IS_MIKEY_ADDRESS(address) && IS_BIT_SET(lynx->mem_map_ctrl, MIKEY))
    {
        /* mikey access */
        /* mikey_peek(&lynx->mikey, address, data); */
    }
    else if(IS_ROM_ADDRESS(address) && IS_BIT_SET(lynx->mem_map_ctrl, ROM))
    {
        /* ROM access */
        rom_peek(&lynx->rom, address, data);
    }
    else if(address == 0xFFF8)
    {
        /* reserved register */
        (*data) = 0x00;
    }
    else if(address == 0xFFF9)
    {
        /* memory map control register */
        (*data) = lynx->mem_map_ctrl;
    }
    else if(IS_INTVEC_ADDRESS(address) && 
            IS_BIT_SET(lynx->mem_map_ctrl, CPU_INT_VECTORS))
    {
        /* interrupt vector registers */
    }
    else
    {
        /* RAM access */
        ram_peek(&lynx->ram, address, data);
    }

    return true;
}



/* write a byte to the lynx memory, this presents the cpu's view on memory
 * and is subject to the memory mapping register state */
bool lynx_poke(lynx_t * const lynx, uint16_t const address, uint8_t const data)
{
    return true;
}



/* void lynx_set_input(lynx_t * const lynx, input_t const * const input)
 * {
 * }
 */



void lynx_tick(lynx_t * const lynx)
{
}


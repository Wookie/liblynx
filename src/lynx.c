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

#include "log.h"
#include "65SC02.h"
#include "rom.h"
#include "lynx.h"

struct lynx_private_s
{
    log_fn      lfn;            /* log callbacks for each log level */
};

/* this function initializes the lynx and loads the rom data */
lynx_t * lynx_new()
{
    /* allocate the lynx struct */
    lynx_t * lynx = calloc(1, sizeof(lynx_t));

    /* allocate the private struct */
    lynx->private = calloc(1, sizeof(struct lynx_private_s));

    return lynx;
}

void lynx_delete(lynx_t * const lynx)
{
    if(!lynx)
    {
        LERR(lynx->private->lfn, "lynx_delete(): passed NULL pointer");
        return;
    }

    if(lynx->private)
    {
        /* free the lynx private struct memory */
        free(lynx->private);
    }
    else
    {
        LWARN(lynx->private->lfn, "lynx_delete(): private struct pointer is NULL");
    }

    /* free the lynx struct memory */
    free(lynx);
}

bool lynx_set_log_callback(lynx_t * const lynx, lynx_log_fn fn)
{
    if(!lynx)
        return false;

    if(!fn)
        return false;

    /* store the log callback function for the given log level */
    lynx->private->lfn = (log_fn)fn;

    return true;
}

void lynx_init(lynx_t * const lynx, char const * const rom)
{
    /* initialize mikey */

    /* initialize suzie */

    /* initialize ram */

    /* initialize rom */
    rom_init(&lynx->rom, rom, lynx->private->lfn);

    /* initialize input */
}

void lynx_deinit(lynx_t * const lynx)
{
    /* deinitialize mikey */

    /* deinitialize suzie */

    /* deinitialize ram */

    /* deinitialize rom */
    rom_deinit(&lynx->rom, lynx->private->lfn);

    /* deinitialize input */
}

void lynx_set_cart(lynx_t * const lynx, char const * const cart)
{
}

void lynx_reset(lynx_t * const lynx)
{
}

/* void lynx_set_input(lynx_t * const lynx, input_t const * const input)
 * {
 * }
 */

void lynx_update(lynx_t * const lynx)
{
}


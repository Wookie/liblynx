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
#include "memmap.h"
#include "msg.h"
#include "log.h"
#include "cpu.h"
#include "65SC02.h"
#include "ram.h"
#include "mikey.h"
#include "suzy.h"
#include "rom.h"
#include "sysclock.h"
#include "sysbus.h"
#include "mem.h"
#include "lynx.h"

/* private lynx data struct */
struct lynx_private_s
{
    lynx_log_fn lfn;            /* log callbacks for each log level */
    msg_q_t     q;              /* message queue */
};

#define LYNX_LOG(a, msg)  if((a->private) && (a->private->lfn)) (*(a->private->lfn))(LYNX_LOG, msg)
#define LYNX_WARN(a, msg) if((a->private) && (a->private->lfn)) (*(a->private->lfn))(LYNX_WARNING, msg)
#define LYNX_ERR(a, msg)  if((a->private) && (a->private->lfn)) (*(a->private->lfn))(LYNX_ERROR, msg)

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
    lynx->private->lfn = fn;

    /* initialize the msg queue */
    msg_q_init(&lynx->private->q);

    /* initialize the system bus */
    sysbus_init(&lynx->bus, &lynx->private->q);

    /* initialize rom */
    rom_init(&lynx->rom, rom, &lynx->private->q);

    /* initialize ram */
    ram_init(&lynx->ram, &lynx->private->q);

    /* initialize mikey */
    mikey_init(&lynx->mikey, &lynx->private->q);

    /* initialize the cpu */
    cpu_init(&lynx->cpu, &lynx->private->q);
    
    /* initialize suzie */
    suzy_init(&lynx->suzy, &lynx->private->q);

    /* initialize the system clock */
    sysclock_init(&lynx->clock);

    return true;
}



bool lynx_deinit(lynx_t * const lynx)
{
    if(!lynx)
        return false;

    /* deinitialize the clock */
    sysclock_deinit(&lynx->clock);

    /* deinitialize suzy */
    suzy_deinit(&lynx->suzy);

    /* deinitialize the cpu */
    cpu_deinit(&lynx->cpu);
    
    /* deinitialize mikey */
    mikey_deinit(&lynx->mikey);

    /* deinitialize ram */
    ram_deinit(&lynx->ram);

    /* deinitialize rom */
    rom_deinit(&lynx->rom);

    /* deinitialize the system bus */
    sysbus_deinit(&lynx->bus);

    if(lynx->private)
        free(lynx->private);

    return true;
}



void lynx_update(lynx_t * const lynx)
{
    msg_t msg;

    if(!lynx)
        return;

    /* process all of the messages */
    while(msg_q_dequeue(&lynx->private->q, &msg))
    {
        switch(msg.type)
        {
            case LOG_MSG:
                LYNX_LOG(lynx, msg.params.msg);
                free(msg.params.msg);
                break;
            case WARN_MSG:
                LYNX_WARN(lynx, msg.params.msg);
                free(msg.params.msg);
                break;
            case ERR_MSG:
                LYNX_ERR(lynx, msg.params.msg);
                free(msg.params.msg);
                break;
            case SET_RESET:
                break;
            case SET_ADDRESS_BUS:
                break;
            case SET_DATA_BUS:
                break;
        }
    }
}


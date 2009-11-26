/*
 * sysbus.c
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
#include "sysbus.h"

struct sysbus_private_s
{
    msg_q_t     *q;
};


bool sysbus_init(sysbus_t * const bus, msg_q_t * const q)
{
    if(!bus || !q)
        return false;

    /* clear out sysbus struct */
    memset(bus, 0, sizeof(sysbus_t));

    /* allocate private struct */
    bus->private = calloc(1, sizeof(struct sysbus_private_s));

    /* store msg q pointer */
    bus->private->q = q;

    return true;
}


bool sysbus_deinit(sysbus_t * const bus)
{
    if(!bus)
        return false;

    if(bus->private)
        free(bus->private);

    return true;
}


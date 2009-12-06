/*
 * sysclock.c
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "memmap.h"
#include "msg.h"
#include "log.h"
#include "sysclock.h"

bool sysclock_init(sysclock_t * const clock)
{
    if(!clock)
        return false;

    memset(clock, 0, sizeof(sysclock_t));

    return true;
}

bool sysclock_deinit(sysclock_t * const clock)
{
    if(!clock)
        return false;

    return true;
}

bool sysclock_update(sysclock_t * const clock)
{
    if(!clock)
        return false;

    /* change the clock state */
    clock->state = !clock->state;

    if(!clock->state)
    {
        /* update tick count on falling edge */
        clock->ticks++;
    }

    return true;
}


/*
 * sysclock.h
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

#ifndef _SYSCLOCK_H_
#define _SYSCLOCK_H_

/* the Lynx clock is 16 MHz, which means a tick happens every 63 nanoseconds */
#define NS_PER_TICK         (63)
#define NS_PER_LOW_PHASE    (31)
#define NS_PER_HIGH_PHASE   (32)

typedef struct sysclock_s
{
    uint64_t    ticks;
    bool        state;

} sysclock_t;

bool sysclock_init(sysclock_t * const clock);
bool sysclock_deinit(sysclock_t * const clock);

bool sysclock_update(sysclock_t * const clock);

#endif


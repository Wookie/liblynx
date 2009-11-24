/*
 * suzy.h
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

#ifndef _SUZY_H_
#define _SUZY_H_

#define SUZY_SIZE            (0x0100)
#define SUZY_START           (0xFC00)
#define SUZY_END             (0xFCFF)
#define IS_SUZY_ADDRESS(a)   ((a >= SUZY_START) && (a <= SUZY_END))

typedef struct suzy_s
{
    /* suzy registers */
} suzy_t;

#endif


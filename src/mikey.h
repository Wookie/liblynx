/*
 * mikey.h
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

#ifndef _MIKEY_H_
#define _MIKEY_H_

typedef struct mikey_private_s * mikey_private_t;

typedef struct mikey_s
{
    /* mikey registers */

    mikey_private_t     private;

} mikey_t;


bool mikey_init(mikey_t * const mikey, msg_q_t * const q);
bool mikey_deinit(mikey_t * const mikey);

#endif


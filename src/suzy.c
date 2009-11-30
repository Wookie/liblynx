/*
 * suzy.c
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
#include "suzy.h"

struct suzy_private_s
{
    msg_q_t     q;
};

bool suzy_init(suzy_t * const suzy, msg_q_t q)
{
    if(!suzy || !q)
        return false;

    /* clear out suzy struct */
    memset(suzy, 0, sizeof(suzy_t));

    /* allocate private struct */
    suzy->private = calloc(1, sizeof(struct suzy_private_s));

    /* store msg q pointer */
    suzy->private->q = q;

    return true;
}


bool suzy_deinit(suzy_t * const suzy)
{
    if(!suzy)
        return false;

    if(suzy->private)
        free(suzy->private);

    return true;
}


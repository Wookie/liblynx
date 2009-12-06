/*
 * mikey.c
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
#include "mikey.h"

typedef enum mikey_state_e
{
    MIKEY_RESET,
    CPU_RUN

} mikey_state_t;

struct mikey_private_s
{
    msg_q_t         q;
    mikey_state_t   state;      /* mikey state */
};

bool mikey_init(mikey_t * const mikey, msg_q_t q)
{
    if(!mikey || !q)
        return false;

    /* zero out mikey */
    memset(mikey, 0, sizeof(mikey_t));

    /* allocate mikey's private struct */
    mikey->private = calloc(1, sizeof(struct mikey_private_s));

    /* store the msg q pointer */
    mikey->private->q = q;

    return true;
}


bool mikey_deinit(mikey_t * const mikey)
{
    if(!mikey)
        return false;

    /* free the private struct */
    if(mikey->private)
        free(mikey->private);

    return true;
}



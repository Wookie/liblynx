/*
 * msg.c
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

struct msg_q_s
{
    msg_t           msgs[MSG_Q_SIZE];
    int             num_msgs;
    int             head;
    int             tail;
};


bool msg_q_init(msg_q_t q)
{
    if(!q)
        return false;

    /* clear out the message queue */
    memset(q, 0, sizeof(msg_q_t));

    return true;
}


bool msg_q_deinit(msg_q_t q)
{
    if(!q)
        return false;

    return true;
}


bool msg_q_enqueue(msg_q_t q, msg_t const * const msg)
{
    if(!q || !msg)
        return false;

    /* check for full queue */
    if(q->num_msgs == MSG_Q_SIZE)
        return false;

    /* copy the message into the tail */
    memcpy(&q->msgs[q->tail], msg, sizeof(msg_t));

    /* increment the number of messages in the queue */
    q->num_msgs++;

    /* adjust the tail index */
    q->tail = ((q->tail + 1) % MSG_Q_SIZE);

    return true;
}


bool msg_q_dequeue(msg_q_t q, msg_t * const msg)
{
    if(!q || !msg)
        return false;

    /* check for empty queue */
    if(!q->num_msgs)
        return false;

    /* copy the head message into the out buffer */
    memcpy(msg, &q->msgs[q->head], sizeof(msg_t));

    /* decrement the number of messages in the queue */
    q->num_msgs--;

    /* adjust the head index */
    q->head = ((q->head + 1) % MSG_Q_SIZE);

    return true;
}


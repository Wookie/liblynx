/*
 * msg.h
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

#ifndef _MSG_H_
#define _MSG_H_

#define MSG_Q_SIZE  (256)

typedef enum msg_type_e
{
    LOG_MSG,
    WARN_MSG,
    ERR_MSG,
    SET_RESET,
    SET_ADDRESS_BUS,
    SET_DATA_BUS

} msg_type_t;

typedef union msg_params_u
{
    uint16_t        address;
    uint8_t         data;
    bool            value;
    char            *msg;

} msg_params_t;

typedef struct msg_s
{
    source_t        src;        /* subsystem sending the message */
    msg_type_t      type;       /* type of message */
    msg_params_t    params;     /* message parameters */

} msg_t;

typedef struct msg_q_s * msg_q_t;

bool msg_q_init(msg_q_t q);
bool msg_q_deinit(msg_q_t q);

bool msg_q_enqueue(msg_q_t q, msg_t const * const msg);
bool msg_q_dequeue(msg_q_t q, msg_t * const msg);

#endif


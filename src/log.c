/*
 * log.c
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

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "memmap.h"
#include "msg.h"
#include "log.h"

#define MAX_LOG_MSG_SIZE (4096)

void log_msg(msg_q_t q, source_t const src, log_level_t const lvl, 
             char const * const fmt, ...)
{
    static msg_t msg;
    static char buf[MAX_LOG_MSG_SIZE];
    va_list ap;

    if(!q)
        return;

    va_start(ap, msg);
    
    /* format the message */
    vsnprintf(buf, MAX_LOG_MSG_SIZE, fmt, ap);

    /* queue up the log the message */
    memset(&msg, 0, sizeof(msg_t));
    msg.type = lvl;
    msg.src = src;
    msg.params.msg = strdup(buf); /* memory will be released when processed */
    msg_q_enqueue(q, &msg);

    va_end(ap);
}



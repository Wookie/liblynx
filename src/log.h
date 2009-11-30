/*
 * log.h
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

#ifndef _LOG_H_
#define _LOG_H_


typedef enum log_level_e
{
    LOG,
    WARNING,
    ERROR

} log_level_t;

/* the logging wrapper function */
void log_msg(msg_q_t q, source_t const src, log_level_t const lvl, 
             char const * const msg, ...);

/* utility macros */
#define LLOG(q, src, ...)     log_msg(q, src, LOG, __VA_ARGS__)
#define LWARN(q, src, ...)    log_msg(q, src, WARNING, __VA_ARGS__)
#define LERR(q, src, ...)     log_msg(q, src, ERROR, __VA_ARGS__)

#endif


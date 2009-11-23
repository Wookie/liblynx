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


typedef enum {
    LOG,
    WARNING,
    ERROR
} LOG_LEVEL;

/* log callback signature */
typedef void (*log_fn)(LOG_LEVEL const lvl, char const * const msg);

/* the universal logging function */
void log_msg(log_fn log, LOG_LEVEL const lvl, char const * const msg, ...);

/* utility macros */
#define LLOG(log, ...)     log_msg(log, LOG, __VA_ARGS__)
#define LWARN(log, ...)    log_msg(log, WARNING, __VA_ARGS__)
#define LERR(log, ...)     log_msg(log, ERROR, __VA_ARGS__)

#endif


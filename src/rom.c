/*
 * rom.h
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
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "rom.h"

bool rom_init(rom_t * const rom, char const * const romfile, log_fn log)
{
    FILE* in = NULL;
    size_t num_read = 0;

    if(!rom)
    {
        LERR(log, "rom_init(); called with NULL rom pointer");
        return false;
    }

    if(!romfile)
    {
        LERR(log, "rom_init(): NULL romfile pointer");
        return false;
    }

    if((in = fopen(romfile, "rb")) == NULL)
    {
        LERR(log, "rom_init(): failed to open romfile");
        return false;
    }

    /* seek to the end */
    fseek(in, 0, SEEK_END);
    rom->size = ftell(in);
    fseek(in, 0, SEEK_SET);

    /* allocate buffer to store rom data */
    rom->rom = calloc(sizeof(uint8_t), rom->size);

    if(!rom->rom)
    {
        LERR(log, "rom_init(): failed to allocate rom buffer");
        fclose(in);
        return false;
    }

    /* read in the file data */
    if((num_read = fread(rom->rom, sizeof(uint8_t), rom->size, in)) != rom->size)
    {
        LERR(log, "rom_init(); failed to read in rom file");
        free(rom->rom);
        fclose(in);
        return false;
    }

    fclose(in);

    return true;
}

bool rom_deinit(rom_t * const rom, log_fn log)
{
    if(!rom)
    {
        LERR(log, "rom_deinit(): called with NULL rom pointer");
        return false;
    }

    if(!rom->rom)
    {
        free(rom->rom);
    }
    else
    {
        LWARN(log, "rom_deinit(): NULL rom memory pointer");
    }

    return true;
}


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

#define ROM_LOG(a, ...) if((a->private) && (a->private->lfn)) LLOG(a->private->lfn, __VA_ARGS__)
#define ROM_WARN(a, ...) if((a->private) && (a->private->lfn)) LWARN(a->private->lfn, __VA_ARGS__)
#define ROM_ERR(a, ...) if((a->private) && (a->private->lfn)) LERR(a->private->lfn, __VA_ARGS__)

struct rom_private_s
{
    log_fn      lfn;
    bool        read_only;
};


rom_t * rom_new()
{
    rom_t * rom = (rom_t*)calloc(1, sizeof(rom_t));

    if(rom)
    {
        rom->private = (struct rom_private_s*)calloc(1, sizeof(rom_private_t));
    }

    return rom;
}



void rom_delete(rom_t * const rom)
{
    if(!rom)
        return;

    if(rom->private)
    {
        free(rom->private);
    }

    free(rom);
}



bool rom_set_log_callback(rom_t * const rom, log_fn log)
{
    if(!rom || !rom->private)
        return false;

    rom->private->lfn = log;

    return true;
}



bool rom_init(rom_t * const rom, char const * const romfile)
{
    FILE* in = NULL;
    size_t num_read = 0;

    if(!rom || !rom->private)
        return false;

    if(!romfile)
    {
        ROM_ERR(rom, "rom_init(): NULL romfile pointer");
        return false;
    }

    if((in = fopen(romfile, "rb")) == NULL)
    {
        ROM_ERR(rom, "rom_init(): failed to open romfile");
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
        ROM_ERR(rom, "rom_init(): failed to allocate rom buffer");
        fclose(in);
        return false;
    }

    /* read in the file data */
    if((num_read = fread(rom->rom, sizeof(uint8_t), rom->size, in)) != rom->size)
    {
        ROM_ERR(rom, "rom_init(); failed to read in rom file");
        free(rom->rom);
        fclose(in);
        return false;
    }

    fclose(in);

    return true;
}



bool rom_deinit(rom_t * const rom)
{
    if(!rom || !rom->private)
        return false;

    if(!rom->rom)
    {
        free(rom->rom);
        rom->rom = NULL;
    }
    else
    {
        ROM_WARN(rom, "rom_deinit(): NULL rom memory pointer");
    }

    return true;
}



bool rom_set_read_only(rom_t * const rom, bool const read_only)
{
    if(!rom || !rom->private)
        return false;

    /* store the read only setting */
    rom->private->read_only = read_only;

    return true;
}



bool rom_is_read_only(rom_t * const rom)
{
    if(!rom || !rom->private)
        return false;

    return rom->private->read_only;
}



bool rom_peek(rom_t * const rom, uint16_t const address, uint8_t * const data)
{
    if(!rom || !rom->private)
        return false;

    if(!IS_ROM_ADDRESS(address))
    {
        ROM_ERR(rom, "rom_peek(): 0x%04x out of ROM address range", address);
        return false;
    }

    if(!data)
    {
        ROM_ERR(rom, "rom_peek(): null data pointer");
        return false;
    }

    /* read the byte from the rom buffer */
    (*data) = rom->rom[(address - 0xF000)];

    return true;
}



bool rom_poke(rom_t * const rom, uint16_t const address, uint8_t const data)
{

}



/*
 * rom.c
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

#include "memmap.h"
#include "msg.h"
#include "log.h"
#include "rom.h"

struct rom_private_s
{
    msg_q_t     q;
};


bool rom_init(rom_t * const rom, char const * const romfile, msg_q_t q)
{
    FILE* in = NULL;
    size_t num_read = 0;

    if(!rom || !q)
        return false;

    /* zero out the rom struct */
    memset(rom, 0, sizeof(rom_t));

    /* allocate private struct */
    rom->private = calloc(1, sizeof(struct rom_private_s));

    /* store the msg q pointer */
    rom->private->q = q;

    if(!romfile)
    {
        LERR(rom->private->q, ROM, "rom_init(): NULL romfile pointer");
        return false;
    }

    if((in = fopen(romfile, "rb")) == NULL)
    {
        LERR(rom->private->q, ROM, "rom_init(): failed to open romfile");
        return false;
    }

    /* get the size of the file */
    fseek(in, 0, SEEK_END);
    if(ftell(in) > ROM_SIZE)
    {
        LWARN(rom->private->q, ROM, "rom_init(): rom file larger than rom memory");
    }
    fseek(in, 0, SEEK_SET);

    /* read in the file data */
    if((num_read = fread(rom->data, sizeof(uint8_t), ROM_SIZE, in)) != ROM_SIZE)
    {
        LERR(rom->private->q, ROM, "rom_init(); failed to read in rom file");
        fclose(in);
        return false;
    }

    fclose(in);

    return true;
}



bool rom_deinit(rom_t * const rom)
{
    if(!rom)
        return false;

    if(rom->private)
        free(rom->private);

    return true;
}



bool rom_peek(rom_t * const rom, uint16_t const address, uint8_t * const data)
{
    if(!rom || !rom->private)
        return false;

    if(!data)
    {
        LERR(rom->private->q, ROM, "rom_peek(): null data pointer");
        return false;
    }
    
    if(!IS_ROM_ADDRESS(address))
    {
        LERR(rom->private->q, ROM, "rom_peek(): 0x%04x out of ROM address range", address);
        return false;
    }

    /* read the byte from the rom buffer */
    (*data) = rom->data[(address - ROM_START)];

    return true;
}



bool rom_poke(rom_t * const rom, uint16_t const address, uint8_t const data)
{
    if(!rom || !rom->private)
        return false;

    LWARN(rom->private->q, ROM, "rom_poke(); writing data to 0x%04x", address);

    /* write the byte to the rom buffer */
    rom->data[(address - ROM_START)] = data;

    return true;
}



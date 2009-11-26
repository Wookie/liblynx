/*
 * mem.c
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
#include "log.h"
#include "ram.h"
#include "rom.h"
#include "mikey.h"
#include "suzy.h"
#include "mem.h"
#include "misc.h"

bool mem_init(mem_t * const m, ram_t * const ram, suzy_t * const suzy,
              mikey_t * const mikey, rom_t * const rom)
{
    if(!m)
        return false;

    /* clear out the memmap struct */
    memset(m, 0, sizeof(mem_t));

    /* store subsystem pointers */
    m->ram = ram;
    m->suzy = suzy;
    m->mikey = mikey;
    m->rom = rom;

    return true;
}


bool mem_deinit(mem_t * const m)
{
    if(!m)
        return false;

    return true;
}

bool mem_read(mem_t * const m, source_t const src, 
                 uint16_t const address, uint8_t * const data)
{
    switch(src)
    {
        case VIDEO:
        case REFRESH:
           return ram_read(m->ram, address, data);
        
        case SUZY:
           return ram_read(m->ram, address, data);

        case CPU:
            if(IS_INTVEC_ADDRESS(address) && IS_BIT_SET(m->ctrl, VECTORS_ENABLE))
            {
                return rom_read(m->rom, address, data);
            }
            else if(IS_ROM_ADDRESS(address) && IS_BIT_SET(m->ctrl, ROM_ENABLE))
            {
                return rom_read(m->rom, address, data);
            }
            else if(IS_MIKEY_ADDRESS(address) && IS_BIT_SET(m->ctrl, MIKEY_ENABLE))
            {
                return mikey_read(m->mikey, address, data);
            }
            else if(IS_SUZY_ADDRESS(address) && IS_BIT_SET(m->ctrl, SUZY_ENABLE))
            {
                return suzy_read(m->suzy, address, data);
            }
            else if(IS_RAM_ADDRESS(address))
            {
                return ram_read(m->ram, address, data);
            }
            break;
        default:
            break;
    }

    return false;
}


bool mem_write(mem_t * const m, source_t const src,
                 uint16_t const address, uint8_t const data)
{
    switch(src)
    {
        case VIDEO:
        case REFRESH:
           return ram_write(m->ram, address, data);
        
        case SUZY:
           return ram_write(m->ram, address, data);

        case CPU:
            if(IS_MIKEY_ADDRESS(address) && IS_BIT_SET(m->ctrl, MIKEY_ENABLE))
            {
                return mikey_write(m->mikey, address, data);
            }
            else if(IS_SUZY_ADDRESS(address) && IS_BIT_SET(m->ctrl, SUZY_ENABLE))
            {
                return suzy_write(m->suzy, address, data);
            }
            else if(IS_RAM_ADDRESS(address))
            {
                return ram_write(m->ram, address, data);
            }
            break;
        default:
            break;
    }

    return false;
}


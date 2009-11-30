/*
 * cpu.c
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
#include "cpu.h"
#include "65SC02.h"

struct cpu_private_s
{
    msg_q_t     q;                  /* message queue */

    int         remaining_ticks;    /* ticks remaining in current instruction */
    uint8_t     opcode;             /* opcode read from memory */
    uint16_t    address;            /* current bus address */

};


bool cpu_init(cpu_t * const cpu, msg_q_t q)
{
    if(!cpu)
        return false;

    /* clear out the cpu struct memory */
    memset(cpu, 0, sizeof(cpu_t));

    /* allocate the private memory area */
    cpu->private = calloc(1, sizeof(struct cpu_private_s));

    /* store the message queue pointer */
    cpu->private->q = q;

    return true;
}



bool cpu_deinit(cpu_t * const cpu)
{
    if(!cpu)
        return false;

    if(cpu->private)
        free(cpu->private);

    return true;
}


/****************************** OPCODE FUNCTIONS *****************************/

#if 0
bool adc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool and(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool asl(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bcc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bcs(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool beq(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bit(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bmi(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bne(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bpl(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool brk(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bvc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool bvs(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool clc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool cld(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool cli(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool clv(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool cmp(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool cpx(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool cpy(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool dec(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool dex(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool dey(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool eor(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool inc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool inx(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool iny(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool jmp(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool jsr(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool lda(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool ldx(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool ldy(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool lsr(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool nop(cpu_t * const cpu, opcode_handler_t * const params)
{

}

bool ora(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool pha(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool php(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool pla(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool plp(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool rol(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool ror(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool rti(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool rts(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sbc(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sec(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sed(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sei(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sta(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool stx(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool sty(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool tax(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool tay(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool tsx(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool txa(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool txs(cpu_t * const cpu, opcode_handler_t * const params);
{
}

bool tya(cpu_t * const cpu, opcode_handler_t * const params);
{
}


static bool _cpu_set_address_bus(cpu_t * const cpu, uint16_t const address)
{
    if(!cpu)
        return false;

    return true;
}

static bool _cpu_set_data_bus(cpu_t * const cpu, uint8_t const data)
{
    if(!cpu)
        return false;

    return true;
}

static bool _cpu_get_data_bus(cpu_t * const cpu, uint8_t * const data)
{
    if(!cpu || !data)
        return false;

    return true;
}

static bool _cpu_request_sysbus(cpu_t * const cpu)
{
    if(!cpu)
        return false;

    return true;
}
#endif


/*
 * 65SC02.h
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

#ifndef _65SC02_H_
#define _65SC02_H_

#define MAX_OPCODES (0xFF)

/* 6502 addressing modes */
typedef enum addressing_mode_e
{
    accumulator,
    absolute,
    absolute_x_indexed,
    absolute_y_indexed,
    immediate,
    implied,
    indirect,
    x_indexed_indirect,
    indirect_y_indexed,
    relative,
    zeropage,
    zeropage_x_indexed,
    zeropage_y_indexed

} addressing_mode_t;

/* flags for setting possible cycle penalties */
typedef enum cycle_penalty_e
{
    page    = 0x01,
    branch  = 0x02

} cycle_penalty_t;

/* flags for determining which flags get updated */
typedef enum flag_changes_e
{
    N   = 0x80,
    V   = 0x40,
    O   = 0x20,
    B   = 0x10,
    D   = 0x08,
    I   = 0x04,
    Z   = 0x02,
    C   = 0x01

} flag_changes_t;

/* opcode handler function parameters */
typedef struct opcode_definition_s
{
    addressing_mode_t   addr_mode;
    int                 size;
    int                 cycles;
    cycle_penalty_t     penalty;
    flag_changes_t      flag_changes;

} opcode_definition_t;

/* opcode handler function signature */
typedef bool (*cpu_state_change)(cpu_t * const cpu, opcode_definition_t * const defs);

/* opcode handler definitions */
typedef struct opcode_handler_s
{
    cpu_state_change    cfn;
    opcode_definition_t defs;

} opcode_hander_t;

/* opcode handler functions */
bool adc(cpu_t * const cpu, opcode_handler_t * const params);
bool and(cpu_t * const cpu, opcode_handler_t * const params);
bool asl(cpu_t * const cpu, opcode_handler_t * const params);
bool bcc(cpu_t * const cpu, opcode_handler_t * const params);
bool bcs(cpu_t * const cpu, opcode_handler_t * const params);
bool beq(cpu_t * const cpu, opcode_handler_t * const params);
bool bit(cpu_t * const cpu, opcode_handler_t * const params);
bool bmi(cpu_t * const cpu, opcode_handler_t * const params);
bool bne(cpu_t * const cpu, opcode_handler_t * const params);
bool bpl(cpu_t * const cpu, opcode_handler_t * const params);
bool brk(cpu_t * const cpu, opcode_handler_t * const params);
bool bvc(cpu_t * const cpu, opcode_handler_t * const params);
bool bvs(cpu_t * const cpu, opcode_handler_t * const params);
bool clc(cpu_t * const cpu, opcode_handler_t * const params);
bool cld(cpu_t * const cpu, opcode_handler_t * const params);
bool cli(cpu_t * const cpu, opcode_handler_t * const params);
bool clv(cpu_t * const cpu, opcode_handler_t * const params);
bool cmp(cpu_t * const cpu, opcode_handler_t * const params);
bool cpx(cpu_t * const cpu, opcode_handler_t * const params);
bool cpy(cpu_t * const cpu, opcode_handler_t * const params);
bool dec(cpu_t * const cpu, opcode_handler_t * const params);
bool dex(cpu_t * const cpu, opcode_handler_t * const params);
bool dey(cpu_t * const cpu, opcode_handler_t * const params);
bool eor(cpu_t * const cpu, opcode_handler_t * const params);
bool inc(cpu_t * const cpu, opcode_handler_t * const params);
bool inx(cpu_t * const cpu, opcode_handler_t * const params);
bool iny(cpu_t * const cpu, opcode_handler_t * const params);
bool jmp(cpu_t * const cpu, opcode_handler_t * const params);
bool jsr(cpu_t * const cpu, opcode_handler_t * const params);
bool lda(cpu_t * const cpu, opcode_handler_t * const params);
bool ldx(cpu_t * const cpu, opcode_handler_t * const params);
bool ldy(cpu_t * const cpu, opcode_handler_t * const params);
bool lsr(cpu_t * const cpu, opcode_handler_t * const params);
bool nop(cpu_t * const cpu, opcode_handler_t * const params);
bool ora(cpu_t * const cpu, opcode_handler_t * const params);
bool pha(cpu_t * const cpu, opcode_handler_t * const params);
bool php(cpu_t * const cpu, opcode_handler_t * const params);
bool pla(cpu_t * const cpu, opcode_handler_t * const params);
bool plp(cpu_t * const cpu, opcode_handler_t * const params);
bool rol(cpu_t * const cpu, opcode_handler_t * const params);
bool ror(cpu_t * const cpu, opcode_handler_t * const params);
bool rti(cpu_t * const cpu, opcode_handler_t * const params);
bool rts(cpu_t * const cpu, opcode_handler_t * const params);
bool sbc(cpu_t * const cpu, opcode_handler_t * const params);
bool sec(cpu_t * const cpu, opcode_handler_t * const params);
bool sed(cpu_t * const cpu, opcode_handler_t * const params);
bool sei(cpu_t * const cpu, opcode_handler_t * const params);
bool sta(cpu_t * const cpu, opcode_handler_t * const params);
bool stx(cpu_t * const cpu, opcode_handler_t * const params);
bool sty(cpu_t * const cpu, opcode_handler_t * const params);
bool tax(cpu_t * const cpu, opcode_handler_t * const params);
bool tay(cpu_t * const cpu, opcode_handler_t * const params);
bool tsx(cpu_t * const cpu, opcode_handler_t * const params);
bool txa(cpu_t * const cpu, opcode_handler_t * const params);
bool txs(cpu_t * const cpu, opcode_handler_t * const params);
bool tya(cpu_t * const cpu, opcode_handler_t * const params);

/* table of opcode handler and definitions */
opcode_handler_t const opcodes[MAX_OPCODES] = {

/*    VALUE       OP     ADDR MODE           SZ  CYC PNLTY    N | V | B | D | I | Z | C */
/*======================================================================================*/
    /* 0x00 */  { brk, { implied,            1,  7,  0,     ( 0 | 0 | 0 | 0 | I | 0 | 0 )}},
    /* 0x01 */  { ora, { x_indexed_indirect, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x02 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},   
    /* 0x03 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},   
    /* 0x04 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x05 */  { ora, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x06 */  { asl, { zeropage,           2,  5,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x07 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},   
    /* 0x08 */  { php, { implied,            1,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x09 */  { ora, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x0A */  { asl, { accumulator,        1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x0B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x0C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x0D */  { ora, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x0E */  { asl, { absolute,           3,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x0F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x10 */  { bpl, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}}, 
    /* 0x11 */  { ora, { indirect_y_indexed, 2,  5,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x12 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x13 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x14 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x15 */  { ora, { zeropage_x_indexed  2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x16 */  { asl, { zeropage_x_indexed  2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x17 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x18 */  { clc, { implied             1,  2,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | C )}},
    /* 0x19 */  { ora, { absolute_y_indexed  3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x1A */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x1B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x1C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x1D */  { ora, { absolute_x_indexed  3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x1E */  { asl, { absolute_x_indexed  3,  7,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x1F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x20 */  { jsr, { absolute,           3,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x21 */  { and, { x_indexed_indirect  2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x22 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x23 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x24 */  { bit, { zeropage,           2,  3,  0,     ( N | V | 0 | 0 | 0 | Z | 0 )}},
    /* 0x25 */  { and, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x26 */  { rol, { zeropage,           2,  5,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x27 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x28 */  { plp, { implied,            1,  4,  0,     ( N | V | B | D | I | Z | C )}},
    /* 0x29 */  { and, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x2A */  { rol, { accumulator,        1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x2B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x2C */  { bit, { absolute,           3,  4,  0,     ( N | V | 0 | 0 | 0 | Z | 0 )}},
    /* 0x2D */  { and, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x2E */  { rol, { absolute,           3,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x2F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x30 */  { bmi, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x31 */  { and, { indirect_y_indexed, 2,  5,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x32 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x33 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x34 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x35 */  { and, { zeropage_x_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x36 */  { rol, { zeropage_x_indexed, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x37 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x38 */  { sec, { implied,            1,  2,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | C )}},
    /* 0x39 */  { and, { absolute_y_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x3A */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x3B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x3C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x3D */  { and, { absolute_x_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x3E */  { rol, { absolute_x_indexed, 3,  7,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x3F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x40 */  { rti, { implied,            1,  6,  0,     ( N | V | B | D | I | Z | C )}},
    /* 0x41 */  { eor, { x_indexed_indirect, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x42 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x43 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x44 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x45 */  { eor, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x46 */  { lsr, { zeropage,           2,  5,  0,     ( 0 | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x47 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x48 */  { pha, { implied,            1,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x49 */  { eor, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x4A */  { lsr, { accumulator,        1,  2,  0,     ( 0 | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x4B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x4C */  { jmp, { absolute,           3,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x4D */  { eor, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x4E */  { lsr, { absolute,           3,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x4F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x50 */  { bvc, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x51 */  { eor, { indirect_y_indexed, 2,  5,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x52 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x53 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x54 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x55 */  { eor, { zeropage_x_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x56 */  { lsr, { zeropage_x_indexed, 2,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x57 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x58 */  { cli, { implied,            1,  2,  0,     ( 0 | 0 | 0 | 0 | I | 0 | 0 )}},
    /* 0x59 */  { eor, { absolute_y_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x5A */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x5B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x5C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x5D */  { eor, { absolute_x_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x5E */  { lsr, { absolute_x_indexed, 3,  7,  0,     ( 0 | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x5F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x60 */  { rts, { implied,            1,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x61 */  { adc, { x_indexed_indirect, 2,  6,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x62 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x63 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x64 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x65 */  { adc, { zeropage,           2,  3,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x66 */  { ror, { zeropage,           2,  5,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x67 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x68 */  { pla, { implied,            1,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x69 */  { adc, { immediate,          2,  2,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x6A */  { ror, { accumulator,        1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x6B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x6C */  { jmp, { indirect,           3,  5,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x6D */  { adc, { absolute,           3,  4,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x6E */  { ror, { absolute,           3,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x6F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x70 */  { bvs, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x71 */  { adc, { indirect_y_indexed, 2,  5,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x72 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x73 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x74 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x75 */  { adc, { zeropage_x_indexed, 2,  4,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x76 */  { ror, { zeropage_x_indexed, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x77 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x78 */  { sei, { implied,            1,  2,  0,     ( 0 | 0 | 0 | 0 | I | 0 | 0 )}},
    /* 0x79 */  { adc, { absolute_y_indexed, 3,  4,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x7A */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x7B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x7C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x7D */  { adc, { absolute_x_indexed, 3,  7,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0x7E */  { ror, { absolute_x_indexed, 3,  7,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0x7F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x80 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x81 */  { sta, { x_indexed_indirect, 2,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x82 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x83 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x84 */  { sty, { zeropage,           2,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x85 */  { sta, { zeropage,           2,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x86 */  { stx, { zeropage,           2,  3,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x87 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x88 */  { dey, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x89 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x8A */  { txa, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x8B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x8C */  { sty, { absolute,           3,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x8D */  { sta, { absolute,           3,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x8E */  { stx, { absolute,           3,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x8F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x90 */  { bcc, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x91 */  { sta, { indirect_y_indexed, 2,  6,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x92 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x93 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x94 */  { sty, { zeropage_x_indexed, 2,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x95 */  { sta, { zeropage_x_indexed, 2,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x96 */  { stx, { zeropage_y_indexed, 2,  4,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x97 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x98 */  { tya, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x99 */  { sta, { absolute_y_indexed, 3,  5,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x9A */  { txs, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0x9B */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x9C */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x9D */  { sta, { absolute_x_indexed, 3,  5,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x9E */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0x9F */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xA0 */  { ldy, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA1 */  { lda, { x_indexed_indirect, 2,  6,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA2 */  { ldx, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xA4 */  { ldy, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA5 */  { lda, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA6 */  { ldx, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xA8 */  { tay, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xA9 */  { lda, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xAA */  { tax, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xAB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xAC */  { ldy, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xAD */  { lda, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xAE */  { ldx, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xAF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB0 */  { bcs, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB1 */  { lda, { indirect_y_indexed, 2,  5,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xB2 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB4 */  { ldy, { zeropage_x_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xB5 */  { lda, { zeropage_x_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xB6 */  { ldx, { zeropage_y_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xB7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB8 */  { clv, { implied,            1,  2,  0,     ( 0 | V | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xB9 */  { lda, { absolute_y_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xBA */  { tsx, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xBB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xBC */  { ldy, { absolute_x_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xBD */  { lda, { absolute_x_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xBE */  { ldx, { absolute_y_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xBF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xC0 */  { cpy, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xC1 */  { cmp, { x_indexed_indirect, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xC2 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xC3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xC4 */  { cpy, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xC5 */  { cmp, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xC6 */  { dec, { zeropage,           2,  5,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xC7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xC8 */  { iny, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xC9 */  { cmp, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xCA */  { dex, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xCB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xCC */  { cpy, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xCD */  { cmp, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xCE */  { dec, { absolute,           3,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xCF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD0 */  { bne, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD1 */  { cmp, { indirect_y_indexed, 2,  5,  page,  ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xD2 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD4 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD5 */  { cmp, { zeropage_x_indexed, 2,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xD6 */  { dec, { zeropage_x_indexed, 3,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xD7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xD8 */  { cld, { implied,            1,  2,  0,     ( 0 | 0 | 0 | D | 0 | 0 | 0 )}},
    /* 0xD9 */  { cmp, { absolute_y_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xDA */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xDB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xDC */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xDD */  { cmp, { absolute_x_indexed, 3,  4,  page,  ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xDE */  { dec, { absolute_x_indexed, 2,  7,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xDF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xE0 */  { cpx, { immediate,          2,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xE1 */  { sbc, { x_indexed_indirect, 2,  6,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xE2 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xE3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xE4 */  { cpx, { zeropage,           2,  3,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xE5 */  { sbc, { zeropage,           2,  3,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xE6 */  { inc, { zeropage,           2,  5,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xE7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xE8 */  { inx, { implied,            1,  2,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xE9 */  { sbc, { immediate,          2,  2,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xEA */  { nop, { implied,            1,  2,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xEB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xEC */  { cpx, { absolute,           3,  4,  0,     ( N | 0 | 0 | 0 | 0 | Z | C )}},
    /* 0xED */  { sbc, { absolute,           3,  4,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xEE */  { inc, { absolute,           3,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xEF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF0 */  { beq, { relative,           2,  2,  branch,( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF1 */  { sbc, { indirect_y_indexed, 2,  5,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xF2 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF3 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF4 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF5 */  { sbc, { zeropage_x_indexed, 2,  4,  0,     ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xF6 */  { inc, { zeropage_x_indexed, 2,  6,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xF7 */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xF8 */  { sed, { implied,            1,  2,  0,     ( 0 | 0 | 0 | D | 0 | 0 | 0 )}},
    /* 0xF9 */  { sbc, { absolute_y_indexed, 3,  4,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xFA */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xFB */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xFC */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}},
    /* 0xFD */  { sbc, { absolute_x_indexed, 3,  4,  page,  ( N | V | 0 | 0 | 0 | Z | C )}},
    /* 0xFE */  { inc, { absolute_x_indexed, 3,  7,  0,     ( N | 0 | 0 | 0 | 0 | Z | 0 )}},
    /* 0xFF */  { NULL,{ 0,                  0,  0,  0,     ( 0 | 0 | 0 | 0 | 0 | 0 | 0 )}}
};

#endif


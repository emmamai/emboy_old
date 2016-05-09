#ifndef _OPCODES_H_

/*
This file breaks normal function naming conventions, as
my normal convention is very hard to read with opcode-based
function names.
*/

typedef struct opcode_s {
	char* name;
	void (*run)( cpuState_t* cpu, mmapState_t* mmap );
	char* (*disasm)( cpuState_t* cpu, mmapState_t* mmap );
} opcode_t;

void no_opcode( cpuState_t *cpu, mmapState_t *mmap );
char* no_op_display( cpuState_t *cpu, mmapState_t *mmap );

void op_nop( cpuState_t* cpu, mmapState_t* mmap );			// 0x00 NOP
void op_ld_bc_d16( cpuState_t* cpu, mmapState_t* mmap );	// 0x01 LD BC, d16
void op_dec_b( cpuState_t* cpu, mmapState_t* mmap );		// 0x05 DEC B
void op_ld_b_d8( cpuState_t* cpu, mmapState_t* mmap );		// 0x06 LD B, d8
void op_dec_bc( cpuState_t* cpu, mmapState_t* mmap );		// 0x0B DEC BC
void op_inc_c( cpuState_t* cpu, mmapState_t* mmap );		// 0x0C INC C
void op_dec_c( cpuState_t* cpu, mmapState_t* mmap );		// 0x0D DEC C
void op_ld_c_d8( cpuState_t* cpu, mmapState_t* mmap );		// 0x0E LD C, d8
void op_jr_nz_r8( cpuState_t* cpu, mmapState_t* mmap );		// 0x20 JR NZ r8
void op_ld_hl_d16( cpuState_t* cpu, mmapState_t* mmap );	// 0x21 LD HL, d16
void op_ld_hlinc_a( cpuState_t* cpu, mmapState_t* mmap );	// 0x22 LD (HL+), A
void op_ld_a_hlinc( cpuState_t* cpu, mmapState_t* mmap );	// 0x2A LD A, (HL+)
void op_ld_sp_d16( cpuState_t* cpu, mmapState_t* mmap );	// 0x31 LD SP, d16
void op_ld_hldec_a( cpuState_t* cpu, mmapState_t* mmap );	// 0x32 LD (HL-), A
void op_ld_hl_d8( cpuState_t* cpu, mmapState_t* mmap );		// 0x36 LD (HL), d8
void op_ld_a_d8( cpuState_t* cpu, mmapState_t* mmap );		// 0x3E LD A, d8
void op_ld_hl_a( cpuState_t* cpu, mmapState_t* mmap );		// 0x77 LD (HL), A
void op_ld_a_b( cpuState_t* cpu, mmapState_t* mmap );		// 0x78 LD A, B
void op_xor_a( cpuState_t* cpu, mmapState_t* mmap );		// 0xAF XOR A
void op_or_c( cpuState_t* cpu, mmapState_t* mmap );			// 0xB1 OR C
void op_jp_a16( cpuState_t* cpu, mmapState_t* mmap );		// 0xC3 JP Aa16
void op_call_a16( cpuState_t* cpu, mmapState_t* mmap );		// 0xCD CALL a16
void op_ldh_a8_a( cpuState_t* cpu, mmapState_t* mmap );		// 0xE0 LDH (a8), A
void op_ld_cref_a( cpuState_t* cpu, mmapState_t* mmap );	// 0xE2 LD (C), A
void op_ld_a16_a( cpuState_t* cpu, mmapState_t* mmap );		// 0xEA LD (a16), A
void op_ldh_a_a8( cpuState_t* cpu, mmapState_t* mmap );		// 0xF0 LDH A, (a8)
void op_ld_a_a16( cpuState_t* cpu, mmapState_t* mmap );		// 0xFA LD A, (a16)
void op_cp_d8( cpuState_t* cpu, mmapState_t* mmap );		// 0xFE CP d8

#include "opcode_table.h"

#define _OPCODES_H_
#endif
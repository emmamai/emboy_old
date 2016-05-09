#include "cartridge.h"
#include "memmap.h"
#include "cpu.h"
#include "gui.h"

/*
This file breaks normal function naming conventions, as
my normal convention is very hard to read with opcode-based
function names.
*/
void no_opcode( cpuState_t* cpu, mmapState_t* mmap ) {
	OnBreak();
}

char * no_op_display( cpuState_t* cpu, mmapState_t* mmap ) {
	return "INVALID_OP";
}

// 0x00 NOP
void op_nop( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}


// 0x01 LD BC, 16
void op_ld_bc_d16( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->b = Mmap_Peek( mmap, *cpu->pc + 2 );
	*cpu->c = Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 3;
	*cpu->cycles_until_next_instruction = 12;
}

//0x05 DEC B
void op_dec_b( cpuState_t* cpu, mmapState_t* mmap ) {
	CPU_UpdateHFlag_Subtract( cpu, *cpu->b, 1 );
	*cpu->b = *cpu->b - 1;
	CPU_UpdateZFlag( cpu, *cpu->b );
	CPU_SetNFlag( cpu );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0x06 LD B, d8
void op_ld_b_d8( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->b = Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 8;
}

//0x0B DEC BC
void op_dec_bc( cpuState_t* cpu, mmapState_t* mmap ) {
	CPU_UpdateHFlag_Subtract( cpu, *cpu->b, 1 );
	*cpu->bc = *cpu->bc - 1;
	CPU_UpdateZFlag( cpu, *cpu->bc );
	CPU_SetNFlag( cpu );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0x0C INC C
void op_inc_c( cpuState_t* cpu, mmapState_t* mmap ) {
	CPU_UpdateHFlag_Add( cpu, *cpu->c, 1 );
	*cpu->c = *cpu->c + 1;
	CPU_UpdateZFlag( cpu, *cpu->c );

	CPU_ClearNFlag( cpu );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0x0D DEC C
void op_dec_c( cpuState_t* cpu, mmapState_t* mmap ) {
	CPU_UpdateHFlag_Subtract( cpu, *cpu->c, 1 );
	*cpu->c = *cpu->c - 1;
	CPU_UpdateZFlag( cpu, *cpu->c );
	CPU_SetNFlag( cpu );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0x0E LD C, d8
void op_ld_c_d8( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->c = Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 8;
}

//0x20 JR NZ r8
void op_jr_nz_r8( cpuState_t* cpu, mmapState_t *mmap ) {
	if ( CPU_GetZFlag( cpu ) == 0 ) {
		char rel = (char)Mmap_Peek( mmap, *cpu->pc + 1 );

		*cpu->pc = *cpu->pc + rel + 2;
		*cpu->cycles_until_next_instruction = 12;
	} else {
		*cpu->pc = *cpu->pc + 2;
		*cpu->cycles_until_next_instruction = 8;
	}
}

// 0x21 LD HL, d16
void op_ld_hl_d16( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->h = Mmap_Peek( mmap, *cpu->pc + 2 );
	*cpu->l = Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 3;
	*cpu->cycles_until_next_instruction = 12;
}

// 0x22 LD (HL+), A
void op_ld_hlinc_a( cpuState_t* cpu, mmapState_t* mmap ) {
	Mmap_Poke( mmap, ++*cpu->hl, *cpu->a );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 8;
}

// 0x2A LD A, (HL+)
void op_ld_a_hlinc( cpuState_t* cpu, mmapState_t *mmap ) {
	*cpu->a = Mmap_Peek( mmap, *cpu->hl );

	*cpu->hl = *cpu->hl + 1;

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 8;
}

// 0x31 LD SP, d16
void op_ld_sp_d16( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->sp = 0;
	*cpu->sp += Mmap_Peek( mmap, *cpu->pc + 2 ) << 8;
	*cpu->sp += Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 3;
	*cpu->cycles_until_next_instruction = 12;
}

// 0x32 LD (HL-),
void op_ld_hldec_a( cpuState_t* cpu, mmapState_t* mmap ) {
	Mmap_Poke( mmap, *cpu->hl, *cpu->a );

	*cpu->hl = *cpu->hl - 1;

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 8;
}

// 0x36 LD (HL), d8
void op_ld_hl_d8( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned char val = Mmap_Peek( mmap, *cpu->pc + 1 );

	Mmap_Poke( mmap, *cpu->hl, val );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 12;
}

// 0x3E LD A, d8
void op_ld_a_d8( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->a = Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 8;
}

// 0x77 LD (HL), A
void op_ld_hl_a( cpuState_t* cpu, mmapState_t* mmap ) {
	Mmap_Poke( mmap, *cpu->hl, *cpu->a );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 8;
}

// 0x78 LD A, B
void op_ld_a_b( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->a = cpu->b;

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0xAF XOR A
void op_xor_a( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->a = 0;
	*cpu->f = 0x80;

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0xB1 OR C
void op_or_c( cpuState_t* cpu, mmapState_t* mmap ) {
	*cpu->a = *cpu->a | *cpu->c;
	*cpu->f = 0x00;
	CPU_UpdateZFlag( cpu, *cpu->a );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 4;
}

// 0xC3 JP a16
void op_jp_a16( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short new_address = Mmap_Peek( mmap, *cpu->pc + 2 ) << 8;
	new_address += Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->pc = new_address;
	*cpu->cycles_until_next_instruction = 16;
}

// 0xCD CALL a16
void op_call_a16( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short new_address = Mmap_Peek( mmap, *cpu->pc + 2 ) << 8;
	new_address += Mmap_Peek( mmap, *cpu->pc + 1 );

	CPU_PushWord( cpu, mmap, *cpu->pc + 3 );

	*cpu->pc = new_address;
	*cpu->cycles_until_next_instruction = 24;
}

// 0xE0 LDH (a8), A
void op_ldh_a8_a( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short address = Mmap_Peek( mmap, *cpu->pc + 1 ) + 0xFF00;
	Mmap_Poke( mmap, address, *cpu->a );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 12;
}

// 0xE2 LD (C), A
void op_ld_cref_a( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short address = *cpu->c + 0xFF00;
	Mmap_Poke( mmap, address, *cpu->a );

	*cpu->pc = *cpu->pc + 1;
	*cpu->cycles_until_next_instruction = 8;
}

// 0xEA LD (a16), A
void op_ld_a16_a( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short address = Mmap_Peek( mmap, *cpu->pc + 2 ) << 8;
	address += Mmap_Peek( mmap, *cpu->pc + 1 );

	Mmap_Poke( mmap, address, *cpu->a );

	*cpu->pc = *cpu->pc + 3;
	*cpu->cycles_until_next_instruction = 16;
}

// 0xF0 LDH A, (a8)
void op_ldh_a_a8( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short address = Mmap_Peek( mmap, *cpu->pc + 1 ) + 0xFF00;
	*cpu->a = Mmap_Peek( mmap, address );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 12;
}

// 0xFA LD A, (a16)
void op_ld_a_a16( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned short address = Mmap_Peek( mmap, *cpu->pc + 2 ) << 8;
	address += Mmap_Peek( mmap, *cpu->pc + 1 );

	*cpu->a = Mmap_Peek( mmap, address );

	*cpu->pc = *cpu->pc + 3;
	*cpu->cycles_until_next_instruction = 16;
}

// 0xFE CP d8
void op_cp_d8( cpuState_t* cpu, mmapState_t* mmap ) {
	unsigned char op = Mmap_Peek( mmap, *cpu->pc + 1 );

	CPU_UpdateZFlag( cpu, (*cpu->a) - op );
	CPU_UpdateHFlag_Subtract( cpu, *cpu->a, op );
	CPU_SetNFlag( cpu );
	CPU_UpdateCFlag_Subtract( cpu, *cpu->a, op );

	*cpu->pc = *cpu->pc + 2;
	*cpu->cycles_until_next_instruction = 8;
}
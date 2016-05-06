#include <stdio.h>
#include <stdlib.h>

#include "cartridge.h"
#include "memmap.h"
#include "cpu.h"
#include "opcodes.h"


cpuState_t * CPU_Init() {
	cpuState_t * cpu = malloc( sizeof( cpuState_t ) );

	cpu->sp = malloc( sizeof( short ) );
	cpu->pc = malloc( sizeof( short ) );

	void * reg_block = malloc( sizeof( short ) * 4 );

	cpu->af = reg_block;
	cpu->bc = reg_block + sizeof( short );
	cpu->de = reg_block + ( sizeof( short ) * 2 );
	cpu->hl = reg_block + ( sizeof( short ) * 3 );

	cpu->cycles_until_next_instruction = malloc( sizeof( char ) );
	*cpu->cycles_until_next_instruction = 1;

	cpu->a = (unsigned char *)cpu->af;
	cpu->b = (unsigned char *)cpu->bc;
	cpu->d = (unsigned char *)cpu->de;
	cpu->h = (unsigned char *)cpu->hl;
	cpu->f = (unsigned char *)cpu->af;
	cpu->c = (unsigned char *)cpu->bc;
	cpu->e = (unsigned char *)cpu->de;
	cpu->l = (unsigned char *)cpu->hl;

	//fix high byte addresses
	cpu->a++;
	cpu->b++;
	cpu->d++;
	cpu->h++;

	*cpu->pc = 0;
	*cpu->sp = 0xFFFF;
	*cpu->af = 0;
	*cpu->bc = 0;
	*cpu->de = 0;
	*cpu->hl = 0;

	return cpu;
}

int CPU_RunClockCycle( cpuState_t* cpu, mmapState_t* mmap ) {
	if ( --*cpu->cycles_until_next_instruction == 0 ) {
		unsigned char opcode = Mmap_Peek( mmap, *cpu->pc );

		printf( "[CPU] 0x%04x:0x%02x | %s\n", *cpu->pc, opcode, opcodes[opcode].name );
		opcodes[opcode].run( cpu, mmap );
		return 1;
	}
	return 0;
}



/*======================
Functions for directly manipulating CPU flags
======================*/

unsigned char CPU_GetCFlag( cpuState_t* cpu ) {
	return *cpu->f & 0x10;
}
unsigned char CPU_GetHFlag( cpuState_t* cpu ) {
	return *cpu->f & 0x20;
}
unsigned char CPU_GetNFlag( cpuState_t* cpu ) {
	return *cpu->f & 0x40;
}
unsigned char CPU_GetZFlag( cpuState_t* cpu ) {
	return *cpu->f & 0x80;
}
void CPU_SetCFlag( cpuState_t* cpu ) {
	*cpu->f |= 0x10;
}
void CPU_SetHFlag( cpuState_t* cpu ) {
	*cpu->f |= 0x20;
}
void CPU_SetNFlag( cpuState_t* cpu ) {
	*cpu->f |= 0x40;
}
void CPU_SetZFlag( cpuState_t* cpu ) {
	*cpu->f |= 0x80;
}
void CPU_ClearCFlag( cpuState_t* cpu ) {
	*cpu->f &= 0xEF;
}
void CPU_ClearHFlag( cpuState_t* cpu ) {
	*cpu->f &= 0xDF;
}
void CPU_ClearNFlag( cpuState_t* cpu ) {
	*cpu->f &= 0xBF;
}
void CPU_ClearZFlag( cpuState_t* cpu )  {
	*cpu->f &= 0x7F;
}

/*======================
Functions for automatically manipulating CPU flags
======================*/

void CPU_UpdateZFlag( cpuState_t *cpu, unsigned char result ) {
	if( result == 0 ) {
		CPU_SetZFlag( cpu );
	} else {
		CPU_ClearZFlag( cpu );
	}
}

void CPU_UpdateHFlag_Subtract( cpuState_t* cpu, unsigned char dest, unsigned char operand ) {
	if ( CPU_CheckHalfCarry_Subtract( *cpu->b, 1 ) == 0 ) {
		CPU_ClearHFlag( cpu );
	} else {
		CPU_SetHFlag( cpu );
	}
}

void CPU_UpdateHFlag_Add( cpuState_t* cpu, unsigned char dest, unsigned char operand ) {
	if ( CPU_CheckHalfCarry_Add( *cpu->b, 1 ) == 0 ) {
		CPU_ClearHFlag( cpu );
	} else {
		CPU_SetHFlag( cpu );
	}
}

unsigned char CPU_CheckHalfCarry_Subtract( unsigned char dest, unsigned char operand ) {
	if ( (dest & 0x0F) - (operand & 0x0F) < 0 ) {
		return 1;
	} else {
		return 0;
	}
}

unsigned char CPU_CheckHalfCarry_Add( unsigned char dest, unsigned char operand ) {
	if ( ( dest & 0x0F ) + ( operand & 0x0F) > 0x0F ) {
		return 1;
	} else {
		return 0;
	}
}

void CPU_UpdateCFlag_Subtract( cpuState_t* cpu, unsigned char dest, unsigned char operand ) {
	if ( dest < operand ) {
		CPU_SetCFlag( cpu );
	} else {
		CPU_ClearCFlag( cpu );
	}
}

void CPU_UpdateCFlag_Add( cpuState_t *cpu, unsigned char dest, unsigned char operand ) {
	int result = dest;
	result = result + operand;
	if ( result > 0xFF ) {
		CPU_SetCFlag( cpu );
	} else {
		CPU_ClearCFlag( cpu );
	}
}

void CPU_PushByte( cpuState_t* cpu, mmapState_t* mmap, unsigned char value ) {
	Mmap_Poke( mmap, *cpu->sp, value );
	*cpu->sp = *cpu->sp - 1;
}

void CPU_PushWord( cpuState_t* cpu, mmapState_t* mmap, unsigned short value ) {
	unsigned char high_byte = (unsigned char)( value >> 8 );
	unsigned char low_byte = (unsigned char)( value & 0x00FF );

	//Yes, the Z80 is little endian. Keep in mind, stack grows down.
	//Pushing high then low ends up in little endian order.
	//The real Z80 effectively decrements SP by two, then does
	// an LD (SP), nn.
	CPU_PushByte( cpu, mmap, high_byte );
	CPU_PushByte( cpu, mmap, low_byte );
}
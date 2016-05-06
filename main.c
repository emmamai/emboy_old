#include <stdio.h>
#include <stdlib.h>

#include "cartridge.h"
#include "memmap.h"
#include "cpu.h"


cartridge_t* cart;
cpuState_t* cpu;
mmapState_t* mmap;

void SetStatupState( cpuState_t *cpu ) {
	*cpu->af = 0x01b0;
	*cpu->bc = 0x0013;
	*cpu->de = 0x00d8;
	*cpu->hl = 0x014d;
	*cpu->sp = 0xfffe;
	*cpu->pc = 0x100;
}

int RunClockCycle( cpuState_t* cpu, mmapState_t* mmap ) {
	LCD_RunClockCycle( mmap );
	return CPU_RunClockCycle( cpu, mmap );
}

int main( int argc, char **argv ) {
	if ( argc < 2 ) {
		printf( "Usage: %s filename\n", argv[0] );
		return 1;
	}

	cart = Cart_Load( argv[1] );
	if ( !cart ) {
		return 1;
	}

	cpu = CPU_Init();
	SetStatupState( cpu );
	

	mmap = Mmap_Init();
	mmap->cart = cart;

	LCD_Init( mmap );

	GUI_Init( &argc, &argv );

	GUI_MainLoop( cpu, mmap );

	GUI_Shutdown();

	return 0;
}
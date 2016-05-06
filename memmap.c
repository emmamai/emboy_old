#include <stdio.h>
#include <stdlib.h>

#include "cartridge.h"
#include "memmap.h"

mmapState_t* Mmap_Init( cartridge_t* cart ) {
	mmapState_t *mmap = malloc( sizeof( mmapState_t ) );

	mmap->cart = cart;
	mmap->vram = malloc( 16384 );
	mmap->wram = malloc( 32768 );
	mmap->oam = malloc( 0xA0 );
	mmap->hram = malloc( 63 );

	mmap->wram_bank = 0;

	return mmap;
}

extern unsigned int lcd_mode_cycle_count;

//Might not need this, but just to be safe, this is a separate
//function that will NOT emulate anything that might happen when
//reading an address beyond obtaining the value that is present
unsigned char Mmap_PeekConst( const mmapState_t* mmap, unsigned short addr ) {
	if ( !mmap ) {
		return 0;
	}
	if ( addr < 0x4000 && mmap->cart->buffer_size >= 16384 ) { //Rom bank 00
		return mmap->cart->buffer[addr];
	} else if ( addr < 0x8000 && mmap->cart->buffer_size >= 32768 ) { //Switchable, rom banks 01-NN
		return mmap->cart->buffer[addr + ( mmap->cart->rom_bank_number * 16384 )];
	} else if ( addr < 0xA000 ) { //VRAM
		return mmap->vram[(addr - 0x8000) + (mmap->vram_bank * 8192)];
	} else if ( addr < 0xC000 ) { //Switchable, external ram banks 00-NN, if any
		printf( "[MEM] Read from external RAM location - not implemented yet\n" );
		return 0; //Not emulated yet!
	} else if ( addr < 0xD000 ) { //Work RAM, bank 00
		return mmap->wram[addr - 0xC000];
	} else if ( addr < 0xE000 ) { //Work RAM, bank 01, or switchable 01-07 if CGB
		return mmap->wram[( addr - 0xC000 ) + (mmap->wram_bank)];
	} else if ( addr < 0xF000 ) { //Echo of WRAM bank 00
		return mmap->wram[addr - 0xE000];
	} else if ( addr < 0xFE00 ) { //Echo of WRAM bank 01/01-07
		return mmap->wram[( addr - 0xE000 ) + (mmap->wram_bank)];
	} else if ( addr < 0xFEA0 ) { //Sprite attribute table (OAM)
		return mmap->oam[addr - 0xFE00];
	} else if ( addr < 0xFF00 ) { //Invalid
		printf( "[MEM] Read from invalid memory region 0xFF00-0xFF7F\n" );
		return 0;
	} else if ( addr == 0xFF44 ) {
		printf( "[MEM] Read from LY Register (LY:%i, count:%i)\n", mmap->reg_ly, lcd_mode_cycle_count );
		return mmap->reg_ly;
	} else if ( addr < 0xFF80 ) { //IO ports
		printf( "[MEM] Read from I/O port address %4x - not implemented\n", addr );
		return 0; //Not emulated yet!
	} else if ( addr < 0xFFFE ) {
		return mmap->hram[addr - 0xFF80];
	} else {
		return 0;
	}
}

unsigned char Mmap_Peek( mmapState_t* mmap, unsigned short addr ) {
	return Mmap_PeekConst( mmap, addr );
}

void Mmap_Poke( mmapState_t* mmap, unsigned short addr, unsigned char value ) {
if ( !mmap ) {
		return;
	}
	if ( addr < 0x4000 && mmap->cart->buffer_size >= 16384 ) { //Rom bank 00
		//mmap->cart->buffer[addr];
		printf( "[MEM] Write to cart ROM, lower bank - not implemented\n" );
	} else if ( addr < 0x8000 && mmap->cart->buffer_size >= 32768 ) { //Switchable, rom banks 01-NN
		//mmap->cart->buffer[addr + ( mmap->cart->rom_bank_number * 16384 )];
		printf( "[MEM] Write to cart ROM, upper bank - not implemented\n" );
	} else if ( addr < 0xA000 ) { //VRAM
		mmap->vram[(addr - 0x8000) + (mmap->vram_bank * 8192)] = value;
	} else if ( addr < 0xC000 ) { //Switchable, external ram banks 00-NN, if any
		printf( "[MEM] Write to external RAM location - not implemented\n" );
	} else if ( addr < 0xD000 ) { //Work RAM, bank 00
		mmap->wram[addr - 0xC000] = value;
	} else if ( addr < 0xE000 ) { //Work RAM, bank 01, or switchable 01-07 if CGB
		mmap->wram[( addr - 0xC000 ) + (mmap->wram_bank)] = value;
	} else if ( addr < 0xF000 ) { //Echo of WRAM bank 00
		mmap->wram[addr - 0xE000] = value;
	} else if ( addr < 0xFE00 ) { //Echo of WRAM bank 01/01-07
		mmap->wram[( addr - 0xE000 ) + (mmap->wram_bank)] = value;
	} else if ( addr < 0xFEA0 ) { //Sprite attribute table (OAM)
		mmap->oam[addr - 0xFE00] = value;
	} else if ( addr < 0xFF00 ) { //Invalid
		printf( "[MEM] Write to invalid memory region 0xFF00-0xFF7F\n" );
	} else if ( addr < 0xFF80 ) { //IO ports
		printf( "[MEM] Write to I/O port address %4x - not implemented\n", addr );
	} else if ( addr < 0xFFFE ) {
		mmap->hram[addr - 0xFF80] = value;
	}
}
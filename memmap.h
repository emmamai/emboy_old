typedef struct mmapState_s {
	cartridge_t *cart;
	char* vram;
	char vram_bank;

	char* wram;
	char wram_bank;
	
	char* oam;
	char* hram;

	char reg_lcd_control; 	// 0xFF40 LCD Control
	char reg_stat;			// 0xFF41 LCDC Status
 	char reg_ly; 			// 0xFF44 LCDC Y-coord - Current line being drawn. If >143, system is in VBLANK.

	char reg_interrupt_enable;
} mmapState_t;

mmapState_t* Mmap_Init();

unsigned char Mmap_PeekConst( const mmapState_t* mmap, unsigned short addr );
unsigned char Mmap_Peek( mmapState_t* mmap, unsigned short addr );
void Mmap_Poke( mmapState_t* mmap, unsigned short addr, unsigned char value );

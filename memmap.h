typedef struct mmapState_s {
	cartridge_t *cart;
	char* vram;
	char vram_bank;

	char* wram;
	char wram_bank;
	
	char* oam;
	char* ioports;
	char* hram;
	char reg_interrupt_enable;
} mmapState_t;

mmapState_t* Mmap_Init();

unsigned char Mmap_PeekConst( const mmapState_t* mmap, unsigned short addr );
unsigned char Mmap_Peek( mmapState_t* mmap, unsigned short addr );
void Mmap_Poke( mmapState_t* mmap, unsigned short addr, unsigned char value );

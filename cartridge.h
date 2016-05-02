
typedef enum {
	CART_ROM_ONLY = 				0x00,
	CART_MBC1 = 					0x01,
	CART_MBC1_RAM = 				0x02,
	CART_MBC1_RAM_BATTERY = 		0x03,
	CART_MBC2 =						0x05,
	CART_MBC2_BATTERY = 			0x06,
	CART_ROM_RAM = 					0x08,
	CART_ROM_RAM_BATTERY =			0x09,
	CART_MMM01 = 					0x0B,
	CART_MMM01_RAM =				0x0C,
	CART_MMM01_RAM_BATTERY = 		0x0D,
	CART_MBC3_TIMER_BATTERY =		0x0F,
	CART_MBC3_TIMER_RAM_BATTERY = 	0x10,
	CART_MBC3 = 					0x11,
	CART_MBC3_RAM = 				0x12,
	CART_MBC3_RAM_BATTERY = 		0x13,
	CART_MBC4 = 					0x15,
	CART_MBC4_RAM = 				0x16,
	CART_MBC4_RAM_BATTERY = 		0x17,
	CART_MBC5 = 					0x19,
	CART_MBC5_RAM = 				0x1A,
	CART_MBC5_RAM_BATTERY = 		0x1B,
	CART_MBC5_RUMBLE = 				0x1C,
	CART_MBC5_RUMBLE_RAM = 			0x1D,
	CART_MBC5_RUMBLE_RAM_BATTERY = 	0x1E,
	CART_POCKET_CAMERA = 			0xFC,
	CART_BANDAI_TAMA5 = 			0xFD,
	CART_HuC3 = 					0xFE,
	CART_HuC1_RAM_BATTERY = 		0xFF,
} cartType_t;

typedef struct cartridge_s {
	char *logo;
	char title[17];
	char mcode[5];
	char cgbflag;
	char new_lcode[3];
	cartType_t carttype;
	char romsize_byte;
	char ramsize_byte;
	char destcode;
	char old_lcode;
	char version;
	char header_checksum;
	short global_checksum;

	char eram_bank_number;
	char eram_size;
	char *eram;

	char rom_bank_number;
	char *buffer;
	unsigned int buffer_size;
} cartridge_t;

cartridge_t * Cart_Load( char * path );
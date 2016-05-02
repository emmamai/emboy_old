#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cartridge.h"

cartridge_t * Cart_Load( char * path ) {
	char *tmp_buffer;
	int bytes_read = 0;

	FILE * romfile = fopen( path, "r" );
	if ( !romfile ) {
		printf( "File not found: %s\n", path );
		return NULL;
	}

	cartridge_t * cart = malloc( sizeof( cartridge_t ) );

	//using fseek is NOT a good practice, as common as its usage is. Instead, we load 
	//the file in chunks, and reallocate as more comes in, until the file has been 
	//fully read. This is safer than using fseek as there is NO guarantee from the C 
	//library that fseek will work as we expect with binary files; we only expect this
	//because POSIX lets us do it that way.

	cart->buffer_size = 0;
	cart->buffer = malloc( cart->buffer_size );

	tmp_buffer = malloc( 16384 );

	while( ( bytes_read = fread( tmp_buffer, sizeof( char ), 16384, romfile ) ) > 0 ) {
		cart->buffer = realloc( cart->buffer, cart->buffer_size + bytes_read );
		memcpy( cart->buffer + cart->buffer_size, tmp_buffer, bytes_read );
		cart->buffer_size = cart->buffer_size + bytes_read;
	}
	free( tmp_buffer );
	if ( cart->buffer_size < 32768 ) {
		printf( "Failed - file smaller than 32k\n" );
		free( cart->buffer );
		return NULL;
	}
	printf( "File \"%s\" loaded, total %u bytes\n", path, cart->buffer_size );

	cart->logo = &cart->buffer[0x104];
	cart->old_lcode = cart->buffer[0x14b];

	strncpy( cart->title, &cart->buffer[0x134], 11 );
	printf( "Title: %s v0x%02x\n", cart->title, cart->version = cart->buffer[0x14c] );

	memset( cart->new_lcode, 3, sizeof( char ) );
	if ( ( cart->old_lcode = cart->buffer[0x14b] ) != 33 ) {
		printf( "Manufacturer code (old style): %u\n", cart->old_lcode );
	} else {
		memcpy( cart->new_lcode, &cart->buffer[0x144], 2 );
		printf( "Manufacturer code (new style): %s\n", cart->new_lcode );
	}

	return cart;
}

void Cart_Free( cartridge_t *cart ) {
	free( cart->buffer );
	free( cart );
}
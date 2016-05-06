
#include <stdio.h>
#include <stdlib.h>

#include "cartridge.h"
#include "memmap.h"
#include "cpu.h"

unsigned int lcd_mode_cycle_count = 0;

void LCD_Init( mmapState_t* mmap ) {
	//These values are guesses, they could be totally wrong compared to
	//what games may expect
	mmap->reg_lcd_control = 0x80;
	mmap->reg_stat = 0x02;
	mmap->reg_ly = 0;
}

void LCD_RunClockCycle( mmapState_t* mmap ) {
	if ( ( mmap->reg_lcd_control & 0x80 ) == 0x80 ) {
		if ( ( mmap->reg_stat & 0x03 ) == 0 ) {
			lcd_mode_cycle_count++;
			if ( lcd_mode_cycle_count >= 204 ) {
				lcd_mode_cycle_count = 0;
				if ( mmap->reg_ly >= 144 ) {
					mmap->reg_stat = mmap->reg_stat | 0x01;
				} else {
					mmap->reg_ly = mmap->reg_ly + 1;
					mmap->reg_stat = mmap->reg_stat | 0x02;
				}
			}
		} else if ( ( mmap->reg_stat & 0x03 ) == 1 ) {
			lcd_mode_cycle_count++;
			if ( lcd_mode_cycle_count >= 4560 ) {
				lcd_mode_cycle_count = 0;
				mmap->reg_stat = mmap->reg_stat & 0xFE;
				mmap->reg_stat = mmap->reg_stat | 0x02;
			} else {
				if ( lcd_mode_cycle_count % 456 == 0 ) {
					mmap->reg_ly = mmap->reg_ly + 1;
				}
			}
		} else if ( ( mmap->reg_stat & 0x03 ) == 2 ) {
			lcd_mode_cycle_count++;
			if ( lcd_mode_cycle_count >= 80 ) {
				lcd_mode_cycle_count = 0;
				mmap->reg_stat = mmap->reg_stat | 0x03;
			}
		} else if ( ( mmap->reg_stat & 0x03 == 3 ) ) {
			lcd_mode_cycle_count++;
			if ( lcd_mode_cycle_count >= 172 ) {
				lcd_mode_cycle_count = 0;
				mmap->reg_stat = mmap->reg_stat & 0xFC;
			}
		}
	}
}

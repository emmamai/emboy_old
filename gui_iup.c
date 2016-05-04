#include <stdio.h>
#include <stdlib.h>
#include <iup/iup.h>

#include "cartridge.h"
#include "memmap.h"
#include "cpu.h"

Ihandle* dbg_wnd, * dbg_btn_run, * dbg_btn_step, * dbg_btn_break, * dbg_btn_reset;
Ihandle* dbg_lbl_af, * dbg_lbl_bc, * dbg_lbl_de, * dbg_lbl_hl, * dbg_lbl_sp, * dbg_lbl_pc;
Ihandle* dbg_txt_af, * dbg_txt_bc, * dbg_txt_de, * dbg_txt_hl, * dbg_txt_sp, * dbg_txt_pc;
Ihandle* dbg_inslist, * dbg_memdropdown, * dbg_memlist;
Ihandle* dbg_buttons, * dbg_wnd_container, * dbg_reg_lbl_container, * dbg_reg_txt_container, *dbg_reg_container , * dbg_bottom_container, * dbg_right_container;

extern cartridge_t* cart;
extern cpuState_t* cpu;
extern mmapState_t* mmap;

char *af_str;
char *bc_str;
char *de_str;
char *hl_str;
char *sp_str;
char *pc_str;

int is_running = 0;

void UpdateDbgWindowRegValues( cpuState_t* cpu ) {
	sprintf( af_str, "0x%04x", *cpu->af );
	sprintf( bc_str, "0x%04x", *cpu->bc );
	sprintf( de_str, "0x%04x", *cpu->de );
	sprintf( hl_str, "0x%04x", *cpu->hl );
	sprintf( sp_str, "0x%04x", *cpu->sp );
	sprintf( pc_str, "0x%04x", *cpu->pc );

	IupSetAttribute( dbg_txt_af, "VALUE", af_str );
	IupSetAttribute( dbg_txt_bc, "VALUE", bc_str );
	IupSetAttribute( dbg_txt_de, "VALUE", de_str );
	IupSetAttribute( dbg_txt_hl, "VALUE", hl_str );
	IupSetAttribute( dbg_txt_sp, "VALUE", sp_str );
	IupSetAttribute( dbg_txt_pc, "VALUE", pc_str );
}

void OnBreak( void ) {
	printf( "BREAK\n" );
	is_running = 0;
}

void Run( void ) {
	is_running = 1;
}

void Step( void ) {
	while( RunClockCycle( cpu, mmap ) < 1 );
	UpdateDbgWindowRegValues( cpu );
}

int Idle( void ) {
	if ( is_running > 0 ) {
		RunClockCycle( cpu, mmap );
	}
	return IUP_DEFAULT;
}

void CreateDbgWindow() {
	dbg_btn_run = IupButton( "Run", NULL );
	dbg_btn_step = IupButton( "Step", NULL );
	dbg_btn_break = IupButton( "Break", NULL );
	dbg_btn_reset = IupButton( "Reset", NULL );
	dbg_buttons = IupVbox( dbg_btn_run, dbg_btn_step, dbg_btn_break, NULL );

	// dbg_reglist = Iup
	IupSetCallback( dbg_btn_run, "ACTION", (Icallback)Run );
	IupSetCallback( dbg_btn_step, "ACTION", (Icallback)Step );
	IupSetCallback( dbg_btn_break, "ACTION", (Icallback)OnBreak );

	IupSetAttribute( dbg_btn_run, "SIZE", "50x20" );
	IupSetAttribute( dbg_btn_step, "SIZE", "50x20" );
	IupSetAttribute( dbg_btn_break, "SIZE", "50x20" );

	dbg_lbl_af = IupLabel( "AF" );
	dbg_lbl_bc = IupLabel( "BC" );
	dbg_lbl_de = IupLabel( "DE" );
	dbg_lbl_hl = IupLabel( "HL" );
	dbg_lbl_sp = IupLabel( "SP" );
	dbg_lbl_pc = IupLabel( "PC" );

	IupSetAttribute( dbg_lbl_af, "SIZE", "50x20" );
	IupSetAttribute( dbg_lbl_bc, "SIZE", "50x20" );
	IupSetAttribute( dbg_lbl_de, "SIZE", "50x20" );
	IupSetAttribute( dbg_lbl_hl, "SIZE", "50x20" );
	IupSetAttribute( dbg_lbl_sp, "SIZE", "50x20" );
	IupSetAttribute( dbg_lbl_pc, "SIZE", "50x20" );

	dbg_txt_af = IupText( NULL );
	dbg_txt_bc = IupText( NULL );
	dbg_txt_de = IupText( NULL );
	dbg_txt_hl = IupText( NULL );
	dbg_txt_sp = IupText( NULL );
	dbg_txt_pc = IupText( NULL );

	IupSetAttribute( dbg_txt_af, "READONLY", "YES" );
	IupSetAttribute( dbg_txt_bc, "READONLY", "YES" );
	IupSetAttribute( dbg_txt_de, "READONLY", "YES" );
	IupSetAttribute( dbg_txt_hl, "READONLY", "YES" );
	IupSetAttribute( dbg_txt_sp, "READONLY", "YES" );
	IupSetAttribute( dbg_txt_pc, "READONLY", "YES" );

	IupSetAttribute( dbg_txt_af, "SIZE", "50x20" );
	IupSetAttribute( dbg_txt_bc, "SIZE", "50x20" );
	IupSetAttribute( dbg_txt_de, "SIZE", "50x20" );
	IupSetAttribute( dbg_txt_hl, "SIZE", "50x20" );
	IupSetAttribute( dbg_txt_sp, "SIZE", "50x20" );
	IupSetAttribute( dbg_txt_pc, "SIZE", "50x20" );

	dbg_reg_lbl_container = IupVbox( dbg_lbl_af, dbg_lbl_bc, dbg_lbl_de, dbg_lbl_hl, dbg_lbl_sp, dbg_lbl_pc, NULL );
	dbg_reg_txt_container = IupVbox( dbg_txt_af, dbg_txt_bc, dbg_txt_de, dbg_txt_hl, dbg_txt_sp, dbg_txt_pc, NULL );


	dbg_reg_container = IupHbox( dbg_reg_lbl_container, dbg_reg_txt_container, NULL );
	dbg_wnd_container = IupHbox( dbg_buttons, dbg_reg_container, NULL);
	dbg_wnd = IupDialog( dbg_wnd_container );
	IupShowXY( dbg_wnd, IUP_CENTER, IUP_CENTER );
}

int GUI_Init( int *argc, char ***argv ) {
	int r = IupOpen( argc, argv );

	switch( r ) {
		case IUP_OPENED:
			printf( "[GUI] Warning: GUI_Init called after GUI was already initialized");
			return 0;
		case IUP_ERROR:
			printf( "[GUI] Error: Failure initializing IUP library" );
			return -1;
		default:
			break;
	}

	af_str = malloc( 16 );
	bc_str = malloc( 16 );
	de_str = malloc( 16 );
	hl_str = malloc( 16 );
	sp_str = malloc( 16 );
	pc_str = malloc( 16 );

	CreateDbgWindow();

	return 0;
}

void GUI_MainLoop( cpuState_t* cpu, mmapState_t* mmap ) {
	IupSetFunction( "IDLE_ACTION", (Icallback)Idle );
	IupMainLoop();
}

void GUI_Shutdown( void ) {
	IupClose();
}
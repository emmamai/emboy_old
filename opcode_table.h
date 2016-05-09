#ifndef _OPCODES_TABLE_H_

/*
This file breaks normal function naming conventions, as
my normal convention is very hard to read with opcode-based
function names.
*/

opcode_t opcodes[256] = {
	{ // 0x00
		"NOP",
		&op_nop,
		&no_op_display
	},
	{ // 0x01
		"LD BC, d16",
		&op_ld_bc_d16,
		&no_op_display
	},
	{ // 0x02
		"LD (BC), A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x03
		"INC BC UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x04
		"INC B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x05
		"DEC B",
		&op_dec_b,
		&no_op_display
	},
	{ // 0x06
		"LD B, d8",
		&op_ld_b_d8,
		&no_op_display
	},
	{ // 0x07
		"RLCA UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x08
		"LD (a16), SP UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x09
		"ADD HL, BC UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x0A
		"LD A, (BC) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x0B
		"DEC BC",
		&op_dec_bc,
		&no_op_display
	},
	{ // 0x0C
		"INC C",
		&op_inc_c,
		&no_op_display
	},
	{ // 0x0D
		"DEC C",
		&op_dec_c,
		&no_op_display
	},
	{ // 0x0E
		"LD C, d8",
		&op_ld_c_d8,
		&no_op_display
	},
	{ // 0x0F
		"RRCA UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x10
		"STOP UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x11
		"LD DE, d16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x12
		"LD (DE), A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x13
		"INC DE UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x14
		"INC D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x15
		"DEC D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x16
		"LD D, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x17
		"RLA UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x18
		"JR r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x19
		"ADD HL, DE UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1A
		"LD A, (DE) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1B
		"DEC DE UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1C`
		"INC E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1D
		"DEC E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1E
		"LD E, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x1F
		"RRA UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x20
		"JR NZ, r8",
		&op_jr_nz_r8,
		&no_op_display
	},
	{ // 0x21
		"LD HL, d16",
		&op_ld_hl_d16,
		&no_op_display
	},
	{ // 0x22
		"LD (HL+), A",
		&op_ld_hlinc_a,
		&no_op_display
	},
	{ // 0x23
		"INC HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x24
		"INC H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x25
		"DEC H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x26
		"LD H, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x27
		"DAA UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x28
		"JR Z, r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x29
		"ADD HL, HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x2A
		"LD A, (HL+)",
		&op_ld_a_hlinc,
		&no_op_display
	},
	{ // 0x2B
		"DEC HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x2C
		"INC L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x2D
		"DEC L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x2E
		"LD L, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x2F
		"CPL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x30
		"JR NC, r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x31
		"LD SP, d16",
		&op_ld_sp_d16,
		&no_op_display
	},
	{ // 0x32
		"LD (HL-), A",
		&op_ld_hldec_a,
		&no_op_display
	},
	{ // 0x33
		"INC SP UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x34
		"INC (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x35
		"DEC (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x36
		"LD (HL), d8",
		&op_ld_hl_d8,
		&no_op_display
	},
	{ // 0x37
		"SCF UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x38
		"JR C, r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x39
		"ADD HL, SP UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x3A
		"LD A, (HL-) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x3B
		"DEC SP UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x3C
		"INC A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x3D
		"DEC A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x3E
		"LD A, d8",
		&op_ld_a_d8,
		&no_op_display
	},
	{ // 0x3F
		"CCF UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
		{ // 0x40
		"LD B, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x41
		"LD B, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x42
		"LD B, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x43
		"LD B, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x44
		"LD B, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x45
		"LD B, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x46
		"LD B, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x47
		"LD B, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x48
		"LD C, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x49
		"LD C, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4A
		"LD C, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4B
		"LD C, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4C
		"LD C, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4D
		"LD C, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4E
		"LD C, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x4F
		"LD C, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x50
		"LD D, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x51
		"LD D, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x52
		"LD D, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x53
		"LD D, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x54
		"LD D, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x55
		"LD D, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x56
		"LD D, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x57
		"LD D, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x58
		"LD E, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x59
		"LD E, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5A
		"LD E, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5B
		"LD E, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5C
		"LD E, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5D
		"LD E, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5E
		"LD E, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x5F
		"LD E, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x60
		"LD H, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x61
		"LD H, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x62
		"LD H, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x63
		"LD H, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x64
		"LD H, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x65
		"LD H, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x66
		"LD H, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x67
		"LD H, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x68
		"LD L, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x69
		"LD L, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6A
		"LD L, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6B
		"LD L, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6C
		"LD L, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6D
		"LD L, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6E
		"LD L, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x6F
		"LD L, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x70
		"LD (HL), B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x71
		"LD (HL), C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x72
		"LD (HL), D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x73
		"LD (HL), E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x74
		"LD (HL), H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x75
		"LD (HL), L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x76
		"HALT UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x77
		"LD (HL), A",
		&op_ld_hl_a,
		&no_op_display
	},
	{ // 0x78
		"LD A, B",
		&op_ld_a_b,
		&no_op_display
	},
	{ // 0x79
		"LD A, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7A
		"LD A, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7B
		"LD A, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7C
		"LD A, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7D
		"LD A, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7E
		"LD A, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x7F
		"LD A, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x80
		"ADD A, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x81
		"ADD A, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x82
		"ADD A, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x83
		"ADD A, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x84
		"ADD A, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x85
		"ADD A, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x86
		"ADD A, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x87
		"ADD A, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x88
		"ADC A, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x89
		"ADC A, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8A
		"ADC A, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8B
		"ADC A, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8C
		"ADC A, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8D
		"ADC A, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8E
		"ADC A, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x8F
		"ADC A, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x90
		"SUB B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x91
		"SUB C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x92
		"SUB D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x93
		"SUB E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x94
		"SUB H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x95
		"SUB L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x96
		"SUB (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x97
		"SUB A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x98
		"SBC A, B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x99
		"SBC A, C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9A
		"SBC A, D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9B
		"SBC A, E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9C
		"SBC A, H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9D
		"SBC A, L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9E
		"SBC A, (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0x9F
		"SBC A, A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA0
		"AND B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA1
		"AND C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA2
		"AND D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA3
		"AND E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA4
		"AND H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA5
		"AND L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA6
		"AND (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA7
		"AND A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA8
		"XOR B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xA9
		"XOR C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAA
		"XOR D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAB
		"XOR E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAC
		"XOR H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAD
		"XOR L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAE
		"XOR (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xAF
		"XOR A",
		&op_xor_a,
		&no_op_display
	},
	{ // 0xB0
		"OR B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB1
		"OR C",
		&op_or_c,
		&no_op_display
	},
	{ // 0xB2
		"OR D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB3
		"OR E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB4
		"OR H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB5
		"OR L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB6
		"OR (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB7
		"OR A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB8
		"CP B UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xB9
		"CP C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBA
		"CP D UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBB
		"CP E UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBC
		"CP H UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBD
		"CP L UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBE
		"CP (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xBF
		"CP A UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC0
		"RET NZ UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC1
		"POP BC UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC2
		"JP NZ a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC3
		"JP a16",
		&op_jp_a16,
		&no_op_display
	},
	{ // 0xC4
		"CALL NZ, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC5
		"PUSH BC UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC6
		"ADD A, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC7
		"RST 0x00 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC8
		"RET Z UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xC9
		"RET UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xCA
		"JP Z, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xCB
		"PREFIX CB UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xCC
		"CALL Z, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xCD
		"CALL a16",
		&op_call_a16,
		&no_op_display
	},
	{ // 0xCE
		"ADC A, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xCF
		"RST 0x08 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD0
		"RET NC UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD1
		"POP DE UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD2
		"JP NC, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD3
		"INVALID 0xD3",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD4
		"CALL NC, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD5
		"PUSH DE UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD6
		"SUB d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD7
		"RST 0x10 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD8
		"RET C UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xD9
		"RETI UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDA
		"JP C, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDB
		"INVALID 0xDB",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDC
		"CALL C, a16 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDD
		"INVALID 0xDD",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDE
		"SBC A, d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xDF
		"RST 0x18 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE0
		"LDH (a8), A",
		&op_ldh_a8_a,
		&no_op_display
	},
	{ // 0xE1
		"POP HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE2
		"LD (C), A",
		&op_ld_cref_a,
		&no_op_display
	},
	{ // 0xE3
		"INVALID 0xE3",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE4
		"INVALID 0xE4",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE5
		"PUSH HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE6
		"AND d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE7
		"RST 0x20 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE8
		"ADD SP, r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xE9
		"JP (HL) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xEA
		"LD (a16), A",
		&op_ld_a16_a,
		&no_op_display
	},
	{ // 0xEB
		"INVALID 0xEB",
		&no_opcode,
		&no_op_display
	},
	{ // 0xEC
		"INVALID 0xEC",
		&no_opcode,
		&no_op_display
	},
	{ // 0xED
		"INVALID 0xED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xEE
		"XOR d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xEF
		"RST 0x28 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF0
		"LDH A, (a8)",
		&op_ldh_a_a8,
		&no_op_display
	},
	{ // 0xF1
		"POP AF UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF2
		"LD A, (C) UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF3
		"DI FAKED - NO INTERRUPTS",
		&op_nop,
		&no_op_display
	},
	{ // 0xF4
		"INVALID 0xF4",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF5
		"PUSH AF UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF6
		"OR d8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF7
		"RST 0x30 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF8
		"LD HL, SP+r8 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xF9
		"LD SP, HL UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
	{ // 0xFA
		"LD A, (a16)",
		&op_ld_a_a16,
		&no_op_display
	},
	{ // 0xFB
		"EI FAKED - NO INTERRUPTS",
		&op_nop,
		&no_op_display
	},
	{ // 0xFC
		"INVALID 0xFC",
		&no_opcode,
		&no_op_display
	},
	{ // 0xFD
		"INVALID 0xFD",
		&no_opcode,
		&no_op_display
	},
	{ // 0xFE
		"CP d8",
		&op_cp_d8,
		&no_op_display
	},
	{ // 0xFF
		"RST 0x38 UNIMPLEMENTED",
		&no_opcode,
		&no_op_display
	},
};

#define _OPCODES_TABLE_H_
#endif

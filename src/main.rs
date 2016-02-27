use std::env;
use std::str;
use std::fs;
use std::io::Read;
use std::path::Path;

struct Gameboy {
	cpu: GbCpu,
	mmap: MemMap
}

impl Gameboy {
	fn new<P: AsRef<Path>>(path: P) -> Gameboy {
		Gameboy {
			cpu: GbCpu::new(),
			mmap: MemMap {
				cartridge: GbRom::new(path),
				vram: vec![0; 0x2000],
				ram: vec![0; 0x2000],
				oam: vec![0; 0xa0],
				hram: vec![0; 63],
				reg_interrupt_enable: 0,
			}
		}
	}
	fn run_clock_cycle(&mut self) {
		self.cpu.run_clock_cycle(&mut self.mmap);
	}
	fn hard_reset(&mut self) {
		self.cpu.reg_a = 0x01;
		self.cpu.reg_f = 0xB0;
		self.cpu.reg_b = 0x00;
		self.cpu.reg_c = 0x13;
		self.cpu.reg_d = 0x00;
		self.cpu.reg_e = 0xD8;
		self.cpu.reg_h = 0x01;
		self.cpu.reg_l = 0x4D;
		self.cpu.reg_sp = 0xFFFE;
		self.cpu.reg_pc = 0x100;
	}
}

struct MemMap {
	cartridge: GbRom,
	vram: Vec<u8>,
	ram: Vec<u8>,
	oam: Vec<u8>,
	hram: Vec<u8>,
	reg_interrupt_enable: u8,
}

impl MemMap {
	fn peek(&self, addr: u16) -> u8 {
		match addr {
			0x0000 ... 0x3fff => self.cartridge.peek(addr),
			0x4000 ... 0x7fff => self.cartridge.peek(addr),
			0x8000 ... 0x9FFF => self.vram[(addr-0x8000) as usize],
			0xA000 ... 0xBFFF => self.cartridge.peek(addr),
			0xC000 ... 0xCFFF => self.ram[(addr-0xC000) as usize],
			0xD000 ... 0xDFFF => self.ram[(addr-0xC000) as usize],
			0xE000 ... 0xEFFF => self.ram[(addr-0xE000) as usize],
			0xF000 ... 0xFDFF => self.ram[(addr-0xE000) as usize],
			0xFE00 ... 0xFE9F => self.oam[(addr-0xFE00) as usize],
			0xFEA0 ... 0xFEFF => { println!("Read from unusable address space 0xFEA0-0xFEFF"); 0 },
			0xFF00 ... 0xFF7F => { println!("Write to unimplemented IO port address {}", addr); 0 },
			0xFF80 ... 0xFFFE => self.hram[(addr-0xFF80) as usize],
			0xFFFF => self.reg_interrupt_enable,
			_ => panic!("MemMap::addr No mapping for address 0x{0:04X}", addr),
		}
	}
	fn poke(&mut self, addr: u16, val: u8) {
		match addr {
			0x0000 ... 0x3fff => { self.cartridge.poke(addr, val); },
			0x4000 ... 0x7fff => { self.cartridge.poke(addr, val); },
			0x8000 ... 0x9FFF => { self.vram[(addr-0x8000) as usize] = val; },
			0xA000 ... 0xBFFF => { self.cartridge.poke(addr, val); },
			0xC000 ... 0xCFFF => { self.ram[(addr-0xC000) as usize] = val; },
			0xD000 ... 0xDFFF => { self.ram[(addr-0xC000) as usize] = val; },
			0xE000 ... 0xEFFF => { self.ram[(addr-0xE000) as usize] = val; },
			0xF000 ... 0xFDFF => { self.ram[(addr-0xE000) as usize] = val; },
			0xFE00 ... 0xFE9F => { self.oam[(addr-0xFE00) as usize] = val; },
			0xFEA0 ... 0xFEFF => { println!("Read from unusable address space 0xFEA0-0xFEFF"); },
			0xFF00 ... 0xFF7F => { println!("Write to unimplemented IO port address {}", addr); },
			0xFF80 ... 0xFFFE => { self.hram[(addr-0xFF80) as usize]; },
			0xFFFF => { self.reg_interrupt_enable = val; },
			_ => panic!("MemMap::addr No mapping for address 0x{0:04X}", addr),
		};
	}
}

struct GbCpu {
	reg_a: u8,
	reg_f: u8,
	reg_b: u8,
	reg_c: u8,
	reg_d: u8,
	reg_e: u8,
	reg_h: u8,
	reg_l: u8,
	reg_sp: u16,
	reg_pc: u16,

	ins_cycles: i8,
	ins_max_cycles: i8
}

impl GbCpu {
	pub fn new() -> GbCpu {
		GbCpu {
			reg_a: 0xff,
			reg_f: 0xf0,
			reg_b: 0x00,
			reg_c: 0x00,
			reg_d: 0x00,
			reg_e: 0x00,
			reg_h: 0x00,
			reg_l: 0x00,
			reg_sp: 0xffff,
			reg_pc: 0x0000,

			ins_cycles: -1,
			ins_max_cycles: 0,
		}
	}
	fn power_on_reset(&mut self) {
		self.reg_a = 0xff;
		self.reg_f = 0xf0;
		self.reg_b = 0x00;
		self.reg_c = 0x00;
		self.reg_h = 0x00;
		self.reg_l = 0x00;
		self.reg_sp = 0xffff;
		self.reg_pc = 0x0000;
	}
	fn run_clock_cycle(&mut self, mmap: &mut MemMap) {
		self.ins_cycles = self.ins_cycles + 1;
		if (self.ins_cycles >= self.ins_max_cycles) {
			self.run_instruction(mmap)
		}
	}
	fn run_instruction(&mut self, mmap: &mut MemMap) {
		let instruction = mmap.peek(self.reg_pc);

		print!("[0x{0:04X}] 0x{1:02X} 	", self.reg_pc, instruction);
		match instruction {
			0x00 => { //NOP
				self.ins_cycles = 0;
				self.ins_max_cycles = 4;
				self.reg_pc = self.reg_pc + 1;
				println!("NOP");
			}
			0x06 => { //LD B, d8
				self.reg_b = mmap.peek(self.reg_pc + 2);
				
				self.ins_cycles = 0;
				self.ins_max_cycles = 8;
				self.reg_pc = self.reg_pc + 2;
				println!("LD B, 0x{0:02X}", self.reg_h);
			}
			0x0E => { //LD C, d8
				self.reg_c = mmap.peek(self.reg_pc + 2);
				
				self.ins_cycles = 0;
				self.ins_max_cycles = 8;
				self.reg_pc = self.reg_pc + 2;
				println!("LD C, 0x{0:02X}", self.reg_h);
			}
			0x21 => { //LD HL, d16
				self.reg_h = mmap.peek(self.reg_pc + 2);
				self.reg_l = mmap.peek(self.reg_pc + 1);
				
				self.ins_cycles = 0;
				self.ins_max_cycles = 12;
				self.reg_pc = self.reg_pc + 3;
				println!("LD HL, 0x{0:02X}{1:02X}", self.reg_h, self.reg_l);
			}
			0x32 => { //LDD HL, A // NOT FUNCTIONAL - Need to decrement HL
				let address = ((self.reg_h as u16)<< 8 ) + (self.reg_l as u16);
				mmap.poke(address, self.reg_a);

				self.ins_cycles = 0;
				self.ins_max_cycles = 4;
				self.reg_pc = self.reg_pc + 1;
				println!("LD (HL), A : (0x{0:04X}) <- 0x{1:02X}", address, self.reg_a);

				//Decrement HL here
			}
			0xC3 => { //JP a16
				let new_address_high = mmap.peek(self.reg_pc + 2) as u16;
				let new_address_low = mmap.peek(self.reg_pc + 1) as u16;
				let new_address = ( new_address_high << 8 ) + new_address_low;
				

				self.ins_cycles = 0;
				self.ins_max_cycles = 16;
				self.reg_pc = new_address;
				println!("JP 0x{0:04X}", new_address);
			}
			0xAF => { //XOR A
				self.reg_a = 0;
				self.reg_f = self.reg_f & 0x7F;

				self.ins_cycles = 0;
				self.ins_max_cycles = 4;
				self.reg_pc = self.reg_pc + 1;
				println!("XOR a");
			}
			_ => println!("Unimplemented instruction"),
		}
	}
}

struct GbRom { 
	buffer: Vec<u8>
}

impl GbRom {
	pub fn peek(&self, addr: u16) -> u8{
		match addr {
			0x0000 ... 0x3fff => self.buffer[addr as usize],
			0x4000 ... 0x7fff => 	{
										//add banking logic here later
										self.buffer[addr as usize]
									},
			0xA000 ... 0xBFFF => 	{
										//add external ram/otherstuff logic here
										0
									},
			_ => { println!("GbRom::peek called with unusual address"); 0 },
		}
	}
	pub fn poke(&self, addr: u16, val: u8) {

	}
	pub fn new<P: AsRef<Path>>(path: P) -> GbRom {
		println!("Loading ROMfile");
		let mut file = fs::File::open(path).unwrap();
		let mut buf = Vec::new();
		file.read_to_end(&mut buf).unwrap();
		let mut rom = GbRom {
			buffer: buf
		};
		println!("Title: {}", str::from_utf8(rom.get_title()).unwrap());
		rom
	}
	pub fn get_title(&self) -> &[u8] {
		&self.buffer[0x134 .. 0x142]
	}
}

fn main() {
    println!("emboy");

    let rom_filename = env::args().nth(1).unwrap();
    let mut gb= Gameboy::new(rom_filename);
    

  	gb.hard_reset();
    for i in 0..96{
    	gb.cpu.run_clock_cycle(&mut gb.mmap);
    }
}
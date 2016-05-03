LIBS= -liup
OBJS= main.o cartridge.o cpu.o memmap.o opcodes.o gui_iup.o
DEFINES=
CFLAGS= -ggdb -Wall -O0
CC= gcc
OUT= emboy

default: emboy

emboy: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(OUT) $(OBJS)

clean:
	-@rm -f *.o emboy

CC = clang
LD = clang
LAYEC = layec

CFLAGS =
LDFLAGS =
LAYEFLAGS =

GFUX_INCDIR = -Igfux/include
GFUX_INC = $(wildcard ./gfux/include/*.h) $(wildcard ./gfux/lib/*.h) $(wildcard ./gfux/src/*.h)
GFUX_LIB = $(wildcard ./gfux/lib/*.c)
GFUX_OBJ = $(patsubst ./gfux/lib/%.c, ./out/o/gfux/%.o, $(GFUX_LIB))

all: libc liblaye bios sdk gfux

libc:

liblaye:

bios:

sdk:

gfux: gfuxcli

gfuxcli: $(GFUX_OBJ) ./out/o/gfuxcli.o $(GFUX_INC)
	$(LD) $(LDFLAGS) -o ./out/gfuxcli $(GFUX_OBJ) ./out/o/gfuxcli.o

./out/o/gfuxcli.o: ./gfux/src/cli.c $(GFUX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUX_INCDIR) -o $@ ./gfux/src/cli.c

./out/o/gfux/%.o: ./gfux/lib/%.c $(GFUX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUX_INCDIR) -o $@ ./gfux/lib/%.c

clean:
	rm -rf out

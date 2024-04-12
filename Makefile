# GameFU Station master build script
# Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
# See LICENSE.adoc for licensing information for build scripts

CC = clang
LD = clang
LAYEC = layec

CFLAGS =
LDFLAGS =
LAYEFLAGS =

GFUASM_INCDIR = -Igfuasm/include
GFUASM_INC = $(wildcard ./gfuasm/include/*.h) $(wildcard ./gfuasm/src/*.h)
GFUASM_SRC = $(wildcard ./gfuasm/src/*.c)
GFUASM_OBJ = $(patsubst ./gfuasm/src/%.c, ./out/o/gfuasm_%.o, $(GFUASM_SRC))

GFUSX_INCDIR = -Igfusx/include
GFUSX_INC = $(wildcard ./gfusx/include/*.h) $(wildcard ./gfusx/lib/*.h) $(wildcard ./gfusx/src/*.h)
GFUSX_LIB = $(wildcard ./gfusx/lib/*.c)
GFUSX_OBJ = $(patsubst ./gfusx/lib/%.c, ./out/o/gfusx_%.o, $(GFUSX_LIB))

all: gfuasm libc liblaye bios sdk gfusx

gfuasm: $(GFUASM_OBJ) $(GFUASM_INC)
	$(LD) $(LDFLAGS) -o ./out/gfuasm $(GFUASM_OBJ)

./out/o/gfuasm_%.o: ./gfuasm/src/%.c $(GFUASM_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUASM_INCDIR) -o $@ $<

libc:

liblaye:

bios:

sdk:

gfusx: gfusxcli

gfusxcli: $(GFUSX_OBJ) ./out/o/gfusxcli.o $(GFUSX_INC)
	$(LD) $(LDFLAGS) -o ./out/gfusxcli $(GFUSX_OBJ) ./out/o/gfusxcli.o

./out/o/gfusxcli.o: ./gfusx/src/cli.c $(GFUSX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUSX_INCDIR) -o $@ $<

./out/o/gfusx_%.o: ./gfusx/lib/%.c $(GFUSX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUSX_INCDIR) -o $@ $<

clean:
	rm -rf out

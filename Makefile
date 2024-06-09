# GameFU Station master build script
# Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
# See LICENSE.adoc for licensing information for build scripts

# It's entirely possible that this build script becomes something different,
# like a whole CMake shenanigan or something, in the future.
# For now, at least, it's plenty simple to write a few makefile rules.
# The more cross platform this becomes, the more a different build script will be needed.

CC = clang
LD = clang
LAYEC = layec

CFLAGS =
LDFLAGS =
LAYEFLAGS =

GFUASM_INCDIR = -Ilca/include -Igfuasm/include
GFUASM_INC = $(wildcard ./lca/include/*.h) $(wildcard ./gfuasm/include/*.h) $(wildcard ./gfuasm/src/*.h)
GFUASM_SRC = $(wildcard ./gfuasm/src/*.c)
GFUASM_OBJ = $(patsubst ./gfuasm/src/%.c, ./out/o/gfuasm_%.o, $(GFUASM_SRC))

GFULD_INCDIR = -Ilca/include -Igfuld/include
GFULD_INC = $(wildcard ./lca/include/*.h) $(wildcard ./gfuld/include/*.h) $(wildcard ./gfuld/src/*.h)
GFULD_SRC = $(wildcard ./gfuld/src/*.c)
GFULD_OBJ = $(patsubst ./gfuld/src/%.c, ./out/o/gfuld_%.o, $(GFULD_SRC))

GFUSX_INCDIR = -Ilca/include -Igfusx/include
GFUSX_INC = $(wildcard ./lca/include/*.h) $(wildcard ./gfusx/include/*.h) $(wildcard ./gfusx/lib/*.h) $(wildcard ./gfusx/src/*.h)
GFUSX_LIB = $(wildcard ./gfusx/lib/*.c)
GFUSX_OBJ = $(patsubst ./gfusx/lib/%.c, ./out/o/gfusx_%.o, $(GFUSX_LIB))

all: gfuasm gfuld libc liblaye bios sdk gfusx

gfuasm: $(GFUASM_OBJ) $(GFUASM_INC)
	$(LD) $(LDFLAGS) -o ./out/gfuasm $(GFUASM_OBJ)

./out/o/gfuasm_%.o: ./gfuasm/src/%.c $(GFUASM_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUASM_INCDIR) -o $@ $<

gfuld: $(GFULD_OBJ) $(GFULD_INC)
	$(LD) $(LDFLAGS) -o ./out/gfuld $(GFULD_OBJ)

./out/o/gfuld_%.o: ./gfuld/src/%.c $(GFULD_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFULD_INCDIR) -o $@ $<

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

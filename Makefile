# GameFU Station master build script
# Copyright (C) 2024 GameFU Station Dev Team - MPL Licensed
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CC = clang
LD = clang
LAYEC = layec

CFLAGS =
LDFLAGS =
LAYEFLAGS =

GFUSX_INCDIR = -Igfusx/include
GFUSX_INC = $(wildcard ./gfusx/include/*.h) $(wildcard ./gfusx/lib/*.h) $(wildcard ./gfusx/src/*.h)
GFUSX_LIB = $(wildcard ./gfusx/lib/*.c)
GFUSX_OBJ = $(patsubst ./gfusx/lib/%.c, ./out/o/gfusx/%.o, $(GFUSX_LIB))

all: libc liblaye bios sdk gfusx

libc:

liblaye:

bios:

sdk:

gfusx: gfusxcli

gfusxcli: $(GFUSX_OBJ) ./out/o/gfusxcli.o $(GFUSX_INC)
	$(LD) $(LDFLAGS) -o ./out/gfusxcli $(GFUSX_OBJ) ./out/o/gfusxcli.o

./out/o/gfusxcli.o: ./gfusx/src/cli.c $(GFUSX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUSX_INCDIR) -o $@ ./gfusx/src/cli.c

./out/o/gfusx/%.o: ./gfusx/lib/%.c $(GFUSX_INC)
	mkdir -p ./out/o
	$(CC) $(CFLAGS) -c $(GFUSX_INCDIR) -o $@ ./gfusx/lib/%.c

clean:
	rm -rf out

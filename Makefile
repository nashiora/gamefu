CC = clang
LAYEC = layec

all: gamefu

gamefu: ./src/gamefu.laye
    $(LAYEC) -o $@ $<

pong: ./examples/pong.c
    # make the standalone executable for now
    $(CC) -Iinclude/api -o $@ $< ./lib/gamefu/api/unix/log.c

clean:
    rm -f gamefu
    rm -f pong

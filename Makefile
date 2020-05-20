cc = gcc
cflags = -O3
configuration = debug

ifeq ($(configuration),debug)
cflags += -DDEBUG -O0 -g
endif

all: test-sdl emui.o

font.o: font.psf
	ld -r -b binary -o $@ $^

emui.o: emui.c | emui.h
	$(cc) -c -o $@ $< $(cflags)

emui.a: emui.o font.o
	ar rcs $@ $^

test-sdl: sdl_test.c emui.a
	$(cc) -o $@ $^ $(cflags) -lSDL2

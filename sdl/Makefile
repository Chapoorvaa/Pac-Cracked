# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

all: menu

SRC = menu.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: menu.o


.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END

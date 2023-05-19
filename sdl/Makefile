# Makefile

CC = gcc
CPPFLAGS =
CFLAGS =  -std=c99  -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
LDFLAGS = 
LDLIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf`

all: mainmenu

SRC = mainmenu.c 
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

main: mainmenu.o 


.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END

TARGET = CrazySnake
OBJS = callbacks.o colors.o framebuffer.o game.o globals.o graphics.o input.o intro.o map.o render.o move.o menu.o level.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgu -lpng -lz -lm -lpsprtc
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = CrazySnake PSP
PSP_EBOOT_ICON= ICON0.png
PSP_EBOOT_PIC1= PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

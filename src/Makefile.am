lib_LTLIBRARIES = liblynx.la
liblynx_la_SOURCES = \
	65SC02.h \
	cart.h \
	cpu.h \
	log.h \
	lynx.h \
	mem.h \
	memmap.h \
	mikey.h \
	misc.h \
	msg.h \
	ram.h \
	rom.h \
	suzy.h \
	sysbus.h \
	sysclock.h \
	cpu.c \
	log.c \
	lynx.c \
	mem.c \
	mikey.c \
	msg.c \
	ram.c \
	rom.c \
	suzy.c \
	sysbus.c \
	sysclock.c
liblynx_la_CFLAGS = -Wall
liblynx_la_LDFLAGS = -version-info 0:0:0

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = liblynx.la

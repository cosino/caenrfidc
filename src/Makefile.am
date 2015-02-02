# @configure_input@

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = @EXTRA_CFLAGS@ -I$(top_srcdir)/src
AM_LDFLAGS = -lcaenrfid

bin_PROGRAMS = caenrfidc

caenrfidc_SOURCES = caenrfidc.c utils.c commands.c \
			cmd_fw_release.c cmd_modulation.c \
			cmd_regulation.c cmd_channel.c cmd_help.c \
			cmd_power.c cmd_info.c cmd_protocol.c \
			cmd_exit.c cmd_inventory.c cmd_radio.c \
			cmd_read.c \
			cmd_readpoint.c

noinst_HEADERS = client.h macros.h utils.h commands.h

# Special targets

commands.c : commands.def commands.h
	awk -f def2c.awk $< > $@

commands.h : commands.def
	awk -f def2h.awk $< > $@

clean-local :
	rm -rf commands.c commands.h

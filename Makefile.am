-include $(top_srcdir)/build/modmake.rulesam
AUTOMAKE_OPTIONS = foreign subdir-objects
MODNAME=mod_mediabug

LIBS := $(if $(switch_builddir),$(switch_builddir)/libfreeswitch.la,)

mod_LTLIBRARIES = mod_mediabug.la
mod_mediabug_la_SOURCES  = mod_mediabug.c
mod_mediabug_la_CFLAGS   = $(AM_CFLAGS) $(FREESWITCH_CFLAGS) $(MEDIABUG_CFLAGS)
mod_mediabug_la_LDFLAGS  = -avoid-version -module -no-undefined -shared $(FREESWITCH_LIBS) $(MEDIABUG_LIBS)
mod_mediabug_la_LIBADD   = $(LIBS)

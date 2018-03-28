# See LICENSE file for copyright and license details
# zzzy - simple sleep cycle calculator
.POSIX:

include config.mk

all: zzzy

zzzy: zzzy.o
zzzy.o: zzzy.c config.h

config.h:
	cp config.def.h $@

.o:
	$(CC) -o $@ $(LDFLAGS) $<

.c.o:
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

clean:
	rm -f zzzy zzzy.o

dist:
	rm -rf "zzzy-$(VERSION)"
	mkdir -p "zzzy-$(VERSION)/components"
	cp -R LICENSE Makefile README config.mk config.def.h \
	      zzzy.c \
	      zzzy.1 "zzzy-$(VERSION)"
	tar -cf - "zzzy-$(VERSION)" | gzip -c > "zzzy-$(VERSION).tar.gz"
	rm -rf "zzzy-$(VERSION)"

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	cp -f zzzy "$(DESTDIR)$(PREFIX)/bin"
	chmod 755 "$(DESTDIR)$(PREFIX)/bin/zzzy"
	mkdir -p "$(DESTDIR)$(MANPREFIX)/man1"
	cp -f zzzy.1 "$(DESTDIR)$(MANPREFIX)/man1"
	chmod 644 "$(DESTDIR)$(MANPREFIX)/man1/zzzy.1"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/zzzy"
	rm -f "$(DESTDIR)$(MANPREFIX)/man1/zzzy.1"

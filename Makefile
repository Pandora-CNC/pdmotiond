# pdmotiond - CNC backend deamon
# (c) 2017 Benedikt M.
#
# Makefile: Application Makefile

IDIR=inc
SDIR=src
ODIR=obj

CC=arm-none-linux-gnueabi-gcc
STRIP=arm-none-linux-gnueabi-strip

CFLAGS=-I$(IDIR)
LDFLAGS=-static

_DEPS = appargs.h defs.h driver.h errors.h main.h types.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = appargs.o driver.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pdmotiond: $(OBJ)
	$(CC) -o $@.sdbg $^ $(LDFLAGS)
	$(STRIP) --strip-unneeded -o $@ $@.sdbg

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o pdmotiond*

IDIR =./include
ODIR=./obj
SRCDIR=./src
NAME=libdfmt

CC=gcc
CFLAGS=-Wall -Werror -I$(IDIR) -I/usr/include/libusb-1.0/

LIBS=#-lusb-1.0

_DEPS = ../libdfmt.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = com.o libdfmt.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all
all: static


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: static
static: $(OBJ)
	ar rsc $(NAME).a $(OBJ)
	#gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

.PHONY: debug

debug: CFLAGS +=



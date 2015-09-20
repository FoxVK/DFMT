IDIR =../include
ODIR=../obj

NAME=libdfmt

CC=gcc
CFLAGS=-Wall -Werror -I$(IDIR) -I/usr/include/libusb-1.0/ -g

LIBS= -lusb-1.0

DEPS = ../libdfmt.h $(wildcard $(IDIR)/*.h)

OBJ = $(patsubst %.c,%.o,$(wildcard *.c))

VPATH = $(ODIR) ../

.PHONY: all
all: test static

%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS)

.PHONY: static
static: $(OBJ)
	ar rsc ../$(NAME).a $(patsubst %, $(ODIR)/%, $(OBJ))

.PHONY: clean
clean:
	rm -vf $(ODIR)/*.o *~ core $(INCDIR)/*~ ../$(NAME).a ../$(NAME).bin

.PHONY: test
test: $(OBJ)
	gcc $(CFLAGS) -o ../$(NAME).bin $(patsubst %, $(ODIR)/%, $(OBJ)) $(LIBS)  && chmod +x ../$(NAME).bin

debug: CFLAGS +=

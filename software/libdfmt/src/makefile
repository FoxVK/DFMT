IDIR =../include
ODIR=../obj
DOC=../doc

NAME=libdfmt

CC=gcc
AR=ar
CFLAGS=-Wall -std=c99  -O0 -g
INCLUDES = -I../ -I$(IDIR) -I/usr/include/libusb-1.0/

LIBS= -lusb-1.0

DEPS = $(wildcard ../*.h) $(wildcard $(IDIR)/*.h)

OBJ = $(patsubst %.c,%.o,$(wildcard *.c))

VPATH = $(ODIR) ../

.PHONY: all
all: test static

%.o: %.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $(ODIR)/$@ $< $(CFLAGS) $(INCLUDES)

.PHONY: static
static: ../$(NAME).a
	$(info call from static target: name is $(NAME).a )


../%.a: $(OBJ)
	$(info AR target: name is $(NAME).a target name is $@)
	$(AR) rsc $@ $(patsubst %, $(ODIR)/%, $(OBJ))
	
.PHONY: win32
win32: CC = /usr/bin/i686-w64-mingw32-gcc
win32: AR = /usr/bin/i686-w64-mingw32-ar
win32: ODIR := $(ODIR)/win32
win32: NAME := $(NAME)win32
win32: static


.PHONY: clean
clean:
	rm -rvf $(ODIR) *~ core $(INCDIR)/*~ ../*.a ../*.bin

.PHONY: test
test: ../$(NAME).bin

../$(NAME).bin: $(OBJ)
	gcc $(CFLAGS) -o ../$(NAME).bin $(patsubst %, $(ODIR)/%, $(OBJ)) $(LIBS)  && chmod +x ../$(NAME).bin

.PHONY: doc
doc: $(DOC)/html/index.html


$(DOC)/html/index.html: $(wildcard ../*.h) $(DOC)/Doxyfile
	cd $(DOC) && doxygen
	
$(ODIR):
	mkdir -p $(ODIR)

TARGET=reverse
SOURCE=reverse_matrix.c reverse_matrix.h main.c

CC=gcc
CFLAGS=-O2 -lm

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	@echo Compiling...
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

clean:
	@echo Tidying things up...
	-rm -f $(TARGET)



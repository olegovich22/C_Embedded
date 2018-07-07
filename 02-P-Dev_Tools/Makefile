CC=gcc
CFLAGS=-O2

TARGET=reverse
SOURCE=main reverse_matrix
OBJ:=$(addsuffix .o, $(SOURCE))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(TARGET) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)

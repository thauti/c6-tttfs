CC = gcc
CFLAGS =  -Wall  -I ../libll/ 
EXEC = libtfs
HEADERS = ll.h tfs.h
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)
	cp libtfs.so ..

$(EXEC): $(OBJECTS)
	$(CC)   -L ..  -lll -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)

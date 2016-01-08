CC = gcc
CFLAGS = -fPIC -Wall
EXEC = libll.so
HEADERS = ll.h
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)
	cp libll.so ..

$(EXEC): $(OBJECTS)
	$(CC) -shared -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)

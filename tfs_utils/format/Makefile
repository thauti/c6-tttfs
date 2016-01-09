CC = gcc
CFLAGS = -I ../../libll/ -L ../../ -lll
EXEC = tfs_format

all: $(EXEC)
	cp tfs_format ../../
tfs_format: tfs_format.o tfs_utils.o
	$(CC) -o $@ $^ $(CFLAGS)


tfs_utils.o: tfs_utils.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
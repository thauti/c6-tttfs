IDIR =inc/
CC=gcc
CFLAGS=-I$(IDIR) -L$(LDIR)

LDIR =../

LIBS=-lll

_DEPS = tfs_utils.h

_OBJ = tfs_create.o tfs_utils.o 


%.o: %.c $(_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tfs_create: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
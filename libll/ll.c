#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "ll.h"

int read_physical_block(disk_id id, block b, uint32_t num);
int write_physical_block(disk_id id,block b,uint32_t num);

int main()
{
	char* t = malloc(1024);
	block b = t;
	disk_id d;
	start_disk("disk.tfs",&d);
	write_physical_block(d,b,0);
	read_physical_block(d, b, 0);
    printf("Hello world \n");
    return 0;
}

int start_disk(char *name,disk_id *id)
{
	printf("Lancement du disque \n");
	int fd;
	fd = open(name,  O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if(id == NULL)
	{
		fprintf(stderr, "Erreur impossible de lire le fichier\n");
	}
	id->file_descriptor = fd;	
	id->buffer = malloc(BLOCK_SIZE);
	id->block_curr = -1;
	return 0;
}
int stop_disk(disk_id* id)
{
	// A faire sync();
	close(id->file_descriptor);

}

int read_physical_block(disk_id id, block b, uint32_t num)
{
	block blk;
	lseek(id.file_descriptor, num*BLOCK_SIZE, SEEK_SET);
	read(id.file_descriptor, blk, BLOCK_SIZE);
	id.buffer = &blk;
	id.block_curr = num;
	b = blk;
	/*
	if(id->block_curr == num)
	{
		b = id->buffer;
	}*/
	return 0;
}
int write_physical_block(disk_id id, block b, uint32_t num)
{
	lseek(id.file_descriptor,num*BLOCK_SIZE, SEEK_SET);
	write(id.file_descriptor, b, BLOCK_SIZE);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#include "ll.h"
/*
int read_physical_block(disk_id id, block b, uint32_t num);
int write_physical_block(disk_id id,block b,uint32_t num);
*/
int main()
{
    printf("Hello world \n");
    return 0;
}

int start_disk(char *name,disk_id *id)
{
	disk_id* disk;
	int fd;
	fd = open(name,  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	disk = malloc(sizeof(disk_id));
	if(disk == NULL)
	{
		return -1;
	}
	disk->file_descriptor = fd;	

	return 0;
}
int stop_disk(disk_id* id)
{
	// A faire sync();
	close(id->file_descriptor);

}
/*
int read_physical_block(disk_id id, block b, uint32_t num)
{
	b = id.blocks[num*BLOCK_SIZE];	
	return 0;
}
int write_physical_block(disk_id id, block b, uint32_t num)
{
	id.blocks[num*BLOCK_SIZE] = b;
	return 0;
}*/
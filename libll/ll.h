#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 1024
#define BUF_SIZE 1024

typedef char* block;

typedef struct disk_id
{
	int file_descriptor;
	block* buffer;
	int block_curr;
}disk_id;


int start_disk(char *name,disk_id *id);

//int read_block(disk_id,block b,uint32_t num);
//int write_block(disk_id,block b,uint32_t num);
//int sync(disk_id);
int stop_disk(disk_id* id);
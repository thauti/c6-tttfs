#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 1024
#define BUF_SIZE 1024

typedef char* block;

typedef struct disk_id_s
{
	int file_descriptor;
	block buffer;
	int block_curr;
} disk_id_s;

typedef disk_id_s* disk_id; 

typedef int error;

error start_disk(char *name,disk_id *id);

error read_block(disk_id id ,block b,uint32_t num);
error write_block(disk_id id,block b,uint32_t num);
error sync_disk(disk_id id);
error stop_disk(disk_id id);
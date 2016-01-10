#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "tfs.h"
#include "tfs_utils.h"

int main()
{
	disk_id d = malloc(sizeof(disk_id_s));
	start_disk("truc.tfs", &d);
	printf(" ====> %d\n",getvolumedeb(d,0));
	add_free_block(d,0, 6);
	stop_disk(d);
	return 0;
}
int add_free_block(disk_id d,int volume, int b)
{
	int off = getvolumedeb(d,volume);
	printf("off  : %d", off);
	block blk = malloc(BLOCK_SIZE);
	block aux = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	printf(" -> %d  ",blk[0]);
	int nf = data_to_int(blocksub(blk,12),4);

	printf("nombre block ! %d \n", nf);
	//ajouter_infos(blk, 12, toLittleEndian(nf+1), 4);
	int ff = data_to_int(blocksub(blk,16),4);
	printf("premier blokc! %d \n", ff);/*
	if(ff == 0)
	{
		ajouter_infos(blk, 16, toLittleEndian(b), 4);
	}
	else
	{
		int courant = ff;
		read_block(d, aux, off+(1024*ff));
		int ln = data_to_int(blocksub(aux,1020),4);
		while(ln != courant)
		{
			courant = ln;
			ln = data_to_int(blocksub(aux,1020),4);
			read_block(d, aux, off+(1024*ln));
			
		}
		ajouter_infos(blk, 1020, toLittleEndian(b), 4);
	}*/
	return 0;
}
int getvolumedeb(disk_id d, int part)
{
	block b = malloc(1024);
	read_block(d,b,0);
	int offset=0;

	offset+=4;
	int nparts = data_to_int(blocksub(b,offset),4);
	offset +=4;
	int* partition = malloc(nparts*sizeof(int));
	int pos = 1;
	int i = 0;
	while(i != part)
	{
		pos+= data_to_int(blocksub(b,offset),4);
		partition[i] =  data_to_int(blocksub(b,offset),4);
		offset+=4;
		i++;

	}
	return pos*BLOCK_SIZE;
}
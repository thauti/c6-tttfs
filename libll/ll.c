#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "ll.h"
#include <string.h>

error read_physical_block(disk_id id, block b, uint32_t num);
error write_physical_block(disk_id id,block b,uint32_t num);


error start_disk(char *name,disk_id *id)
{
	printf("Lancement du disque %s \n", name);
	int fd;
	fd = open(name,  O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

	if(fd <0)
	{
		fprintf(stderr, "Erreur impossible de lire le fichier\n");
		return 1;
	}
	(*id)->file_descriptor = fd;
	(*id)->buffer = malloc(BLOCK_SIZE);
	(*id)->block_curr = -1;
	return 0;
}

error stop_disk(disk_id id)
{
	// A faire sync();
	printf("Fermeture \n");
	sync_disk(id);
	close(id->file_descriptor);
	return 0;
}

error read_physical_block(disk_id id, block b, uint32_t num)
{
	printf("Lit %d octets dans le bloc n° %d \n", BLOCK_SIZE, num);
	
	lseek(id->file_descriptor, num*BLOCK_SIZE, SEEK_SET);
	read(id->file_descriptor, b, BLOCK_SIZE);
	id->buffer = b;
	
	id->block_curr = num;
	//printf("Mis en cache %d \n", id->block_curr);
	return 0;
}
error write_physical_block(disk_id id, block b, uint32_t num)
{
	printf("Ecriture \n");
	id->buffer = b;
	lseek(id->file_descriptor,num*BLOCK_SIZE, SEEK_SET);
	write(id->file_descriptor, b, BLOCK_SIZE);
	id->block_curr = num;
	return 0;
}
error sync_disk(disk_id id)
{
	// On vide le buffer sur le disque
	if(id->block_curr != -1){
		//printf("Vidage du buffer \n");
		lseek(id->file_descriptor,id->block_curr*BLOCK_SIZE, SEEK_SET);
		write(id->file_descriptor, id->buffer, BLOCK_SIZE);
		id->block_curr = -1;
	}
	return 0;
}

error read_block(disk_id id,block b,uint32_t num)
{

	if(num == id->block_curr)
	{
		//printf("Lecture depuis le buffer %c \n", id->buffer[1]);

		int i;
		for(i=0; i<BUF_SIZE;i++)
		{
			b[i]=id->buffer[i];
		}
		
	}
	else
	{
		sync_disk(id);
		read_physical_block(id, b, num);
	}
	return 0;

}
error write_block(disk_id id, block b, uint32_t num)
{
	if(num == id->block_curr)
	{
		//printf("Ecriture sur le buffer \n");
		id->buffer = b;

	}
	else
	{
		sync_disk(id);
		write_physical_block(id, b, num);
	}
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "tfs_utils.h"

#define TTTFS_MAGIC_NUMBER 0x31534654;
#define TTTFS_VOLUME_BLOCK_SIZE 1024;

int main(int argc, char* argv[])
{
	char* nom;
	disk_id d;
	d=malloc(sizeof(disk_id_s));
	block firstblock;
	firstblock = malloc(BLOCK_SIZE);
	int p = 0;
	int file_count;

	if(argc < 5)
	{
			fprintf(stderr, "Erreur: le nombre d'argument est invalide \n");
			exit(-1);
	}
	
	if(strcmp(argv[1], "-p"))
	{
		fprintf(stderr, "Erreur: Syntaxe des arguments invalide \n");
			exit(-1);
	}

	if(atoi(argv[2]) == 0)
	{
		fprintf(stderr, "Erreur: Syntaxe des arguments invalide \n");
			exit(-1);
	}
	p = atoi(argv[2]);
	if(strcmp(argv[3], "-mf"))
	{
		fprintf(stderr, "Erreur: Syntaxe des arguments invalide \n");
			exit(-1);
	}
	if(atoi(argv[4]) == 0)
	{
		fprintf(stderr, "Erreur: Syntaxe des arguments invalide \n");
			exit(-1);
	}
	file_count = atoi(argv[4]);
	if(argc == 6){
		nom = argv[argc-1];
	}
	else
	{
		nom = "disk.tfs";
	}



	start_disk(nom, &d);
	read_block(d, firstblock,0);
	int offset = 4;
	int n_partition = data_to_int(blocksub(firstblock,offset),4);
	if(n_partition < p)
	{

		fprintf(stderr, "Erreur: La partition n'existe pas\n");
			exit(-1);
	}
	int i;
	int pos=1;
	offset = 8;
	for(i=1;i<p;i++)
	{
		printf("%d == \n", data_to_int(blocksub(firstblock,offset),4));
		pos+= data_to_int(blocksub(firstblock,offset),4);
		offset+=4;
	}
	int taille = data_to_int(blocksub(firstblock,offset),4);
	printf("Taille bloc %d", taille);
	/*
	d = malloc(sizeof(disk_id_s));
	b = malloc(BLOCK_SIZE);
	f = malloc(BLOCK_SIZE);
	printf("%d", size);
	strncpy(f,toLittleEndian(size),4);
	if(argc == 4)
		nom = argv[3];
	else
		nom = "disk.tfs";
	start_disk(nom, &d);
	write_block(d, b, size-1);
	write_block(d, f, 0);
	printf("Creation du disque %s de taille %d blocs (%d octets) \n", nom, size, size*BLOCK_SIZE);*/

	
	stop_disk(d);
	return 0;
}

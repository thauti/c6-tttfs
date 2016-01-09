#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ll.h"
#include "tfs_utils.h"

void afficherinfos(int taille, int nparitions, int* partition);

int main(int argc, char* argv[])
{
	char* nom;
	if (argc > 2)
	{
		fprintf(stderr, "Erreur: Le nombre d'argument est invalide\n");
		exit(-1);
	}
	if(argc == 1)
	{
		nom = "disk.tfs";
	}
	else	
	{
		nom = argv[1];
	}
	if(access(nom, F_OK))
	{
		fprintf(stderr, "Erreur: Le fichier n'existe pas\n");
		exit(-1);
	}

	disk_id d;
	int offset = 0;
	block b = malloc(BLOCK_SIZE);
	d = malloc(sizeof(disk_id));
	start_disk(nom, &d);
	read_block(d, b, 0);
	int nblocks = data_to_int(blocksub(b,offset),4);
	offset+=4;
	int nparts = data_to_int(blocksub(b,offset),4);
	offset +=4;
	int* partition = malloc(nparts*sizeof(int));
	for(int i=0;i<nparts;i++)
	{
		partition[i] =  data_to_int(blocksub(b,offset),4);
		offset+=4;
	}
	stop_disk(d);
	afficherinfos(nblocks, nparts, partition);
	return 0;
}
void afficherinfos(int taille, int npartition, int* partition)
{
	int i;
	printf("================== \n");
	printf("=== Disque TFS ===\n");
	printf("==================\n");
	printf("Taille du disque : %d block(s) \n", taille);
	printf("Nombre de partition : %d \n", npartition);
	for(i=0;i<npartition;i++)
	{
		printf("Taille de la partition %d : %d block(s)\n", i, partition[i]);
	}
}
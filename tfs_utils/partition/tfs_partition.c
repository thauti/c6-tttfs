#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "tfs_utils.h"

int main(int argc, char* argv[])
{
	char* nom;
	int npartition = 0;
	int i;
	if(argc < 3)
	{
			fprintf(stderr, "Erreur: le nombre d'argument est invalide \n");
			exit(-1);
	}
	for(i=1;i<argc-1;i++)
	{
		if(!strcmp(argv[i], "-p"))
		{
			if(atoi(argv[i+1]) ==0)
			{
				fprintf(stderr, "Erreur: L'argument -p doit être suivi par un nombre\n");
				exit(-1);
			}
			npartition++;
		}
	}
	
	int partition[npartition];
	//printf("npar = %d \n", npartition);
	int k=0;
	for(i=1;i<argc-1;i++)
	{
		if(!strcmp(argv[i], "-p"))
		{
			if(!atoi(argv[i+1]) || atoi(argv[i+1]) < 0)
			{
				fprintf(stderr, "Erreur: L'argument -p doit être suivi par un nombre positif \n");
				exit(-1);
			}
			partition[k] = atoi(argv[i+1]);
			k++;
		}
	}
	
	for(i = 0; i<npartition;i++)
	{
		if(partition[i] < 0)
		{
			fprintf(stderr, "Erreur: La taille des partitions ne peut pas être négative\n");
				exit(-1);
		}
	}
	if(atoi(argv[argc-1]) == 0) // Si le dernier argument n'est pas un nombre alors on a donné le nom du disque
	{						// en parametre
		nom = argv[argc-1];
	}
	else
	{
		nom = "disk.tfs";
	}

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

	int offset = 4;
	disk_id d;
	d=malloc(sizeof(disk_id_s));
	
	block first_block = malloc(1024);

	char* n_little = toLittleEndian(npartition); 

	//printf("%s", nom);
	start_disk(nom, &d);
	read_block(d, first_block, 0);


	int tmp = 0;
	for(i=0;i<npartition;i++)
	{
		tmp+= partition[i];
	}
	char* sub = blocksub(first_block,0);
	int taille_disk = data_to_int(sub, 4);
	//printf("-> %d\n", taille_disk);
	if(tmp > taille_disk-1)
	{
		fprintf(stderr, "Erreur: La taille totale des partitions dépasse la taille du disque \n");
		exit(-1);
	}
	ajouter_infos(first_block,offset,n_little, sizeof(n_little));
	offset += 4;

	write_block(d, first_block,0);

	for(i = 0; i<npartition;i++)
	{
		printf("Creation de la partition : %d de taille %d bloc(s)\n", i, partition[i]);
		char* p = toLittleEndian(partition[i]);
		ajouter_infos(first_block,offset,p, sizeof(p));
		offset +=4;
	}
	stop_disk(d);
	return 0;
}

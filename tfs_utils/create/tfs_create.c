#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "tfs_utils.h"

int main(int argc, char* argv[])
{
	uint32_t size;
	disk_id d;
	block b;
	block f;
	char* nom;

	if(argc != 3)
	{
		if(argc != 4){
			fprintf(stderr, "Erreur: le nombre d'argument est invalide \n");
			exit(-1);
		}
	}
	
	if(strcmp(argv[1],"-s"))
	{
		fprintf(stderr, "Erreur: L'argument -s doit être présent \n");
		exit(-1);
	}
	
	if(!atoi(argv[2]))
	{
		fprintf(stderr, "Erreur: Merci de founir un nombre valide pour le flag -s \n");
		exit(-1);
	}
	
	size = atoi(argv[2]);
	
	if(size<0)
	{
		fprintf(stderr, "Erreur: La taille doit être positive\n");
		exit(-1);
	}

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
	stop_disk(d);
	printf("Creation du disque %s de taille %d blocs (%d octets) \n", nom, size, size*BLOCK_SIZE);
	return 0;
}

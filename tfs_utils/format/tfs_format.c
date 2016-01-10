#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ll.h"
#include "tfs_utils.h"

#define TTTFS_MAGIC_NUMBER 0x31534654
#define TTTFS_VOLUME_BLOCK_SIZE 1024

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

	if(access(nom, F_OK))
	{
		fprintf(stderr, "Erreur: Le fichier n'existe pas\n");
		exit(-1);
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
	int filetable_long = file_count/16; // 16 = 1024/64
	if(file_count%16 != 0)
	{
		filetable_long++;
	}
	if(filetable_long+2 > taille)
	{
		fprintf(stderr, "Erreur: La partition ne peut pas stocker autant de fichier\n");
		exit(-1);
	}
	int free_block_count= (taille-filetable_long)-2;
	int next_free = filetable_long+2+1;


	block b_partition = malloc(BLOCK_SIZE);
	read_block(d, b_partition, pos);
	
	//
	//	TTTFS Description Block
	//
	int offset_0 = 0;
	
	char* MAGIC_NUM = toLittleEndian(TTTFS_MAGIC_NUMBER);
	char* VOLUME_BLOCK = toLittleEndian(TTTFS_VOLUME_BLOCK_SIZE);
	char* BLOCK_COUNT = toLittleEndian(taille);
	char* FREE_BLOCK = toLittleEndian(free_block_count);
	char* NEXT_FREE = toLittleEndian(next_free);
	char* MAX_FILE = toLittleEndian(file_count);
	char* FREE_FILE = toLittleEndian(file_count-1);
	char* FIRST_FREE = toLittleEndian(1);

	ajouter_infos(b_partition,offset_0, MAGIC_NUM, sizeof(MAGIC_NUM));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, VOLUME_BLOCK, sizeof(VOLUME_BLOCK));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, BLOCK_COUNT, sizeof(BLOCK_COUNT));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, FREE_BLOCK, sizeof(FREE_BLOCK));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, NEXT_FREE, sizeof(NEXT_FREE));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, MAX_FILE, sizeof(MAX_FILE));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, FREE_FILE, sizeof(FREE_FILE));
	offset_0+=4;
	ajouter_infos(b_partition,offset_0, FIRST_FREE, sizeof(FIRST_FREE));


	write_block(d,b_partition,pos);


	//
	//	TTTFS File Block
	//

	int p_fichier = 0;
	int i_fichier = 0;
	int offset_f=60;
	block bf = malloc(TTTFS_VOLUME_BLOCK_SIZE);
	char* nf;
	while(i_fichier < file_count)
	{
		if(offset_f+64 > 1024)
		{
			nf = toLittleEndian(i_fichier+1);
			ajouter_infos(bf, offset_f,nf,sizeof(nf));
			write_block(d,bf, pos+p_fichier+1);
			bf = malloc(TTTFS_VOLUME_BLOCK_SIZE);
			offset_f = 60;
			p_fichier++;
		}
		if(i_fichier+1 == file_count)
		{
			nf =toLittleEndian(i_fichier);
		}else
		{
			nf = toLittleEndian(i_fichier+1);
		}
		printf("%d\n pos offset_f %d \n", nf[0], offset_f);
		ajouter_infos(bf, offset_f,nf,sizeof(nf));
		i_fichier+=1;
		offset_f += 64;

	}
	write_block(d,bf,pos+p_fichier+1);

	//
	//	TTTFS Data Blocks
	//
	block bd = malloc(TTTFS_VOLUME_BLOCK_SIZE);
	int i_fb = 0;
	int ii = filetable_long+1;
	char* end;
	while(i_fb<free_block_count+1)
	{
		bd = malloc(TTTFS_VOLUME_BLOCK_SIZE);
		if(i_fb+1==free_block_count+1)
		{
			end = toLittleEndian(ii);
		}else
		{
			end = toLittleEndian(ii+1);
			printf("-> %d", end[0]);
		}
		ajouter_infos(bd, 1019,end, sizeof(end));
		write_block(d,bd,pos+p_fichier+1+i_fb+1);
		ii++;
		i_fb++;
	}


	//
	//	Racine (Filetable)
	//

	char* r_taille = toLittleEndian(64);
	char* r_type = toLittleEndian(1);
	char* r_empty = toLittleEndian(0);
	char* r_fb = toLittleEndian(filetable_long+1);
	int truc;
	block r_block;
	r_block = malloc(TTTFS_VOLUME_BLOCK_SIZE);
	read_block(d,r_block,pos+1);
	int r_offset = 0;
	ajouter_infos(r_block, r_offset,r_taille,sizeof(taille));
	r_offset +=4;
	ajouter_infos(r_block, r_offset,r_type,sizeof(r_type));
	r_offset +=4;
	ajouter_infos(r_block, r_offset,r_fb,sizeof(r_fb));
	for(truc=0;truc<10;truc++)
	{
	ajouter_infos(r_block, r_offset,r_empty,sizeof(r_empty));
	r_offset +=4;
	}
	ajouter_infos(r_block, r_offset,r_empty,sizeof(r_empty));
	r_offset +=4;
	ajouter_infos(r_block, r_offset,r_empty,sizeof(r_empty));
	r_offset +=4;
	ajouter_infos(r_block, r_offset,r_type,sizeof(r_type));
	r_offset +=4;
	write_block(d,r_block,pos+1);
	

	//
	//	Racine (Data)
	//
	block d_block;
	d_block = malloc(TTTFS_VOLUME_BLOCK_SIZE);
	d_block[4] = '.';
	d_block[5] = '\0';
	d_block[36] = '.';
	d_block[37]  = '.';
	d_block[38] = '\0';
	write_block(d, d_block,filetable_long+pos+1);

	stop_disk(d);
	return 0;
}

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
	//delete_free_block(d, 0, 3);
	putDirEntry(d,0,2);
	removeEntry(d,0,1);
	stop_disk(d);
	return 0;
}
int removeEntry(disk_id di, int volume, int n)
{
	int offset = getvolumedeb(di,volume);
	block bl = malloc(BLOCK_SIZE);
	int r = n%16;
	int d = n/16;
	read_block(di, bl,((offset+d*1024)/1024)+1);
	int j;
	if(r==0)
	{
		j=0;
	}
	else
	{
		j = 64*r;
	}
	printf("=>> %d", j);
/*
	int k;
	int temp;
	block empty = malloc(BLOCK_SIZE);
	for(k=0;k<10;k++)
	{
		temp = data_to_int(blocksub(bl,j+(16+k*4)),4);

		if(temp!=0){
			printf("Libération du bloc %d", temp);
			write_block(di,empty,offset+temp);
			add_free_block(di,volume, (1024*temp+offset)/1024);
		}
	}
	/*
	int w = data_to_int(blocksub(bl,j+56),4);
	if(w!=0)
	{

		block s = malloc(BLOCK_SIZE);
		read_block(di,s, (1024*j+offset)/1024);
		int off = 0;
		int nn;
		while(off<1024)
		{
			nn = data_to_int(blocksub(s,off),4);
			if(nn!=0)
			{
				write_block(di,empty,(1024*nn+offset)/1024);
				add_free_block(di,volume,(1024*nn+offset)/1024);
			}
			off+=4;
		}
	}/*
	int l =  data_to_int(blocksub(bl,j+60),4);
	if(l!=0)
	{

		block s = malloc(BLOCK_SIZE);
		block s2 = malloc(BLOCK_SIZE);
		read_block(di,s, (1024*j+offset)/1024);
		int off2 = 0;
		int off3=0;
		int nn2;
		int nn3;
		while(off2<1024)
		{
			s2 = malloc(BLOCK_SIZE);
			nn2 = data_to_int(blocksub(s,off2),4);
			if(nn2!=0){
			while(off3<1024)
			{
				nn3 = data_to_int(blocksub(s,off3),4);
				if(nn3!=0)
				{
					write_block(di,empty,(1024*nn3+offset)/1024);
					add_free_block(di,volume,(1024*nn3+offset)/1024);
				}
				off3+=4;
			}
			}
			read_block(di,s2,(1024*nn2+offset)/1024);
			add_free_block(di,volume,(1024*nn2+offset)/1024);
			off2++;
		}
		write_block(di,empty,((1024*nn3+offset)/1024));
	}	*/
	ajouter_infos(bl,0+j, toLittleEndian(32), 4);
	ajouter_infos(bl,4+j, toLittleEndian(1), 4);
	ajouter_infos(bl,8+j, toLittleEndian(0), 4);
	ajouter_infos(bl,12+j, toLittleEndian(0), 4);
	ajouter_infos(bl,16+j, toLittleEndian(0), 4);
	ajouter_infos(bl,20+j, toLittleEndian(0), 4);
	ajouter_infos(bl,24+j, toLittleEndian(0), 4);
	ajouter_infos(bl,28+j, toLittleEndian(0), 4);
	ajouter_infos(bl,32+j, toLittleEndian(0), 4);
	ajouter_infos(bl,36+j, toLittleEndian(0), 4);
	ajouter_infos(bl,40+j, toLittleEndian(0), 4);
	ajouter_infos(bl,44+j, toLittleEndian(0), 4);
	ajouter_infos(bl,48+j, toLittleEndian(0), 4);
	ajouter_infos(bl,52+j, toLittleEndian(0), 4);
	ajouter_infos(bl,56+j, toLittleEndian(0), 4);


	return 0;
}

int putDirEntry(disk_id d, int volume, int pred)
{
	int offset = getvolumedeb(d,volume);
	if(getFreeBlock(d, volume) == 0 || getFreeFile(d, volume) == 0)
	{
		return 1;
	}

	block bl = malloc(BLOCK_SIZE);
	printf("BLOCK No : %d",((offset+(getNextFreeF(d, volume)/16)*1024)/1024)+1);
	int dd = ((offset+(getNextFreeF(d, volume)/16)*1024)/1024)+1;
	read_block(d,bl,((offset+(getNextFreeF(d, volume)/16)*1024)/1024)+1);
	int nff=getNextFreeF(d, volume);
	int r = getNextFreeF(d, volume)%16;
	int ne;
	if(r==0)
	{
		ne = 60;
	}
	else
	{
		ne = (r*64)+60;
	}
	int nex = data_to_int(blocksub(bl,ne),4);
	int j;
	if(r==0)
	{
		j=0;
	}
	else
	{
		j = 64*r;
	}
	int  block_free = getNextFreeB(d,volume);

	ajouter_infos(bl,0+j, toLittleEndian(0), 4);
	ajouter_infos(bl,4+j, toLittleEndian(0), 4);
	ajouter_infos(bl,8+j, toLittleEndian(0), 4);
	ajouter_infos(bl,12+j, toLittleEndian(0), 4);
	ajouter_infos(bl,16+j, toLittleEndian(0), 4);
	ajouter_infos(bl,20+j, toLittleEndian(0), 4);
	ajouter_infos(bl,24+j, toLittleEndian(0), 4);
	ajouter_infos(bl,28+j, toLittleEndian(0), 4);
	ajouter_infos(bl,32+j, toLittleEndian(0), 4);
	ajouter_infos(bl,36+j, toLittleEndian(0), 4);
	ajouter_infos(bl,40+j, toLittleEndian(0), 4);
	ajouter_infos(bl,44+j, toLittleEndian(0), 4);
	ajouter_infos(bl,48+j, toLittleEndian(0), 4);
	ajouter_infos(bl,52+j, toLittleEndian(0), 4);
	ajouter_infos(bl,56+j, toLittleEndian(getNextFreeF(d,volume)), 4);

	setNextFreeF(d, volume, nex);


	block monblock = malloc(BLOCK_SIZE);
	ajouter_infos(monblock,0,toLittleEndian(nff),4);
	monblock[4] = '.';
	monblock[5] = '\0';
	ajouter_infos(monblock,64,toLittleEndian(pred),4);
	monblock[65] = '.';
	monblock[66] = '.';
	monblock[67] = '\0';

	delete_free_block(d,volume, block_free);
	write_block(d, monblock,block_free+1);
	write_block(d,bl,dd);
	return 0;
}
int setNextFreeF(disk_id d, int volume, int x)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	char* xc = toLittleEndian(x);
	ajouter_infos(blk,28,xc,sizeof(xc));
	return 0;
}
int getNextFreeF(disk_id d, int volume)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	int nf = data_to_int(blocksub(blk,28),4);
	return nf;
}
int getNextFreeB(disk_id d, int volume)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	int nf = data_to_int(blocksub(blk,16),4);
	return nf;
}
int getFreeFile(disk_id d, int volume)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	int nf = data_to_int(blocksub(blk,24),4);
	return nf;
}
int getFreeBlock(disk_id d, int volume)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	int nf = data_to_int(blocksub(blk,12),4);
	return nf;
}
int delete_free_block(disk_id d, int volume, int b)
{
	int off = getvolumedeb(d,volume);
	block blk = malloc(BLOCK_SIZE);
	read_block(d, blk,off/1024);
	int nf = data_to_int(blocksub(blk,12),4);
	int ff = data_to_int(blocksub(blk,16),4);
	int c = 0;
	int pro =0;
	if(nf !=0){
		if(ff==b)
		{
			if(nf==1){
				ajouter_infos(blk, 16, toLittleEndian(0), sizeof(toLittleEndian(0)));
				printf("hello2\n");
			}
			else{
				block aux = malloc(BLOCK_SIZE);
				read_block(d,aux,(off+(ff*1024))/1024);
				pro = data_to_int(blocksub(aux,1020),4);
				printf("hello1\n");
				//ajouter_infos(blk, 16, toLittleEndian(n), sizeof(toLittleEndian(n)));
			}
		}else
		{
			int suivant =ff;
			block aux = malloc(BLOCK_SIZE);
			int k = 0;
			while(suivant != b)
			{
				c=suivant;
				read_block(d, aux, (off+(1024*suivant))/1024);
				suivant = data_to_int(blocksub(aux,1020),4);
				if(k==0)
				{
					pro = suivant;
					printf("pro : %d", pro);

				}
				printf("boucle\n");
			}
			block next = malloc(BLOCK_SIZE);
			read_block(d, next, (off+(1024*suivant))/1024);
			int ln = data_to_int(blocksub(next,1020),4);
			if(ln == suivant)
			{
				char* cc = toLittleEndian(c);
				ajouter_infos(aux, 1020, cc, sizeof(cc));
				write_block(d,aux,(off+(c*1024))/1024);
			}
			else
			{
				ajouter_infos(aux, 1020, blocksub(next,1020), sizeof(blocksub(next,1020)));
				write_block(d,aux,(off+(c*1024))/1024);
			}
		
		}
		ajouter_infos(blk, 12, toLittleEndian(nf-1), 4);
		printf("PRO %d", pro);
		ajouter_infos(blk, 16, toLittleEndian(pro), 4);
		write_block(d,blk,off/1024);
	}
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
	ajouter_infos(blk, 12, toLittleEndian(nf+1), 4);

	int ff = data_to_int(blocksub(blk,16),4);
	printf("premier blokc! %d \n", ff);

	if(ff == 0)
	{
		ajouter_infos(blk, 16, toLittleEndian(b), sizeof(toLittleEndian(b)));
	}
	else
	{
		int suivant = ff;
		read_block(d, aux, (off+(1024*ff))/1024);
		int ln = data_to_int(blocksub(aux,1020),4);
		while(ln != suivant)
		{
			ln = suivant;
			suivant = data_to_int(blocksub(aux,1020),4);
			block aux = malloc(BLOCK_SIZE);
			printf("Lecture du block : encours: %d suivant: %d\n", ln, suivant);
			read_block(d, aux, (off+(1024*ln))/1024);
			
		}
		write_block(d,blk,off/1024);
		ajouter_infos(aux, 1020, toLittleEndian(b), sizeof(toLittleEndian(b)));
		write_block(d, aux, (off+(1024*ln))/1024);
		printf("ecriture sur le block %d \n de la valeur %d", (off+(1024*ln))/1024, b);
		block bb = malloc(BLOCK_SIZE);
		read_block(d, bb, (off+1024*b)/1024);
		ajouter_infos(bb, 1020, toLittleEndian(b), sizeof(toLittleEndian(b)));
		write_block(d,bb,(off+1024*b)/1024);
	}
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include "ll.h"
#include "tfs_utils.h"


/*
int main()
{
	uint32_t t = 3;
	toLittleEndian(t);
	return 0;
}*/

char* toLittleEndian(uint32_t n)
{
	unsigned char* v = malloc(4);
	n = htole32(n);
	v[3]=(n>>24)& 0x00FF;
	v[2]=(n>>16)& 0xFF;
	v[1]=(n>>8)& 0xFF;
	v[0]=n;
	printf("\n %x %x %x %x\n", v[0], v[1], v[2], v[3]);
	return v;
}
int ajouter_infos(block org, int offset, char* dest, int dest_size)
{
	int i = 0;
	int k = offset;
	for(i=0;i<dest_size;i++)
	{
		org[++k] = dest[i];
	}
	return 0;
}
int data_to_int(char* t, int size)
{
	char aux[size]; // On crée un tableau annexe
	int i;
	int k = 0;

	for(i=size-1;i>=0;i--)
	{
		aux[i] = t[k];
		k++;
		printf("t[%d] = %p \n", k, aux[i]);
	}
	
	uint32_t num = (uint32_t)aux[0] << 24 |
      (uint32_t)aux[1] << 16 |
      (uint32_t)aux[2] << 8  |
      (uint32_t)aux[3];


	printf("\n N = %d\n", num);
	return (int)num;
}
char* blocksub(block b, int start)
{
	char* aux;
	aux = malloc(4*sizeof(char));
	aux[0] = b[0+start];
	aux[1] = b[1+start];
	aux[2] = b[2+start];
	aux[3] = b[3+start];
	//printf("\naux = %d\n", sizeof(aux));
	return aux;
}
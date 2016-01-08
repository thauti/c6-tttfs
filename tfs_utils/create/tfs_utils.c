#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
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

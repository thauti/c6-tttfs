#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>


char* toLittleEndian(uint32_t n);
int ajouter_infos(block org, int offset, char* dest, int dest_size);
int data_to_int(char* t, int size);
char* blocksub(block b, int start);
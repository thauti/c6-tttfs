#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include "ll.h"

char* toLittleEndian(uint32_t n);
int ajouter_infos(block org, int offset, char* dest, int dest_size)
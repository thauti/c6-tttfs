#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ll.h>

typedef block* Volume;

int getvolumedeb(disk_id d, int part);
int add_free_block(disk_id d,int volume, int b);
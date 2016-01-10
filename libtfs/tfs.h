#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ll.h>

typedef block* Volume;

int getvolumedeb(disk_id d, int part);
int delete_free_block(disk_id d, int volume, int b);
int add_free_block(disk_id d,int volume, int b);
int getFreeBlock(disk_id d, int volume);
int getNextFreeF(disk_id d, int volume);
int getFreeFile(disk_id d, int volume);
int getNextFreeB(disk_id  d, int volume);
int putDirEntry(disk_id d, int volume, int pred);
int setNextFreeF(disk_id d, int volume, int x);
int removeEntry(disk_id di, int volume, int n);
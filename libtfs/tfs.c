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
	start_disk("disk.tfs", &d);
	getVolume(d,0);
	return 0;
}

Volume getVolume(disk_id id, int part)
{
	block first = malloc(1024);
	read_block(id , first,0);
	printf("%d",data_to_int(blocksub(first,0),4));
	char* a = toLittleEndian(8);
	ajouter_infos(first,0, a, sizeof(a));
	write_block(id,first,0);
	stop_disk(id);
	return NULL;
}
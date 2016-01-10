#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ll.h>

typedef block* Volume;

Volume getVolume(disk_id id, int part);
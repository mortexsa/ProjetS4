#include "navalmap.h"
#include "nm_rect.h"
#include "lire.h"
#include "jouer.h"
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>




int main(int argv[],char *argc){
	
	navalmap_t *map;
	map = lireFichier("test.txt");
	initNavalMapLib ();
	placeRemainingShipsAtRandom(map);
	printf("x : %d y : %d\n", map->shipPosition[0].x, map->shipPosition[0].y);
	mov(map,0);
	printf("x : %d y : %d\n", map->shipPosition[0].x, map->shipPosition[0].y);
	free_navalmap(map);
	return 0;
}
	

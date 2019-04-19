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




int main(int argc,char **argv){
	initNavalMapLib ();
	

	navalmap_t *map;
	
	map = lireFichier(argv[1]);
	
	
	placeRemainingShipsAtRandom(map); 								    // place les navire dans la map

	for (int i = 0; i < map->nbShips; i++) {
		printf(" Navire %d : (%d,%d)\n", i, map->shipPosition[i].x, map->shipPosition[i].y);
	}
	
	radar(map,0);  														// le radar 
	//atk(map,0);  														// l'attaque basique
	mov(map,0);   														// deplacement 
	reparation(map,0); 													// reparation du navir fait gagner 25C
	//Process(map); 
	
	free_navalmap(map);
	return 0;
}
	

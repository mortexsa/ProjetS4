#include "navalmap.h"
#include "jouer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include <math.h>

void initNavalMapLib () {

		srand (time (NULL) );
		
}

navalmap_t * init_navalmap (const map_t	mapType,const coord_t mapSize,const int nbShips) {
	
	navalmap_t	* nmap;
	int	j;
	nmap = malloc (sizeof (navalmap_t) );
	nmap->type = mapType;
	nmap->size = mapSize;
	nmap->nbShips = nbShips;
	nmap->shipPosition = malloc (nmap->nbShips * sizeof (coord_t) );
	
	nmap->shipCarac = malloc (nmap->nbShips * sizeof (shipParam *) );
	
	for (j = 0; j < nbShips; ++j) {
		nmap->shipPosition [j] .x = -1;
		nmap->shipCarac [j].posEnnemie.x = -1;
		nmap->shipCarac [j].posEnnemie.y = -1;
	}

	for (int i=0; i<nbShips; ++i) {
		 nmap->shipCarac[i].etat=inconnu;
	}
	
	nmap->map = malloc (mapSize.y * sizeof (entityid_t *) );

	

	for (j = 0; j < mapSize.y; ++j)
		nmap->map [j] = malloc (mapSize.x * sizeof (entityid_t) );

	switch (mapType) {
		case MAP_RECT:
			nmap->initEntityMap = rect_initEntityMap;
			nmap->isMovePossible = rect_isMovePossible;
			nmap->getTargets = rect_getTargets;
			break;
		default:
			printf ("Map type is not recognized. Type 'rectangle' is selected.\n");
			nmap->initEntityMap = rect_initEntityMap;
			nmap->isMovePossible = rect_isMovePossible;
			nmap->getTargets = rect_getTargets;
			break;
	}

	nmap->initEntityMap (nmap);
	

	return nmap;
}

void free_navalmap (
	navalmap_t	* nmap) {
	int	j;
	for (j = 0; j < nmap->size.y; ++j)
		free (nmap->map [j]);
	free (nmap->shipCarac);
	free (nmap->map);
	free (nmap->shipPosition);
	free (nmap);
}

void moveShip (navalmap_t	* nmap,const int	shipID,const coord_t moveVec) {
	if (! nmap->isMovePossible (nmap, shipID, moveVec) ) return;

	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .type = ENT_SEA;
	nmap->shipPosition [shipID] .x += moveVec.x;
	nmap->shipPosition [shipID] .y += moveVec.y;
	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .type = ENT_SHIP;
	nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .id = shipID;
}

void placeRemainingShipsAtRandom (navalmap_t	* nmap) {
	int	i, j, k;
	for (k = 0; k < nmap->nbShips; ++k) {
		
		int	found = 0;

		if (nmap->shipPosition [k] .x != -1) continue;

		while (! found) {
			i = rand () % nmap->size.x;
			j = rand () % nmap->size.y;

			if (nmap->map [j][i] .type == ENT_SEA) found = 1;
		}

		nmap->shipPosition [k] .x = j;
		nmap->shipPosition [k] .y = i;
		nmap->map [j][i] .type = ENT_SHIP;
		nmap->map [j][i] .id = k;
	}
}

void placeShip (
	navalmap_t* nmap,
	const int shipID,
	const coord_t pos) {
	
		if (shipID >= nmap->nbShips) return;
		if (pos.x < 0 || pos.x >= nmap->size.x || pos.y < 0 || pos.y >= nmap->size.y) return;

		if (nmap->map [pos.y][pos.x] .type == ENT_SHIP) {
			printf ("Placement for ship #%d is not possible.\n", shipID);
			return;
	}

	nmap->shipPosition [shipID] .x = pos.x;
	nmap->shipPosition [shipID] .y = pos.y;
	nmap->map [pos.y][pos.x] .type = ENT_SHIP;
	nmap->map [pos.y][pos.x] .id = shipID;
}
int isAtkPossible(navalmap_t * nmap,const int	shipID,	const coord_t atkVec) {    		
	int distance = sqrt((atkVec.x * atkVec.x)+(atkVec.y*atkVec.y));
	if (shipID >= nmap->nbShips) return 0;
	
	

	return (nmap->shipPosition [shipID] .x + atkVec.x >= 0
		 && nmap->shipPosition [shipID] .x + atkVec.x < nmap->size.x
		 && nmap->shipPosition [shipID] .y + atkVec.y >= 0
		 && nmap->shipPosition [shipID] .y + atkVec.y < nmap->size.y
		 && distance > 2 && distance < 4);
}
void Process(navalmap_t *nmap ){
	const int shipID;
	pid_t pid;
	int ret;
	int desctipteurTube[2];



	ret = pipe(desctipteurTube);
	
	if (pipe(desctipteurTube) == -1) {  						
    			printf("Erreur pipe");  								 
    			exit(1); 												
  			}
	// Processus fils 
	
	for(int i = 0; i <nmap->nbShips; i++){
		
		if((pid = fork()) == 0){  

			
		//	write(desctipteurTube[i],Algorithme_deJeu(nmap,shipID),256);
			sleep(1);
			
			exit(0);
		}
	}
	// Processus père
	
	for (int j= 0; j <nmap->nbShips ; j++)
	{
		int p;
		
		
		exit(pid);
		wait(&pid);
		
		p = WEXITSTATUS(pid);
		
	}
}
			 
void Algorithme_deJeu(navalmap_t *nmap , const int shipID){

	
	coord_t attackVec = {nmap->shipCarac[shipID].posEnnemie.x - nmap->shipPosition[shipID].x, nmap->shipCarac[shipID].posEnnemie.y - nmap->shipPosition[shipID].y };

	if (nmap->shipCarac[shipID].etat == inconnu){

		radar(nmap,shipID);
	
	}
	else if (isAtkPossible(nmap, shipID, attackVec)){
		
		atk(nmap,shipID);
	
	}else {
	
		mov(nmap,shipID);
	
	}
}
			

			

	
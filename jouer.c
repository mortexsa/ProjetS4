#include "jouer.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



void non(navalmap_t * nmap, const int shipID) {
	nmap->shipCarac[shipID].Kmax -= 1;
	printf("  -  J%d n'effectue aucune action\n", shipID+1);
}

void mov(navalmap_t * nmap, const int shipID) {
	initNavalMapLib ();
	int dep = (rand() % 2) + 1;
	int direction;
	coord_t c;
	do {
		c.x = 0;
		c.y = 0;
		direction = rand() % 4;
		switch(direction){
			case 0:
				c.x += dep;
				break;
			case 1:
				c.x -= dep;
				break;
			case 2:
				c.y += dep;
				break;
			default:
				c.y -= dep;
				break;
		}
	} while(!nmap->isMovePossible (nmap, shipID, c));
	moveShip (nmap,shipID,c);
	nmap->shipCarac[shipID].Kmax -= 2;
	printf("  -  J%d se deplace en (%d, %d)\n", shipID+1, nmap->shipPosition[shipID].x, nmap->shipPosition[shipID].y);
}

void atk(navalmap_t * nmap, const int shipID) {
	int dep = (rand() % 3) + 2;
	int direction;
	coord_t c;
	do {
		c.x = nmap->shipPosition[shipID].x;
		c.y = nmap->shipPosition[shipID].y;
		direction = rand() % 4;
		switch(direction){
			case 0:
				c.x += dep;
				break;
			case 1:
				c.x -= dep;
				break;
			case 2:
				c.y += dep;
				break;
			default:
				c.y -= dep;
				break;
		}
	} while (c.x < 0 || c.x >= nmap->size.x || c.y < 0 || c.y >= nmap->size.y);
	
}
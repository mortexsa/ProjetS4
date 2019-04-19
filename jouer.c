#include "jouer.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



void non(navalmap_t * nmap, const int shipID) {       //si le joueur n'effectue aucune action il perd 1 K
	
	nmap->shipCarac[shipID].Kmax -= 1;
	
	printf("  -  J%d n'effectue aucune action\n", shipID+1);
}


void mov(navalmap_t * nmap, const int shipID) {   // fonction move permet le deplacement vers un navire ennemie 
												  // avance de 2 case si le navire ennemie est a une distance 2>= ou 1 case sinon		
	

	initNavalMapLib ();
	
	int distance,distance1;
	
	coord_t deplacement;
	coord_t posM = nmap->shipPosition[shipID] ;
	coord_t posE = nmap->shipCarac[shipID].posEnnemie;
	
	if (posM.x == posE.x && posM.y > posE.y){
		
		distance = posE.y - posM.y;
		deplacement.x = 0;
		
		if(distance <= -2 ) deplacement.y = -2;
		
		else deplacement.y = -1;	  

	}else if (posM.x == posE.x && posM.y < posE.y){
		
		distance = posE.y - posM.y;
		deplacement.x = 0;
		
		if(distance >= 2 ) deplacement.y = 2;
		
		else deplacement.y = 1;
	
	}else if (posM.x < posE.x && posM.y == posE.y){
		
		distance = posE.x - posM.x;
		deplacement.y = 0;
		
		if(distance >= 2 ) deplacement.x = 2;
		
		else deplacement.x = 1;
	
	}else if (posM.x > posE.x && posM.y == posE.y){
		
		distance = posE.x - posM.x;
		deplacement.y = 0;
		
		if(distance <= -2 ) deplacement.x = -2;
		
		else deplacement.x = -1;
	
	}else if (posM.x > posE.x && posM.y > posE.y){
		
		distance = posE.x - posM.x;
		distance1 = posE.y - posM.y;
		
		if(distance <= -2 ) deplacement.x = -2;
		
		else deplacement.x = -1;
		
		if(distance1 <= -2 ) deplacement.y = -2;
		
		else deplacement.y = -1;
	
	}else if (posM.x < posE.x && posM.y < posE.y){
		
		distance = posE.x - posM.x;
		distance1 = posE.x - posM.x;
		
		if(distance >= 2 ) deplacement.x = 2;
		
		else deplacement.x = 1;
		
		if(distance1 >= 2 ) deplacement.y = 2;
		
		else deplacement.y = 1;
	
	}else if (posM.x > posE.x && posM.y < posE.y){
		
		distance = posE.x - posM.x;
		distance1 = posE.x - posM.x;
		
		if(distance <= -2 ) deplacement.x = -2;
		
		else deplacement.x = -1;
		
		if(distance1 >= 2 ) deplacement.y = 2;
		
		else deplacement.y = 1;
	
	}else if (posM.x < posE.x && posM.y > posE.y){
		
		distance = posE.x - posM.x;
		distance1 = posE.x - posM.x;
		
		if(distance >= 2 ) deplacement.x = 2;
		
		else deplacement.x = 1;
		
		if(distance1 <= -2 ) deplacement.y = -2;
		
		else deplacement.y = -1;
	}
		
	moveShip (nmap,shipID,deplacement);
	
	nmap->shipCarac[shipID].Kmax -= 2;
	
	printf("  -  J%d se deplace en (%d, %d)\n", shipID, nmap->shipPosition[shipID].x, nmap->shipPosition[shipID].y);
}
	
	
 
void atk(navalmap_t * nmap, const int shipID) {   // fonction attaque qui permet l'attaque d'une cible apres reperage
	
	coord_t atkVec;

	if (isAtkPossible(nmap,shipID,atkVec)){
		
		nmap->shipCarac[shipID].Kmax -= 5;
		
		for (int i=0;i<nmap->nbShips;i++){
			
			if ((nmap->shipPosition[i].x == nmap->shipPosition[shipID].x + atkVec.x) && (nmap->shipPosition[i].y == nmap->shipPosition[shipID].y + atkVec.y) ){
			
				nmap->shipCarac[i].Cmax -= 20;
			}
		
		printf("  -  J%d en postion (%d,%d) a était toucher.\n",i,nmap->shipPosition[i].x,nmap->shipPosition[i].y);	
		
		}
	}
}


void radar(navalmap_t * nmap,const int shipID){        // fonction radar renvoie la postion du bateau a proximité
	
	int trouver = 0;
	int dist = 0;
	
	int	* nbShips = malloc(sizeof(int));
	*nbShips = 0;
	
	int *T;
	
	while (!trouver){
		
		T=rect_getTargets (nmap,nmap->shipPosition[shipID],dist,nbShips);
		
		if(T != NULL && T[0] != shipID){
			
			trouver = 1;
		}

		dist++;

	}
	
	if(T[0] != shipID) {
		
		printf ("  -  ID du navire reperé : %d\n",T[0]);
		
		nmap->shipCarac[shipID].posEnnemie = nmap->shipPosition[T[0]];
	
	}else {
		
		printf ("  -  ID du navire reperé : %d\n",T[1]);
		
		nmap->shipCarac[shipID].posEnnemie = nmap->shipPosition[T[1]];	
	} 
	nmap->shipCarac[shipID].etat = connu;
}


void reparation(navalmap_t * nmap,const int shipID){      // fonction qui repare le navir en action
	
	nmap->shipCarac[shipID].Cmax += 25;
	
	nmap->shipCarac[shipID].Kmax -= 20;

	printf("  -  Le J%d gagne 25C\n", shipID);
	
	printf(" Navire %d : %dC\n", shipID,nmap->shipCarac[shipID].Cmax);
}
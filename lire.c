#include "lire.h"

navalmap_t * lireFichier(char *nomFichier){
	int fd = open(nomFichier,O_RDONLY);
	char buffer[2];
	char stock[7][256] = {0};
	
	int stockEntier[6] = {0};
	int i = 0;
	int j = 0;
	while(read(fd,buffer,1) != 0)
	{
		if(buffer[0] == ';' || buffer[0] == '\n')
		{
			i = 0;
			j++;
		
		}else{
			
			stock[j][i] = buffer[0];
			i++;
		}
	}	
		
	for(i=0;i<7;i++){
		stockEntier[i]=atoi(stock[i+1]);
		
	}	
	// initialisation de la naval_map
	coord_t size={stockEntier[0],stockEntier[1]};

	navalmap_t *map;
	map_t mapType;
	if(strcmp(stock[0],"rectangle") == 0){
		mapType=MAP_RECT;
	}else{
		mapType=MAP_TOTAL;
	}
	map=init_navalmap(mapType,size,stockEntier[2]);

	for(int y = 0; y < map->nbShips ; y++) {
		map->shipCarac[y].Cmax = stockEntier[3];
		map->shipCarac[y].Kmax = stockEntier[4];
		map->shipCarac[y].nbTours = stockEntier[5];
	}

	return map;
}
#include "navalmap.h"
#include "nm_rect.h"
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
	
	int fd = open("test.txt",O_RDONLY);
	char buffer[2];
	char stock[8][256] = {0};
	
	int stockEntier[7] = {0};
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
		
		for(i=0;i<8;i++){
			stockEntier[i]=atoi(stock[i+1]);
			
		}	
		printf("%s",stock[0]);
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
		//printf("%c",map->type);
		
}
	

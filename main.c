#include "navalmap.h"
#include "nm_rect.h"
#include "lire.h"
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

	free_navalmap(map);
			
}
	

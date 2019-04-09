#ifndef _H_lire_
#define _H_lire_
#include "navalmap.h"
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


navalmap_t * lireFichier(char *nomFichier);

#endif

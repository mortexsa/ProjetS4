#ifndef _H_JOUER_
#define _H_JOUER_

#include "navalmap.h"

void non(navalmap_t * nmap, const int shipID);
void mov(navalmap_t * nmap, const int shipID);
void atk(navalmap_t * nmap, const int shipID);
void radar(navalmap_t * nmap,const int shipID);
void reparation(navalmap_t * nmap,const int shipID);
#endif

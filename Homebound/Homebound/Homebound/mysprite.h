#ifndef MYSPRITE_H
#define MYSPRITE_H

#include "gba.h"

// Defines
#define		PLAYERSHIP 0 //Player ship 

#define		PNUM 17

#define		PMAX 18

//#define		NUMTURRETS 4 

typedef struct tagSEntry		// structure for storing standard attributes about sprites
{
	u16 atr[3];
} SEntry;

typedef struct sOBJTurret
{
	int x; // x coords of turret
	int y; // y coords of turret
	int on; // 0 if off, gOAM[on] represents where this sprite is!, if on > 0;
} OBJTurret;




//Prototypes
void GBA_LoadSprites();
void GBA_LoadOBJPalette();

#endif

#include "mysprite.h"
#include "sprite.h"

#include "entity.h"

extern GBA_OAMEntry gOAM[128];// global for sprites
extern SEntry gOBJInfo[1];	// global for attributes of the sprite entities

u16* OBJpalette = OBJPaletteMem; // from define in GBA.h


void GBA_LoadOBJPalette()
{
	int loop;
	for (loop = 0; loop < 256; loop++)
		OBJpalette[loop] = entPalette[loop];	//entity palette
}

void GBA_LoadSprites()
{
	u16  i;
	u16  n = 512;
	u16 *c = (u16 *)(CHR_BASE + (32 * n));

	for (i = 0; i < 512; i++) // load the player ship
		*(c++) = entshipData[i];
	gOBJInfo[PLAYERSHIP].atr[2] = 512;
	gOBJInfo[PLAYERSHIP].atr[0] = COLOR_256 | SQUARE;
	gOBJInfo[PLAYERSHIP].atr[1] = SIZE_32;
}

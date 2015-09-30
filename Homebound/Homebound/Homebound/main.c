//Include Files

#include "gba.h"  //register data type defines
#include "screenmode.h"  //screen mode defines
#include "keypad.h" //keypad defines
#include "gfx.h"
#include "sfx.h"

#include "gfx/intro.h"
#include "gfx/menu.h"
#include "gfx/menubg.h"
#include "gfx/bg.h"
#include "gfx/score.h"
#include "gfx/player.h"
#include "gfx/asteroid.h"
#include "gfx/playerhit.h"
#include "gfx/playerbullet.h"
#include "gfx/pause.h"
#include "gfx/hud.h"
#include "gfx/number.h"
#include "gfx/gameover.h"
#include "gfx/credits.h"


#include "sfx/Bullhorn.h"

extern const SAMPLE Bullhorn;

//Defines
#define	GUYMOVE 3 //speed of char
#define NUMASTEROIDS 4 //Number of asteroids on screen
#define NUMPLAYERBULLETS 10 //max num player bullets

//Global Variables
u16* videoBuffer;					// which buffer do we write too (front or back)
u16* paletteMem = (u16*)0x5000000;	// 256 16 bit BGR values starting at 0x5000000

//sound 


//prototypes
void DoIntro(void);			// display the intro screen, and sleep for a second or two
void DoGame(void);			// run the game
void menu(void);			// the titlescreen/menu
void WaitForStart(void);	// waits for the start key to be pressed
void DrawStatusBar(int lives, int score); // draw the status bar at the bottom of the screen
void DrawBackground(int y);	// draw the scrolling background!
void DrawPlayer(int px, int py, int hit); //Draw the player ship
void DrawAsteroid(int ax[NUMASTEROIDS], int ay[NUMASTEROIDS], int as[NUMASTEROIDS]); // x, y and status of asteroid. 0 off 1 on
void DrawPlayerBullet(int ax[NUMPLAYERBULLETS], int ay[NUMPLAYERBULLETS], int as[NUMPLAYERBULLETS]); // x, y and status of bullet. 0 off 1 on
void DrawHUD(int life, int score);
void DrawNumber(int nx, int ny,int num);
void DrawGameOver(int score);


int main(void)
{
	SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //set mode 4, objects enabled
	init_sfx_system(); //turn on sound
	EraseScreen();



	while (1) // always stay in this loop
	{
#ifndef MENUOFF
		EraseScreen();
		menu(); //Draw menu
#endif
		DoGame(); // game loop
	}
	return 0;
}
//Menu Screen
void menu(void)
{
	int x, y;
	int toggle = 0; // 0 draw top, 1 draw bottom
	int redraw = 0; // do we need to redraw menu (0 no, 1 yes)
	
	int a_on = 0; // if a is being pressed before menu starts, wait to process till it is released
	u32 countFrame = 0; // for fixing up/down on keystrokes
	u32 tmpCount = 0;

	
	if ((!((*KEYS) & KEY_A)))
	{
		a_on = 1;
	}

	u16* srcPtr = (u16 *)&menubgData;
	u16* destBuffer = videoBuffer;
	u16* finalAdr = destBuffer + SCREENSIZE_U16;//screensize in u16 einheiten

	while (destBuffer < finalAdr)
	{
		*destBuffer++ = *srcPtr++;
	}
	for (x = 0; x < 256; x++)	// set the background palette
	{
		paletteMem[x] = menubgPalette[x];
	}
	WaitForVblank();
	Flip();
	FadeIn(2);

	while (1) // loops infinitely till they press start
	{
		countFrame++;

		if ((!((*KEYS) & KEY_UP)) || (!((*KEYS) & KEY_DOWN)))
		{
			if (tmpCount != 0)
			{
				tmpCount = countFrame - tmpCount;
				if (tmpCount > 8)
				{
					tmpCount = 0;
				}
				else
				{
					tmpCount = countFrame - tmpCount;
				}
			}
			if (tmpCount == 0)
			{
				tmpCount = countFrame;
				redraw = 1; // force to redraw menu!
				toggle = (toggle ? 0 : 1);
			}
		}
		if (redraw)
		{
			if (toggle) // draw Highscores
			{
			
				srcPtr = (u16 *)&menubgData;
				destBuffer = videoBuffer;
				finalAdr = destBuffer + SCREENSIZE_U16;
				while (destBuffer < finalAdr)
					*destBuffer++ = *srcPtr++;
				for (y = 0; y < menu_HEIGHT; y++)
					for (x = 0; x < (menu_WIDTH / 2); x++) // actual width 120
						PlotPixel(x + 30, y + 85, menuData[y*(menu_WIDTH / 2) + x]);
			}
			else // draw start game highlighted
			{
				srcPtr = (u16 *)&menubgData;
				destBuffer = videoBuffer;
				finalAdr = destBuffer + SCREENSIZE_U16;
				while (destBuffer < finalAdr)
				{
					*destBuffer++ = *srcPtr++;
				}
			}
			WaitForVblank();
			Flip();
		}
		if (((*KEYS) & KEY_A)) //A is pressed
		{
			a_on = 0;
		}

		if ((!((*KEYS) & KEY_START)) || (!((*KEYS) & KEY_A)))
		{
			if (((a_on != 1) && (!((*KEYS) & KEY_A))))
			{
				if (!toggle)
				{
					return; // they selected start game
				}
				if (!((*KEYS) & KEY_A))
				{
					a_on = 1;
				}
				//Draw the score screen
				FadeOut(2);
				for (x = 0; x < 256; x++)	// set the palette for credits screen
				{
					paletteMem[x] = creditsPalette[x];
				}
				for (y = 0; y < 160; y++)// draw the screen
				{
					for (x = 0; x < 120; x++)
					{
						PlotPixel(x, y, creditsData[y * 120 + x]);
					}
				}
				WaitForVblank();
				Flip();
				FadeIn(2);

				while (1)
				{
					if (!a_on)
					{
						break;
					}
					if (((*KEYS) & KEY_A))
					{
						a_on = 0;
					}
				}
				WaitForStart();
				if (!((*KEYS) & KEY_A))
				{
					a_on = 1;
				}
				FadeOut(2);
				//redraw the menu screen
				for (x = 0; x < 256; x++)	// restore the menu palette
				{
					paletteMem[x] = menubgPalette[x];
				}
				srcPtr = (u16 *)&menubgData;
				destBuffer = videoBuffer;
				finalAdr = destBuffer + SCREENSIZE_U16;
				while (destBuffer < finalAdr)
				{
					*destBuffer++ = *srcPtr++;
				}
				WaitForVblank();
				Flip();
				FadeIn(2);
				toggle = 0;
			}
		}
	} // end while (1)
}
	// loops infinitely till they press start
	void WaitForStart(void)
	{
		while (1) 
		{
			if ((!((*KEYS) & KEY_A)))
			{
				break;
			}
		}
	}

	void DrawBackground(int y)
	{
		int diffy;
		diffy = 320 - y;

		//set bg pallete
		int x;
		
		if (y > 160)
		{
			// draw the remaining
			u16* srcPtr = (u16 *)&bgData + y * 120;//contains the background color values 

			u16* destBuffer = videoBuffer;
			u16* finalAdr = destBuffer + (diffy * 120);//screensize in u16 einheiten
			while (destBuffer<finalAdr)
				*destBuffer++ = *srcPtr++;

			// draw from the top
			diffy = 160 - diffy; // remaing lines to be drawn
			srcPtr = (u16 *)&bgData;//starData contains the background color values 
			finalAdr = destBuffer + (diffy * 120);//screensize in u16 einheiten
			while (destBuffer<finalAdr)
				*destBuffer++ = *srcPtr++;
		}
		else // dont need to scroll
		{
			u16* srcPtr = (u16 *)&bgData + y * 120;//contains the background color values 
			u16* destBuffer = videoBuffer;
			u16* finalAdr = destBuffer + SCREENSIZE_U16;//screensize in u16 einheiten
			while (destBuffer<finalAdr)
				*destBuffer++ = *srcPtr++;
		}
	}
	//Draw player ship to sceen 0 if nt hit 1 if hit
	void DrawPlayer(int px, int py, int hit)
	{
		int x, y;
		//set pallete
		if (hit == 0)
		{
			

			for (y = 0; y < player_HEIGHT; y++)
			{
				for (x = 0; x < (player_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + px, y + py, playerData[y*(player_WIDTH / 2) + x]);
				}
			}
		}
		else if (hit == 1)
		{
			

			for (y = 0; y < playerhit_HEIGHT; y++)
			{
				for (x = 0; x < (playerhit_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + px, y + py, playerhitData[y*(playerhit_WIDTH / 2) + x]);
				}
			}
		
		}
	}
	
	void DrawAsteroid(int ax[NUMASTEROIDS], int ay[NUMASTEROIDS], int as[NUMASTEROIDS])
	{
		int x;
		int y;
		int loop;
		for (loop = 0; loop < NUMASTEROIDS; loop++)
		{
			if (as[loop]) // draw it if its on
			{
				for (y = 0; y < asteroid_HEIGHT; y++)
				{
					for (x = 0; x < (asteroid_WIDTH / 2); x++)
					{
						PlotPixelTransparent(x + ax[loop], y + ay[loop], asteroidData[y*(asteroid_WIDTH / 2) + x]);
					}
				}
			}

		}
	}
	void DrawPlayerBullet(int ax[NUMPLAYERBULLETS], int ay[NUMPLAYERBULLETS], int as[NUMPLAYERBULLETS])
	{
		int x;
		int y;
		int loop;


		for (loop = 0; loop < NUMPLAYERBULLETS; loop++)
		{
			if (as[loop]) // draw it if its on
			{
				for (y = 0; y < playerbullet_HEIGHT; y++)
				{
					for (x = 0; x < (playerbullet_WIDTH / 2); x++)
					{
						PlotPixelTransparent(x + ax[loop], y + ay[loop], playerbulletData[y*((playerbullet_WIDTH / 2)/2) + x]);
					}
				}
			}
			
		}
		
	}
	void DrawPause()
	{
		int x;
		int y;
		for (y = 0; y < 160; y++)
			for (x = 0; x < 120; x++)
				PlotPixelTransparent(x, y, pauseData[y * 120 + x]);
		WaitForVblank();
		Flip();
		if (!((*KEYS) & KEY_B)) //exit pause screen
		{
			menu();


		}


	}
	void DrawNumber(int nx, int ny, int num)
	{
		int x;
		int y;
		if (num == 0)
		{
			for (y = 0; y < zero_HEIGHT; y++)
			{
				for (x = 0; x < (zero_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, zeroData[y*(zero_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 1)
		{
			for (y = 0; y < one_HEIGHT; y++)
			{
				for (x = 0; x < (one_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, oneData[y*(one_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 2)
		{
			for (y = 0; y < two_HEIGHT; y++)
			{
				for (x = 0; x < (two_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, twoData[y*(two_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 3)
		{
			for (y = 0; y < three_HEIGHT; y++)
			{
				for (x = 0; x < (three_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, threeData[y*(three_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 4)
		{
			for (y = 0; y < four_HEIGHT; y++)
			{
				for (x = 0; x < (four_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, fourData[y*(four_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 5)
		{
			for (y = 0; y < five_HEIGHT; y++)
			{
				for (x = 0; x < (five_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, fiveData[y*(five_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 6)
		{
			for (y = 0; y < six_HEIGHT; y++)
			{
				for (x = 0; x < (six_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, sixData[y*(six_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 7)
		{
			for (y = 0; y < seven_HEIGHT; y++)
			{
				for (x = 0; x < (seven_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, sevenData[y*(seven_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 8)
		{
			for (y = 0; y < eight_HEIGHT; y++)
			{
				for (x = 0; x < (eight_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, eightData[y*(eight_WIDTH / 2) + x]);
				}
			}
		}
		else if (num == 9)
		{
			for (y = 0; y < nine_HEIGHT; y++)
			{
				for (x = 0; x < (nine_WIDTH / 2); x++)
				{
					PlotPixelTransparent(x + nx, y + ny, nineData[y*(nine_WIDTH / 2) + x]);
				}
			}
		}
	}
	void DrawLife(int life)
	{
		int x, y;
		for (x = 186; x < (life + 186); x += 2)
			for (y = 35; y < 43; y++)
				PlotPixel(x / 2, y, 0x0202); // green 
		for (x = 186 + life; x < 224; x += 2)
			for (y = 35; y < 43; y++)
				PlotPixel(x / 2, y, 0xBCBC);
	}
	void DrawHud(int life, int score)
	{
		int xpos = 83;
		int ypos = 2;
		int x;
		int y;
		//draw the hud
		for (y = 0; y < hud_HEIGHT; y++)
		{
			for (x = 0; x < (hud_WIDTH / 2); x++)
			{
				PlotPixelTransparent(x + xpos, y + ypos, hudData[y*(hud_WIDTH / 2) + x]);
			}
		}
		//draw the health bar
		for (x = 194; x < (life + 194); x += 2)
			for (y = 12; y < 18; y++)
				PlotPixel(x / 2, y, 0x0202); // green 
		for (x = 194 + life; x < 234; x += 2)
			for (y = 12; y < 18; y++)
				PlotPixel(x / 2, y, 0x0000); 
		int tscore = 0;
		int tscore2 = 0;
		//draw 100s x= 194/2 y = 5
		tscore = score / 100;
		DrawNumber(194/2, 5, tscore);
		tscore = score - (tscore * 100);
		tscore2 = tscore / 10;
		//draw 10s 196/2 y =5
		DrawNumber(200 / 2, 5, tscore2);
		tscore = tscore - (tscore2 * 10);
		//draw 1s 198/x
		DrawNumber(206 / 2, 5, tscore);
	}
	void DrawGameOver(int score)
	{
		int x, y;
		EraseScreen();
		u32 countFrame = 0; // for fixing up/down on keystrokes
		u32 tmpCount = 0;

		u16* srcPtr = (u16 *)&gameoverData;
		u16* destBuffer = videoBuffer;
		u16* finalAdr = destBuffer + SCREENSIZE_U16;//screensize in u16 einheiten

		while (destBuffer < finalAdr)
		{
			*destBuffer++ = *srcPtr++;
		}
		for (x = 0; x < 256; x++)	// set the background palette
		{
			paletteMem[x] = gameoverPalette[x];
		}
		

		int gameover = 1;
		for (y = 0; y < 160; y++)
			for (x = 0; x < 120; x++)
				PlotPixelTransparent(x, y, gameoverData[y * 120 + x]);

		int tscore = 0;
		int tscore2 = 0;
		//draw 100s x= 194/2 y = 5
		tscore = score / 100;
		DrawNumber(126 / 2, 105, tscore);
		tscore = score - (tscore * 100);
		tscore2 = tscore / 10;
		//draw 10s 196/2 y =5
		DrawNumber(132 / 2, 105, tscore2);
		tscore = tscore - (tscore2 * 10);
		//draw 1s 198/x
		DrawNumber(138 / 2, 105, tscore);

		WaitForVblank();
		Flip();
		FadeIn(2);
		while (gameover)
		{
			if (!((*KEYS) & KEY_B)) //exit pause screen
			{
				gameover = 0;
				menu();
			}
		}
		


	}

	

	void DoGame(void)
	{

		int bgy;
		int bgscroll;
		int asteroidx[NUMASTEROIDS]; //asteroid x
		int asteroidy[NUMASTEROIDS]; // asteroid y
		int asteroids[NUMASTEROIDS]; //asteroid status
		int playerBulletx[NUMPLAYERBULLETS]; //player bullet x
		int playerBullety[NUMPLAYERBULLETS]; //player bullet y
		int playerBullets[NUMPLAYERBULLETS]; //player bullet status

		int loop;		// temp loop variable
		int zloop;     //2nd loop
		int play = 1;
		int rnum; // temp storage of random number
		int asteroidDiff = 90; //roughly one a second to start with
		int hit = 0;
		int hittimer;
		int pause = 0;
		int life = 40;
		int score = 0;
		int scorecount = 0;
		int firerate = 0; //limit fire rate
		int asteroidspeed;

		int shipx = (240 / 2 - (player_WIDTH / 2)) / 2; //ships starting coords
		int shipy = 140;

		//set bg pallete
		for (loop = 0; loop < 256; loop++)
		{
			paletteMem[loop] = bgPalette[loop];
		}
		//set asteroids off
		for (loop = 0; loop < NUMASTEROIDS; loop++)
		{
			asteroids[NUMASTEROIDS] = 0;
		}
		//set player bullets off
		for (loop = 0; loop < NUMPLAYERBULLETS; loop++)
		{
			playerBullets[NUMPLAYERBULLETS] = 0;
		}

		bgy = 319; // current y of bg
		bgscroll = 1.5; //scroll speed
		//Game loop
		//Draw Background
		//Draw Player
		//Draw objects
		//Check for collisions
		//Move player / objects
		while (play == 1)
		{
			// End game screen
			//if score = 999 or health = 0
			if (life < 1|| score > 999)
			{
				//game over
				if (score > 999)
				{
					score = 999;
				}
				play = 0;
			}
			//increase asteroid speed as game goes on
			if (score < 100)
			{
				asteroidspeed = 2;
			}
			else if(score< 200)
			{
				asteroidspeed = 3;
			}
			else if (score < 300)
			{
				asteroidspeed = 4;
			}

			DrawBackground(bgy);
			bgy -= bgscroll;		// scroll the background 
			if (bgy < 1)
			{
				bgy = 319;	// reset the scroll, at 319
			}
			DrawPlayer(shipx, shipy, hit); //Draw ship
			DrawPlayerBullet(playerBulletx, playerBullety, playerBullets); // draw bullets
			DrawAsteroid(asteroidx, asteroidy, asteroids); //draw asteroids
			DrawHud(life, score);

			WaitForVblank();
			//increment score
			if (scorecount < 10)
			{
				scorecount++;
				firerate++;
			}
			else if(score < 999)
			{
				score++;
				scorecount = 0;
			}
			// after roughly 1 seconds change colour back
			if (hit == 1)
			{
				hittimer++;
				if (hittimer == 30)
				{
					hit = 0;
					hittimer = 0;
				}
			}
			Flip();	// draw the screen
			if (!((*KEYS) & KEY_START)) //pause screen
			{
				pause = 1;
				DrawPause();
						
			}
			while (pause == 1) //pause screen
			{
				
				if (!((*KEYS) & KEY_B)) //exit pause screen
				{
					pause = 0;
					

				}
			}
			if (!((*KEYS) & KEY_RIGHT)) //move ship right
			{
				shipx += 2;
			}
			if (!((*KEYS) & KEY_LEFT)) //move ship left
			{
				shipx -= 2;
			}
			if (!((*KEYS) & KEY_A)) //shoot bullet
			{
				//if less that 10 player bullets
				for (loop = 0; loop < NUMPLAYERBULLETS; loop++)
				{
					if (playerBullets[loop] == 0 && firerate > 5)
					{
						playerBullets[loop] = 1; //turn bullet on
						playerBulletx[loop] = shipx + 4; //set x middle of ship
						playerBullety[loop] = shipy; // set bullet y start.
						firerate = 0;
						play_sfx(&Bullhorn);
						break;

					}
				}
				
			}

			//check bullet collision + movement
			for (loop = 0; loop < NUMPLAYERBULLETS; loop++)
			{
				if (playerBullets[loop] == 1)//move bullet
				{
					playerBullety[loop] -= 4; //move up
					//bullet vs asteroid
					for (zloop = 0; zloop < NUMASTEROIDS; zloop++)
					{
						if (asteroids[zloop] == 1)
						{
							if (playerBulletx[loop] > asteroidx[zloop] && playerBulletx[loop] < (asteroidx[zloop] + asteroid_HEIGHT/ 2) && (asteroidy[zloop] + asteroid_HEIGHT) > playerBullety[loop])
							{
								asteroids[zloop] = 0;
								playerBullets[loop] = 0;
								score += 20;
							}
							else if ((playerBulletx[loop] + playerbullet_HEIGHT/2) > asteroidx[zloop] && (playerBulletx[loop] + playerbullet_HEIGHT/2) < asteroidx[zloop] + asteroid_HEIGHT/2 && (asteroidy[zloop] + (asteroid_HEIGHT)) > playerBullety[loop])
							{
								asteroids[zloop] = 0;
								playerBullets[loop] = 0;
								score += 20;
							}
						}
					}
				}
				if (playerBullety[loop] < 0)
				{
					playerBullets[loop] = 0; //turn off as it went above screen
				}
			}

			//create asteroids NUMASTEROIDS is max. Asteroid difficulty is frequency of asteroids appearing
			for (loop = 0; loop < NUMASTEROIDS; loop++)
			{
				// if off then random to turn it on
				if (asteroids[loop] == 0)
				{
					rnum = RAND(asteroidDiff);
					if (rnum == 1)
					{
						asteroids[loop] = 1; // turn it on					
						asteroidx[loop] = RAND((240 - asteroid_WIDTH) / 2);
						asteroidy[loop] = 0;
					}
				}
				if (asteroids[loop] == 1) //move asteroid if on
				{
					asteroidy[loop] += asteroidspeed;

					//check for off bottom of screen
					if (asteroidy[loop] > 180 - asteroid_HEIGHT)
					{
						asteroids[loop] = 0;
					}
					
					if (shipx > asteroidx[loop] && shipx < (asteroidx[loop] + asteroid_HEIGHT/2) && (asteroidy[loop] + asteroid_HEIGHT) > 138)
					{
						asteroids[loop] = 0;
						hit = 1;
						life -= 5;
						
						DrawPlayer(shipx, shipy, hit);
					}
					else if ((shipx + player_HEIGHT/2) > asteroidx[loop] && (shipx + player_HEIGHT/2) < asteroidx[loop] + asteroid_HEIGHT/2 && (asteroidy[loop] + asteroid_HEIGHT) > 138)
					{
						asteroids[loop] = 0;
						hit = 1;
						life -= 5;
						DrawPlayer(shipx, shipy, hit);
						
					}	
				}
			}
			if (shipx > 120 - player_WIDTH / 2) //collision right side of screen
			{
				shipx = 120 - player_WIDTH / 2;
			}
			if (shipx < 0) //collision left side of screen
			{
				shipx = 0;
			}
		}
		DrawGameOver(score);
		


	}
	


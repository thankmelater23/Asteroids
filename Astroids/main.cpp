// Andre Villanueva HnG Studios
// 12-26-11 1:00 AM

#include "DarkGDK.h"
#include <time.h>
#include <ctime>
#include "function.h"
#include "High_Score.h"



void DarkGDK ( void )  
{ 
	dbSetWindowTitle("Astroids");
	dbText(230, 70, "WELCOME TO \"Astroid\"");
	dbText(135, 100, "Developed by: Andre Villanueva(HnG Studios)");
	dbText(200, 120, "Created on: December 26, 2011");
	dbText(280, 140, "Game #1");
	dbSync();
	dbSyncOn();
	dbWaitKey();

	dbSyncRate(SYNC_RATE);
	dbSetImageColorKey(0, 255, 0);
	srand(time(NULL));
	dbSetDisplayMode(500, 900, 32);
	dbSetTextSize(26);
	load_game();
	generate_level(NUMBER_OF_ASTEROIDS);
	dbSprite(SHIP, SHIP_START_X, SHIP_START_Y, SHIP_IMAGE);
	dbLoopMusic(BACKGROUND_MUSIC);
	
	bool startGame = false;
	
	

	while(!dbEscapeKey() && LoopGDK())
	{


		if(dbUpKey())
		{
			dbWaitKey();
		}

		TIME = dbTimer();

		move_asteroids();
 		increase_time(TIME, INC_TIME, ASTEROID_SPEED);
		shoot();
		move_ship();
		collision(SHIP);
		reset_asteroids();
		

		dbPasteImage(BACKGROUND_IMAGE, 0, 0);
		dbPasteImage(SCORE_IMAGE, 0, 0);
		dbText(54, 4, dbStr(SCORE));
		dbPasteImage(LIVES_IMAGE, 0, LIVES_Y, LIVES_IMAGE);
		dbText(60, 875, dbStr(HEALTH / 2));

		dbSync();
		dbDeleteSprite(EXPLO);

		if(startGame == false)
		{
			dbSync();
			dbWait(4000);
			startGame = true;
		}

		if(HEALTH == 0)
		{
			int x = dbSpriteX(SHIP);
			int y = dbSpriteY(SHIP);

			dbSprite(DEATH_IMAGE, x, y, DEATH_IMAGE);
			dbDeleteSprite(SHIP);
			dbDeleteSprite(EXPLO);
			dbDeleteSprite(MISSLE);
			play_sound(DEATH);
			dbSync();
			dbWait(4000);
			dbSyncOff();
			memory_leak();
			checkForHighScore(SCORE);
			return;
		}

	}
	
	}





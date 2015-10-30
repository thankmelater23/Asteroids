#include <time.h>
#include <ctime>
#include "CONSTANTS.h"

void generate_level(int);

void memory_leak();

void move_astorids();

void load_game();

void move_ship();

void shoot();

void collision(int &ship);

void play_sound(int sound);

void increase_time(int &, int &, int &);




void increase_time(int &time, int &inc, int &speed)
{
	if(time >= inc || inc == 0 && speed <= ASTEROID_SPEED_HOLDER -3)
	{
             inc = time + 10000;
  			 dbDeleteSprite(NUMBER_OF_ASTEROIDS);
			 NUMBER_OF_ASTEROIDS--;
			 speed-= 2;
	}
}

void play_sound(int sound)
{
	if(dbSoundPlaying(sound))
			{
				dbStopSound(sound);
			}

			dbPlaySound(sound);
			
}

void shoot()
{

	if(SHOT == true)
	{
		int x = dbSpriteX(MISSLE);
		int y = dbSpriteY(MISSLE) + MISSLE_SPEED;

		dbSprite(MISSLE, x, y, MISSLE_IMAGE);


	for(int i = 1; i <= NUMBER_OF_ASTEROIDS; i++)
	{
		if(dbSpriteCollision(MISSLE, i))
		{
			SCORE += 10;
			int x = dbSpriteX(i);
			int y = dbSpriteY(i);

			play_sound(sASTROID_HIT);
			SHOT = false;
			dbSprite(EXPLO, x, y, EXPLO_IMAGE);
			dbDeleteSprite(i);
			dbDeleteSprite(MISSLE);
			dbSprite(i, dbRnd(500), -40, ASTEROID_IMAGE);
		
		}

				if(y <= -5)
				{
					dbDeleteSprite(MISSLE);
					SHOT = false;
				}
	}

	}

	
	if(dbSpaceKey() != true && SHOT == false)
	{
		int x = dbSpriteX(SHIP) + (dbSpriteWidth(SHIP) / 2) -15;
		int y = dbSpriteY(SHIP) - 30;

		
			dbSprite(MISSLE, x, y, MISSLE_IMAGE);
			
			play_sound(LASER);

			SHOT = true;
			
	}
			
}

void collision(int &ship)
{

	for(int i = 1; i <= NUMBER_OF_ASTEROIDS; i++)
	{
	
	if(dbSpriteCollision(ship, i))
	{
		HEALTH -= 2;
		int time = dbTimer();
		int x = dbSpriteX(i);
		int y = dbSpriteY(i);

		
		play_sound(CRASH);
		dbSprite(EXPLO, x, y, EXPLO_IMAGE);
		dbDeleteSprite(i);
		dbSprite(i, dbRnd(500), -40, ASTEROID_IMAGE);
		
		
		if(time >= time+100000)
		{
		dbDeleteSprite(EXPLO);
		}

	}
	}
}

void move_ship()
{
	int left_right = dbSpriteX(SHIP);

	if(dbRightKey())
	{
		if(dbSpriteX(SHIP) < 500 - dbSpriteWidth(SHIP))
		{
		left_right += SHIP_SPEED;
		}

		else
		{
			play_sound(sBUMP);
		}

	}

	if(dbLeftKey())
	{
		if(dbSpriteX(SHIP) > 0)
		{
		left_right -= SHIP_SPEED;
		}
		else
		{
			play_sound(sBUMP);
		}
	}

	dbSprite(SHIP, left_right,  dbSpriteY(SHIP), SHIP_IMAGE);
}

void generate_level(int blocks)
{
	for(int i = 0; i <= blocks; i++)
	{
		dbSprite(i, dbRnd(500), dbRnd(400), ASTEROID_IMAGE);
	}
}

void move_asteroids()
{
	if(F_BALL == false)
	{
	fastball = dbRnd(NUMBER_OF_ASTEROIDS);
	dbSprite(fastball, dbRnd(500), -50, ASTEROID_IMAGE);
	F_BALL = true;
	}

	if(dbSpriteY(fastball) >= 900)
	{
		fastball = dbRnd(NUMBER_OF_ASTEROIDS);
		dbSprite(fastball, dbRnd(500), -50, ASTEROID_IMAGE);
	}

	dbMoveSprite(fastball, FASTBALL_SPEED);
	

	for(int i = 0; i <= NUMBER_OF_ASTEROIDS; i++)
	{
		if(i != fastball)
		{
		dbMoveSprite(i, static_cast<int>(ASTEROID_SPEED));
		}
	}
}

void reset_asteroids()
	{
		for(int i = 1; i < NUMBER_OF_ASTEROIDS; i++)
		{
			if(dbSpriteY(i) > 910 || dbSpriteX(i) >= 500 - dbSpriteWidth(i))
			{
				dbSprite(i, dbRnd(500), -50, ASTEROID_IMAGE);
			}

			for(int j = 1; j < NUMBER_OF_ASTEROIDS; j++)
			{
			if(dbSpriteCollision(i, j))
			{
				if(i != j && i != fastball && j != fastball)
				{
 				dbSprite(i, dbSpriteX(i) + dbSpriteWidth(i), dbSpriteY(i) - dbSpriteHeight(i), ASTEROID_IMAGE);
				}
			}
			}
		}
	}

void load_game()
{
	dbLoadImage("ship.bmp", SHIP_IMAGE);
	dbLoadImage("asteroid.bmp", ASTEROID_IMAGE  );
	dbLoadImage("background.bmp", BACKGROUND_IMAGE);
	dbLoadImage("score.bmp", SCORE_IMAGE);
	dbLoadImage("explode.bmp", EXPLO_IMAGE);
	dbLoadImage("missile.bmp", MISSLE_IMAGE);
	dbLoadImage("lives_img.bmp", LIVES_IMAGE);
	dbLoadImage("lives_ship.bmp", MINI_SHIPS);
	dbLoadImage("indi_astro.bmp", SUPER_ASTEROID_IMAGE);
	dbLoadImage("death.bmp", DEATH_IMAGE);

	dbLoadSound("laser.wav", LASER);
	dbLoadSound("crash.wav", CRASH);
	dbLoadSound("sASTROID_HIT.wav", sASTROID_HIT);
	dbLoadSound("bump.wav", sBUMP);
	dbLoadSound("death.wav", DEATH);
	
	
	dbLoadMusic("background_music.mp3", BACKGROUND_MUSIC);
}

void memory_leak()
{
	for(int i = 0; i < MEMORY_LEAK_LOOP_COUNTER; i++)
	{
	dbDeleteImage(i);
	dbDeleteSprite(i);
	dbDeleteSound(i);
	dbDeleteMusic(i);
	}

	return;
}


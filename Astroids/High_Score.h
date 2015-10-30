int HIGH_SCORE_FILE = 1;


void newHighScore(int spaces);

void checkForHighScore(int spaces);


void checkForHighScore(int score)
{
	dbCLS();
	int highScore;

	if(dbFileExist("HighScore.dat"))
	{

	dbOpenToRead(HIGH_SCORE_FILE, "HighScore.dat");

	highScore = dbReadFile(HIGH_SCORE_FILE);

	dbCloseFile(HIGH_SCORE_FILE);
}
else
{
	highScore = 0;
	}

	dbPrint("HighScore: ");
	dbPrint(dbStr(highScore));
	dbPrint("Your Score: ");
	dbPrint(dbStr(score));
	dbSync();
	dbWaitKey();


	if(score > highScore)
	{
			dbCLS();
		newHighScore(score);
	}
	dbPrint("Good Bye...");
	dbSync();
	dbWaitKey();

}


void newHighScore(int score)
	{
		int centerX = dbScreenWidth() / 2;
		int centerY = dbScreenHeight() / 2;

		dbCLS();

		dbCenterText(centerX, centerY, "Congradulations:");
		dbCenterText(centerX, centerY + 20, "That's the new High Score!");
		dbSync();

		if(dbFileExist("HighScore.dat"))
		{
			dbDeleteFile("HighScore.dat");
		}


			dbOpenToWrite(HIGH_SCORE_FILE, "HighScore.dat");

			dbWriteFile(HIGH_SCORE_FILE, score);

			dbCloseFile(HIGH_SCORE_FILE);


			dbCenterText(centerX, centerY + 40, "Press any key...");
			dbSync();
			dbWaitKey();
		}
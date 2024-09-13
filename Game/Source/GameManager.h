#pragma once
#include "../Models/Game.h"

namespace GameManager
{
	void start();

	static void setConsoleProperties();

	static void loadingScreen();
	static void freezeLoadingScreen();

	static void processingScreen();

	static bool playGame(Game& game);

	static void trackLeftTime(Game& game);
	
	static void updateGame(Game& game, uint8_t key);

	static uint8_t getMovementKey();

	static bool checkGameEndingState(const Game& game);

	namespace GameInterface
	{
		static void displayGameInterface(Game& game);

		static void printColoredPlayer(Player player, Dimension mapDimensions);
		static void printTimeOutAnimation(const Game& game);

		static Coord mapCoordsToConsoleCoords(Coord mapCoords, Dimension mapDimensions);
		static Coord updateCoords(Coord coords, uint8_t key);

		static void updateStats(Game& game);
		static void printStats(const Game& game);

		static void movePlayer(Player player, Coord previousCoords,Dimension mapDimensions);

		static void printScore(const Game& game);
	}

	namespace GameMenu
	{
		static void printVariantsScreen();
		static void printBuildsScreen(uint8_t mapVariant);

		static uint8_t getMapVariant();
		static uint8_t getMapBuild(uint8_t mapVariant);

		static void printHelp();

		static void printColoredLines(bool hasText = true);
		static void printLogo();
		static void printVariants();

		static void printBuilds(uint8_t mapVariant);

		static void checkExitScreen();

		static void printConfirmScreen();
		static bool checkYoNAnswer();

		static void exitHelp();
		static bool confirmMapVariant(uint8_t mapVariant);
		static bool confirmMapBuild(uint8_t mapVariant, uint8_t mapBuild);

		static bool checkPlayAgain();
	}
}
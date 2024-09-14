#include "GameManager.h"
//-----------------------------------------------
#include "../Models/MapObjects/Items/ItemTypes.h"
//-----------------------------------------------
#include "../Builds/MapFactory.h"
#include "../Builds/MapCounts.h"
#include "../Builds/GamePrints.h"
#include "../Builds/MapNames.h"
//-------------------------------
#include <Models/SecondChecker.h>
//---------------------------------
#include <Source/RandomGenerator.h>
#include <Source/addbutmcr.h>
//---------------------------
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

namespace GameManager
{
	static void setConsoleProperties();

	static void printColoredPressLine(const char* line, uint8_t row);

	static void loadingScreen();
	static void freezeLoadingScreen();

	static void processingScreen();

	static void printAnimatedWaitingLine(const char* line, uint16_t sleepTime, bool hasThreads);

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

		static void movePlayer(Player player, Coord previousCoords, Dimension mapDimensions);

		static void printScore(const Game& game);

		namespace PlayKeys
		{
			inline bool isPressedA(uint8_t key)
			{
				return (key == VK_A || (key == VK_TO_LOWER(VK_A)));
			}

			inline bool isPressedS(uint8_t key)
			{
				return (key == VK_S || (key == VK_TO_LOWER(VK_S)));
			}

			inline bool isPressedD(uint8_t key)
			{
				return (key == VK_D || (key == VK_TO_LOWER(VK_D)));
			}

			inline bool isPressedW(uint8_t key)
			{
				return (key == VK_W || (key == VK_TO_LOWER(VK_W)));
			}

			inline bool isPlayKey(uint8_t key)
			{
				return (isPressedA(key) || isPressedS(key) || isPressedD(key) || isPressedW(key));
			}
		}

		namespace PlayTimeOptions
		{
			inline bool isPressedESC(uint8_t key)
			{
				return (key == VK_ESCAPE);
			}
			inline bool isPressedR(uint8_t key)
			{
				return (key == VK_R || (key == VK_TO_LOWER(VK_R)));
			}
		}
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

		static void printExitScreen();

		static void printConfirmScreen();
		static bool checkYoNAnswer();

		static bool confirmMapVariant(uint8_t mapVariant);
		static bool confirmMapBuild(uint8_t mapVariant, uint8_t mapBuild);

		static bool checkPlayAgain();

		namespace ColoredLines
		{
			static uint8_t s_Color = 0x1;

			inline uint8_t toBackgroundColor()
			{
				return (s_Color << 4);
			}

			inline void setColoredLines()
			{
				uint8_t tryColor = 0x0;
				do
				{
					tryColor = RandomGenerator::generateNext(16);
				} while (tryColor == s_Color);

				s_Color = tryColor;
			}

			inline bool isPressedC(uint8_t key)
			{
				return ((key == VK_C) || (key == VK_TO_LOWER(VK_C)));
			}
		}

		namespace Help
		{
			inline bool isPressedE(uint8_t key)
			{
				return ((key == VK_E) || (key == VK_TO_LOWER(VK_E)));
			}

			inline bool isPressedH(uint8_t key)
			{
				return ((key == VK_H) || (key == VK_TO_LOWER(VK_H)));
			}
		}

		namespace ConfirmKeys
		{
			inline bool isYes(uint8_t key)
			{
				return ((key == VK_Y) || (key == VK_TO_LOWER(VK_Y)));
			}

			inline bool isNo(uint8_t key)
			{
				return ((key == VK_N) || (key == VK_TO_LOWER(VK_N)));
			}
		}
}

	namespace ExitGame
	{
		inline bool isPressedESC(uint8_t key)
		{
			return (key == VK_ESCAPE);
		}
	}

	namespace FreezeScreen
	{
		inline bool isPressedF(uint8_t key)
		{
			return (key == VK_F || (key == VK_TO_LOWER(VK_F)));
		}
	}

	namespace Multithread
	{
		static std::mutex coutMutex;
		static std::atomic endFlag(false);
		static std::condition_variable conditionVariable;

		namespace LoadingScreen
		{
			static std::atomic hasFinished(false);
			static bool isFreezed(false);
		}
	}
}

#define GM_CONSOLE_WIDTH  70
#define GM_CONSOLE_HEIGHT 16

#define GM_PLAYABLE_CONSOLE_HEIGHT 36

#define GM_FIRST_ROW 0
#define GM_LAST_ROW  (GM_CONSOLE_HEIGHT - 1)

#define GM_CONSOLE_BACKGROUND_COLOR (GameMenu::ColoredLines::toBackgroundColor() | BACKGROUND_INTENSITY)
#define GM_FOREGROUND_DEF_COLOR 0x0

#define GM_EXIT 0
#define GM_PLAY_AGAIN 1
	
void GameManager::start()
{	
	setConsoleProperties();

	RandomGenerator::setSeed();
	GameMenu::ColoredLines::setColoredLines();

	while (TRUE)
	{
		GameMenu::printVariantsScreen();
		uint8_t mapVariant = GameMenu::getMapVariant();

		if (ExitGame::isPressedESC(mapVariant))
		{
			exit(GM_EXIT);
		}

		if (!GameMenu::confirmMapVariant(mapVariant))
		{
			continue;
		}

		while (TRUE)
		{
			GameMenu::printBuildsScreen(mapVariant);
			uint8_t mapBuild = GameMenu::getMapBuild(mapVariant);

			if (ExitGame::isPressedESC(mapBuild))
			{
				exit(GM_EXIT);
			}

			if (!GameMenu::confirmMapBuild(mapVariant, mapBuild))
			{	
				continue;
			}

			bool playAgain = false;

			while (TRUE)
			{
				Console::setConsoleColor(DEF_FOREGOUND_COLOR);

				std::thread load(loadingScreen);
				Game game(createMap(mapVariant, mapBuild));
				load.join();

				GameInterface::displayGameInterface(game);

				if (playGame(game))
				{
					Console::setConsoleSize(GM_CONSOLE_WIDTH, GM_CONSOLE_HEIGHT);
					continue;
				}

				playAgain = checkGameEndingState(game);
				break;
			}

			if (playAgain)
			{
				break;
			}

			Console::clearConsole();
			exit(GM_EXIT);		
		}
	}
}

void GameManager::setConsoleProperties()
{
	system("title Buff Game");

	Console::makeNotResizable();
	Console::removeMaximizedBox();

	Console::changeVisibilityCursor(FALSE);
	Console::changeVisibilityScrollbars(FALSE);

	Console::disableQuickEditMode();
	Console::setConsoleFont(L"Cascadia Mono SemiBold", 26);

	Console::setConsoleSize(GM_CONSOLE_WIDTH, GM_CONSOLE_HEIGHT);
}

void GameManager::printColoredPressLine(const char* line, uint8_t row)
{
	Console::moveCursor(0, row);

	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);
	Console::printLine(line, Console::Alignment::Center);
	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);
}

void GameManager::loadingScreen()
{
	Multithread::LoadingScreen::hasFinished = false;
	Multithread::LoadingScreen::isFreezed = false;

	std::thread freeze(&freezeLoadingScreen);

	Console::clearConsole();
	GameMenu::printColoredLines(false);

	Console::printSymbol(Symbols::ce_NewLine, 2);
	GamePrints::s_QuickGameInterfaceHelp.displayContent(Console::Alignment::Center);
	Console::printEmptyLine();

	GamePrints::s_QuickTipsTitle.displayContent(Console::Alignment::Center);
	Console::printEmptyLine();

	RandomGenerator::setSeed();
	Console::printLine(GamePrints::s_QuickTipsChoice
					  [RandomGenerator::generateNext(GamePrints::s_QuickTipsChoice.getHeight())].data(),
					  Console::Alignment::Center, false);
	
	printColoredPressLine("PRESS F TO FREEZE", GM_CONSOLE_HEIGHT - 3);

	Console::moveCursor(0, 1);

	printAnimatedWaitingLine("loading", 400, true);

	Console::clearConsole();

	Multithread::LoadingScreen::hasFinished = true;
	freeze.join(); 
}

void GameManager::freezeLoadingScreen()
{
	while (!Multithread::LoadingScreen::hasFinished)
	{
		uint8_t key = Console::getAtomicPressedKey(Multithread::LoadingScreen::hasFinished);

		if (FreezeScreen::isPressedF(key))
		{
			{
				std::unique_lock<std::mutex> lock(Multithread::coutMutex);
				Multithread::LoadingScreen::isFreezed = !Multithread::LoadingScreen::isFreezed;
				Console::clearConsole(1, 1);
				Console::printLine("freezed   ", Console::Alignment::Center);
			}
			Multithread::conditionVariable.notify_one();
		}

		Sleep(DEF_SLEEP_TIME);
	}
}

void GameManager::processingScreen()
{
	Console::clearConsole();
	printAnimatedWaitingLine("processing", 200, false);
	Console::clearConsole(GM_FIRST_ROW, GM_FIRST_ROW);
}

void GameManager::printAnimatedWaitingLine(const char* line, uint16_t sleepTime, bool hasThreads)
{
	for (int step = 0; step < 4; ++step)
	{
		if(hasThreads)
		{
			std::unique_lock<std::mutex> lock(Multithread::coutMutex);
			Multithread::conditionVariable.wait(lock, [] { return !Multithread::LoadingScreen::isFreezed; });
		}

		Console::clearConsole(1, 1);
		Console::printLine(std::string(line + std::string(step, '.') + std::string(3 - step, ' ')).c_str(), Console::Alignment::Center);
		Sleep(sleepTime);
	}
}

void GameManager::GameInterface::displayGameInterface(Game& game)
{
	const Map& map = game.getMap();
	Dimension mapDimensions = map.getDimensions();

	Console::setConsoleSize(GM_CONSOLE_WIDTH, mapDimensions.Height + 3);

	map.print();
	printColoredPlayer(game.getCurrentPlayer(), mapDimensions);

	printColoredPressLine("PRESS ENTER TO START", mapDimensions.Height);

	while (TRUE)
	{
		uint8_t key = Console::getPressedKey();

		if (key == VK_RETURN)
		{
			break;
		}
	}
	
	Console::clearConsole(mapDimensions.Height, mapDimensions.Height + 2);

	game.startTimer();

	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);
	Console::printInThreeAlignments(" |Left Time|", "|Points|", "|Played Time| ", false);
	printStats(game);
}

void GameManager::GameInterface::printColoredPlayer(Player player, Dimension mapDimensions)
{
	Coord consoleCoords = mapCoordsToConsoleCoords(player.getCoords(), mapDimensions);

	Console::setConsoleColor(GM_CONSOLE_BACKGROUND_COLOR);
	Console::printSymbolAt(consoleCoords.X, consoleCoords.Y, player.getSymbol());
	Console::setConsoleColor(GM_FOREGROUND_DEF_COLOR);
}

void GameManager::GameInterface::printTimeOutAnimation(const Game& game)
{
	const Map& map = game.getMap();
	Coord lastCoords = game.getCurrentPlayer().getCoords();
	Coord consoleCoords = GameInterface::mapCoordsToConsoleCoords(lastCoords, map.getDimensions());
	{
		std::lock_guard<std::mutex> lockThread(Multithread::coutMutex);
		for (char times = 0; times < 3; times++)
		{
			GameInterface::movePlayer(lastCoords, game.getCurrentPlayer().getCoords(), map.getDimensions());
			Sleep(200);
			Console::printSymbolAt(consoleCoords.X, consoleCoords.Y, ' ');
			Sleep(200);
		}
	}
}

Coord GameManager::GameInterface::mapCoordsToConsoleCoords(Coord mapCoords, Dimension mapDimensions)
{	
	size_t padding = (Console::getConsoleWidth() - mapDimensions.Width) / 2;

    Coord consoleCoords;
	consoleCoords.X = padding + mapCoords.X;
	consoleCoords.Y = (mapDimensions.Height - 1) - mapCoords.Y;
		
	return consoleCoords;
}

Coord GameManager::GameInterface::updateCoords(Coord coords, uint8_t key)
{
	Coord updatedCoord = coords;

	if (PlayKeys::isPressedA(key))
	{
		updatedCoord.X--;
		Sleep(50);
	}
	else if (PlayKeys::isPressedS(key))
	{
		updatedCoord.Y--;
		Sleep(120);
	}
	else if (PlayKeys::isPressedD(key))
	{
		updatedCoord.X++;
		Sleep(50);
	}
	else if (PlayKeys::isPressedW(key))
	{
		updatedCoord.Y++;
		Sleep(120);
	}

	return updatedCoord;
}

void GameManager::GameInterface::updateStats(Game& game)
{
	SecondChecker secondChecker;

	while (!Multithread::endFlag)
	{
		if (secondChecker.hasOneSecondPassed())
		{
			game.decrementLeftTime();
			printStats(game);
			secondChecker.reset();
		}

		Sleep(DEF_SLEEP_TIME);
	}
}

void GameManager::GameInterface::printStats(const Game& game)
{
	uint8_t statsRow = game.getMap().getDimensions().Height + 2;

	{
		std::lock_guard<std::mutex> lockThread(Multithread::coutMutex);
		Console::clearConsole(statsRow, statsRow);

		std::string leftTime = "  ";
		leftTime += std::to_string(game.getLeftTime()) + 's';

		std::string points;

		if (0 <= game.getPoints() && game.getPoints() <= 9)
		{
			points += '0';
		}

		points += std::to_string(game.getPoints());

		std::string playedTime = ' ' + std::to_string(game.getPlayedTime().getCurrentDuration()) + "s  ";

		Console::printInThreeAlignments(leftTime.c_str(), points.c_str(), playedTime.c_str(), false);
	}
}

void GameManager::GameInterface::movePlayer(Player player, Coord previousCoords,Dimension mapDimensions)
{
	Coord consoleCoords = mapCoordsToConsoleCoords(previousCoords, mapDimensions);
	Console::printSymbolAt(consoleCoords.X, consoleCoords.Y, Symbols::ce_WhiteSpace);

	printColoredPlayer(player, mapDimensions);
}

void GameManager::GameInterface::printScore(const Game& game)
{
	Console::printSymbol('-', Console::getConsoleWidth());
	Console::printInThreeAlignments(" |Collected Items|","|Points|","|Played Time| ", false);
	Console::printString("");

	std::string collectedItems = "  " + std::to_string(game.getCollectedItemsCount());

	std::string points;

	if (0 >= game.getPoints() && game.getPoints() <= 9)
	{
		points += '0';
	}

	points += std::to_string(game.getPoints());

	std::string playedTime = ' ' + std::to_string(game.getPlayedTime().getLastReportDuration()) + "s  ";

	Console::printInThreeAlignments(collectedItems.c_str(), points.c_str(), playedTime.c_str(), false);
	Console::printString("");
	Console::printSymbol('-', Console::getConsoleWidth());

	printColoredPressLine("PRESS ENTER TO CONTINUE", GM_CONSOLE_HEIGHT - 3);

	while (TRUE)
	{
		uint8_t key = Console::getPressedKey();

		if (key == VK_RETURN)
		{
			break;
		}
	}
}

uint8_t GameManager::getMovementKey()
{
	while (!Multithread::endFlag)
	{
		uint8_t key = Console::getAtomicPressedKey(Multithread::endFlag);

		if (GameInterface::PlayKeys::isPlayKey(key) || 
			GameInterface::PlayTimeOptions::isPressedESC(key) || 
			GameInterface::PlayTimeOptions::isPressedR(key))
		{
			return key;
		}
	}

	return GM_EXIT;
}

bool GameManager::checkGameEndingState(const Game& game)
{
	Console::clearConsole();
	Console::setConsoleSize(GM_CONSOLE_WIDTH, GM_CONSOLE_HEIGHT);

	Console::setConsoleColor(DEF_FOREGOUND_COLOR);
	processingScreen();

	GameMenu::printColoredLines(false);

	if (game.isEnded())
	{
		if (game.areAllItemsCollected())
		{
			Console::printLine("All items have been collected!",Console::Alignment::Center);
			Console::printLine("Congrats!", Console::Alignment::Center);
		}
		else if (game.isTimeOut())
		{
			Console::printLine("You ran out of time!", Console::Alignment::Center);
			Console::printLine("Next time better!", Console::Alignment::Center);
		}
		else
		{
			throw std::runtime_error("Unknown ending happened");	
		}

		GameInterface::printScore(game);

		return GameMenu::checkPlayAgain();
	}
	else
	{
		throw std::runtime_error("Unknown error occured during playing game");
	}
}

bool GameManager::GameMenu::checkPlayAgain()
{
	Console::clearConsole(1, GM_LAST_ROW - 1);
	GamePrints::s_PlayAgainScreen.displayContent(Console::Alignment::Center);

	return checkYoNAnswer();
}

bool GameManager::playGame(Game& game)
{
	Multithread::endFlag = false;

	std::thread modifyDisplayStats(&GameInterface::updateStats, std::ref(game));
	std::thread checkEndConditions(&trackLeftTime, std::ref(game));

	bool restartGame = false;

	while (!Multithread::endFlag)
	{
		uint8_t key = getMovementKey();

		if (key == GM_EXIT) 
		{ 
			break; 
		}
		else if (GameInterface::PlayTimeOptions::isPressedESC(key))
		{
			game.setLeftTime(0);
			break;
		}
		else if (GameInterface::PlayTimeOptions::isPressedR(key))
		{
			game.setLeftTime(0);
			restartGame = true;
			break;
		}

		updateGame(game, key);
	}

	game.endTimer();

	checkEndConditions.join();
	modifyDisplayStats.join();

	if (game.isTimeOut())
	{
		GameInterface::printTimeOutAnimation(game);
	}

	return restartGame;
}

void GameManager::trackLeftTime(Game& game)
{
	while (!game.isEnded())
	{
		Sleep(DEF_SLEEP_TIME);
	}

	Multithread::endFlag = true;
}

void GameManager::updateGame(Game& game, uint8_t key)
{
	Coord updatedCoords = GameInterface::updateCoords(game.getCurrentPlayer().getCoords(), key);

	const Map& map = game.getMap();
	MapSymbolType mapSymbolType = map.whatMapEntityIs(updatedCoords);

	switch (mapSymbolType)
	{
	case MapSymbolType::Obsticle:
	case MapSymbolType::Border:
	{
		break;
	}
	case MapSymbolType::Item:
	{
		if (!game.hasCollectedItemCoords(updatedCoords))
		{
			polymorphic_ptr<Item> item = map.getItem(updatedCoords);
			
			ItemType itemType = getItemType(item);

			switch (itemType)
			{
			case ItemType::NormalItem:
			case ItemType::TimyItem:
			case ItemType::RandomItem:
			{
				game.updateGameStats(item);
				game.addCollectedItemCoords(item->getCoords());

				GameInterface::printStats(game);
				break;
			}
			case ItemType::TrollItem:
			{
				game.updateGameStats(item);
				GameInterface::printStats(game);
			}
			case ItemType::TeleportItem:
			{
				TeleportItem* teleportItem = dynamic_cast<TeleportItem*>(item.get());
				teleportItem->teleportPlayer(updatedCoords);
				break;
			}
			case ItemType::DeathItem:
			{
				game.updateGameStats(item);
				Multithread::endFlag = true;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
	case MapSymbolType::WhiteSpace:
	{
		{
			std::lock_guard<std::mutex> lockThread(Multithread::coutMutex);
			GameInterface::movePlayer(updatedCoords, game.getCurrentPlayer().getCoords(), map.getDimensions());
		}
		game.updateCurrentPlayerCoords(updatedCoords);
		break;
	}
	}
}

void GameManager::GameMenu::printVariantsScreen()
{
	Console::clearConsole();
	GameMenu::printColoredLines();
	GameMenu::printLogo();
	GameMenu::printVariants();
}

void GameManager::GameMenu::printBuildsScreen(uint8_t mapVariant)
{
	Console::clearConsole();
	GameMenu::printColoredLines();
	GameMenu::printLogo();
	GameMenu::printBuilds(mapVariant);
}

uint8_t GameManager::GameMenu::getMapVariant()
{
	while (TRUE)
	{
		uint8_t key = Console::getPressedKey();

		if (MapCounts::s_MapVariantsCount.isInRange(TO_NUMBER(key)))
		{
			return key;
		}
		else if (ColoredLines::isPressedC(key))
		{
			ColoredLines::setColoredLines();
			GameMenu::printColoredLines();
		}
		else if (Help::isPressedH(key))
		{
			GameMenu::printHelp();
			GameMenu::printVariantsScreen();
		}
		else if (ExitGame::isPressedESC(key))
		{
			GameMenu::printExitScreen();
			GameMenu::printVariantsScreen();
		}
	}
}

uint8_t GameManager::GameMenu::getMapBuild(uint8_t mapVariant)
{
	uint8_t index = TO_INDEX(mapVariant);

	while (TRUE)
	{
		uint8_t key = Console::getPressedKey();

		if (MapCounts::s_MapBuildsCounts[index].isInRange(TO_NUMBER(key)))
		{
			return key;
		}
		else if (ColoredLines::isPressedC(key))
		{
			ColoredLines::setColoredLines();
			GameMenu::printColoredLines();
		}
		else if (Help::isPressedH(key))
		{
			GameMenu::printHelp();
			GameMenu::printBuildsScreen(mapVariant);		
		}
		else if (ExitGame::isPressedESC(key))
		{
			GameMenu::printExitScreen();
			GameMenu::printBuildsScreen(mapVariant);
		}
	}
}

void GameManager::GameMenu::printConfirmScreen()
{
	GameMenu::printColoredLines(false);
	Console::clearConsole(1, GM_LAST_ROW - 1);
	GamePrints::s_ConfirmScreen.displayContent(Console::Alignment::Center);
}

bool GameManager::GameMenu::checkYoNAnswer()
{
	while (TRUE)
	{
		uint8_t key = Console::getPressedKey();

		if (ConfirmKeys::isYes(key))
		{
			return TRUE;
		}
		else if (ConfirmKeys::isNo(key))
		{
			return FALSE;
		}
	}
}

bool GameManager::GameMenu::confirmMapVariant(uint8_t mapVariant)
{
	printConfirmScreen();

	Console::moveCursor(0, GamePrints::Constants::s_RowToInsertInCS);
	Console::printLine(MapNames::s_MapVariantsNames[TO_INDEX(mapVariant)].data(), Console::Alignment::Center);

	return checkYoNAnswer();
}

bool GameManager::GameMenu::confirmMapBuild(uint8_t mapVariant, uint8_t mapBuild)
{
	printConfirmScreen();

	Console::moveCursor(0, GamePrints::Constants::s_RowToInsertInCS);
	Console::printLine(MapNames::s_MapBuildNames[TO_INDEX(mapVariant)][TO_INDEX(mapBuild)].data(), Console::Alignment::Center);

	return checkYoNAnswer();
}

void GameManager::GameMenu::printHelp()
{
	Console::clearConsole(1, GM_LAST_ROW - 1);
	GamePrints::s_HelpScreen.displayContent(Console::Alignment::Center);
	GameMenu::printColoredLines(false);

	while (TRUE)
	{
		if (Help::isPressedE(Console::getPressedKey()))
		{
			Console::clearConsole(1, GM_LAST_ROW - 1);
			return;
		}
	}
}

void GameManager::GameMenu::printColoredLines(bool hasText)
{
	Console::moveCursor(0, GM_FIRST_ROW);
	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);

	if (hasText)
	{
		Console::moveCursor(0, GM_LAST_ROW);
		Console::printInThreeAlignments(" @Made by Deirror@", "Version 1.4", "Press H for help ",
										false, GM_CONSOLE_BACKGROUND_COLOR | GM_FOREGROUND_DEF_COLOR);
	}
	else
	{
		Console::moveCursor(0, GM_LAST_ROW);
		Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);
	}

	Console::moveCursor(0, 1);
}

void GameManager::GameMenu::printLogo()
{
	GamePrints::s_BuffLogo.displayContent(Console::Alignment::Center);
}

void GameManager::GameMenu::printVariants()
{
	GamePrints::s_MapVariantsOption.displayContent(Console::Alignment::Center);
}

void GameManager::GameMenu::printBuilds(uint8_t mapVariant)
{
	uint8_t index = TO_INDEX(mapVariant);
	GamePrints::s_MapBuildsOption[index].displayContent(Console::Alignment::Center);
}

void GameManager::GameMenu::printExitScreen()
{
	Console::clearConsole(1, GM_LAST_ROW - 1);
	GamePrints::s_ExitScreen.displayContent(Console::Alignment::Center);
	GameMenu::printColoredLines(false);

	if (checkYoNAnswer())
	{
		exit(GM_EXIT);
	}

	Console::clearConsole(1, GM_LAST_ROW - 1);
}
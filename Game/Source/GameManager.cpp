#include "GameManager.h"
//--------------------------------------------------
#include "../Models/MapObjects/Items/TeleportItem.h"
//--------------------------------------------------
#include "../Builds/MapFactory.h"
#include "../Builds/MapCounts.h"
#include "../Builds/GamePrints.h"
#include "../Builds/MapNames.h"
//---------------------------------
#include <Source/RandomGenerator.h>
#include <Source/addbutmcr.h>
//-------------------------------
#include <Models/SecondChecker.h>
//-------------------------------
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

namespace Multithread 
{
	static std::mutex coutMutex;
	static std::atomic endFlag(false);
}

namespace ConfirmKeys
{
	static bool isYes(uint8_t key)
	{
		return ((key == VK_Y) || (key == VK_TO_LOWER(VK_Y)));
	}

	static bool isNo(uint8_t key)
	{
		return ((key == VK_N) || (key == VK_TO_LOWER(VK_N)));
	}
}

namespace ColoredLines
{
	static uint8_t s_Color = 0x1;

	static uint8_t toBackgroundColor()
	{
		return (s_Color << 4);
	}

	static void setColoredLines()
	{
		uint8_t tryColor = 0x0;
		do
		{
			tryColor = RandomGenerator::generateNext(16);
		} while (tryColor == s_Color);

		s_Color = tryColor;
	}

	static bool isPressedC(uint8_t key)
	{
		return ((key == VK_C) || (key == VK_TO_LOWER(VK_C)));
	}
}

namespace Help
{
	static bool isPressedE(uint8_t key)
	{
		return ((key == VK_E) || (key == VK_TO_LOWER(VK_E)));
	}

	static bool isPressedH(uint8_t key)
	{
		return ((key == VK_H) || (key == VK_TO_LOWER(VK_H)));
	}
}

namespace ExitGame
{
	static bool isPressedESC(uint8_t key)
	{
		return (key == VK_ESCAPE);
	}
}

namespace PlayKeys
{
	static bool isPressedA(uint8_t key)
	{
		return (key == VK_A || (key == VK_TO_LOWER(VK_A)));
	}

	static bool isPressedS(uint8_t key)
	{
		return (key == VK_S || (key == VK_TO_LOWER(VK_S)));
	}

	static bool isPressedD(uint8_t key)
	{
		return (key == VK_D || (key == VK_TO_LOWER(VK_D)));
	}

	static bool isPressedW(uint8_t key)
	{
		return (key == VK_W || (key == VK_TO_LOWER(VK_W)));
	}

	static bool isPlayKey(uint8_t key)
	{
		return (isPressedA(key) || isPressedS(key) || isPressedD(key) || isPressedW(key));
	}
}

#define GM_CONSOLE_WIDTH  70
#define GM_CONSOLE_HEIGHT 16

#define GM_PLAYABLE_CONSOLE_HEIGHT 36

#define GM_FIRST_ROW 0
#define GM_LAST_ROW  (GM_CONSOLE_HEIGHT - 1)

#define GM_CONSOLE_BACKGROUND_COLOR (ColoredLines::toBackgroundColor() | BACKGROUND_INTENSITY)
#define GM_FOREGROUND_DEF_COLOR 0x0

#define GM_EXIT 0
#define GM_PLAY_AGAIN 1
	
void GameManager::start()
{	
	setConsoleProperties();

	RandomGenerator::setSeed();
	ColoredLines::setColoredLines();

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

		GameMenu::printColoredLines();

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

			std::thread load(loadingScreen);

			Map map = createMap(mapVariant, mapBuild);
			Game game(map);

			load.join();

			GameInterface::displayGameInterface(game);
			playGame(game);

			if (checkGameEndingState(game))
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
	Console::setConsoleFont(L"Cascadia Mono SemiBold", 22);

	Console::setConsoleSize(GM_CONSOLE_WIDTH, GM_CONSOLE_HEIGHT);
}

void GameManager::loadingScreen()
{
	Console::clearConsole();

	Console::printLine("loading   ", Console::Alignment::Center);
	Sleep(300);

	Console::clearConsole(GM_FIRST_ROW, GM_FIRST_ROW);
	Console::printLine("loading.  ", Console::Alignment::Center);
	Sleep(340);

	Console::clearConsole(GM_FIRST_ROW, GM_FIRST_ROW);
	Console::printLine("loading.. ", Console::Alignment::Center);
	Sleep(400);

	Console::clearConsole(GM_FIRST_ROW, GM_FIRST_ROW);
	Console::printLine("loading...", Console::Alignment::Center);
	Sleep(200);

	Console::clearConsole(GM_FIRST_ROW, GM_FIRST_ROW);
}

void GameManager::GameInterface::displayGameInterface(Game& game)
{
	Console::setConsoleSize(GM_CONSOLE_WIDTH, GM_PLAYABLE_CONSOLE_HEIGHT);

	const Map& map = game.getMap();

	map.print();

	Dimension mapDimensions = map.getDimensions();
	printColoredPlayer(game.getCurrentPlayer(), mapDimensions);

	Console::moveCursor(0, mapDimensions.Height);

	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);
	Console::printLine("PRESS ENTER TO START", Console::Alignment::Center);
	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);

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
		Sleep(45);
	}
	else if (PlayKeys::isPressedS(key))
	{
		updatedCoord.Y--;
		Sleep(110);
	}
	else if (PlayKeys::isPressedD(key))
	{
		updatedCoord.X++;
		Sleep(45);
	}
	else if (PlayKeys::isPressedW(key))
	{
		updatedCoord.Y++;
		Sleep(110);
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
	static uint8_t statsRow = game.getMap().getDimensions().Height + 2;

	{
		std::lock_guard<std::mutex> lockThread(Multithread::coutMutex);
		Console::clearConsole(statsRow, statsRow);

		std::string leftTime = "  ";
		leftTime += std::to_string(game.getLeftTime()) + 's';

		std::string points;

		if (0 >= game.getPoints() && game.getPoints() <= 9)
		{
			points += '0';
		}

		points += std::to_string(game.getPoints());

		std::string playedTime = ' ' + std::to_string(game.getPlayedTime()) + "s  ";

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

	std::string collectedItems = "  " + std::to_string(game.getCollectedItems());

	std::string points;

	if (0 >= game.getPoints() && game.getPoints() <= 9)
	{
		points += '0';
	}

	points += std::to_string(game.getPoints());

	std::string playedTime = ' ' + std::to_string(game.getPlayedTime()) + "s  ";

	Console::printInThreeAlignments(collectedItems.c_str(), points.c_str(), playedTime.c_str(), false);
	Console::printString("");
	Console::printSymbol('-', Console::getConsoleWidth());

	Console::printLine("PRESS ENTER TO CONTINUE", Console::Alignment::Center);

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

		if (PlayKeys::isPlayKey(key))
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

	Sleep(150);

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

	return false;
}

bool GameManager::GameMenu::checkPlayAgain()
{
	Console::clearConsole(1, GM_LAST_ROW - 1);

	GamePrints::s_PlayAgainScreen.displayContent(Console::Alignment::Center);

	return checkYoNAnswer();
}

void GameManager::playGame(Game& game)
{
	Multithread::endFlag = false;

	std::thread modifyDisplayStats(&GameInterface::updateStats, std::ref(game));
	std::thread checkEndConditions(&trackLeftTime, std::ref(game));

	while (!Multithread::endFlag)
	{
		uint8_t key = getMovementKey();

		if (key == GM_EXIT) 
		{ 
			break; 
		}

		updateGame(game, key);
	}

	checkEndConditions.join();
	modifyDisplayStats.join();
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
		polymorphic_ptr<Item> item = map.getItem(updatedCoords);

		if (!game.hasCollectedItem(item->getCoords()))
		{
			game.updateGameStats(item);
			
			/*Soon Teleport Item, though this code works it isn't reusable..must be patternized
			if (dynamic_cast<TeleportItem*>(item.get()))
			{
				TeleportItem* proba = dynamic_cast<TeleportItem*>(item.get());
				Coord conCoords = GameInterface::mapCoordsToConsoleCoords(updatedCoords, map.getDimensions());
				Console::printSymbolAt(conCoords.X, conCoords.Y, Symbols::ce_WhiteSpace);
				proba->teleportPlayer(updatedCoords);
			}
			*/

			game.addCollectedItemCoords(item->getCoords());

			GameInterface::printStats(game);
		}
	}
	case MapSymbolType::WhiteSpace:
	{
		{
			std::lock_guard<std::mutex> lockThread(Multithread::coutMutex);

			GameInterface::movePlayer(updatedCoords, game.getCurrentPlayer().getCoords(), map.getDimensions());
		}
		game.updateCurrentPlayer(updatedCoords);
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
	GameMenu::printColoredLines();
}

void GameManager::GameMenu::printBuildsScreen(uint8_t mapVariant)
{
	Console::clearConsole(1, GM_LAST_ROW - 1);
	GameMenu::printLogo();
	GameMenu::printBuilds(mapVariant);
	GameMenu::printColoredLines();
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
			GameMenu::exitHelp();
			GameMenu::printLogo();
			GameMenu::printVariants();
			GameMenu::printColoredLines();
		}
		else if (ExitGame::isPressedESC(key))
		{
			GameMenu::checkExitScreen();
			GameMenu::printLogo();
			GameMenu::printVariants();
			GameMenu::printColoredLines();
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
			GameMenu::exitHelp();
			GameMenu::printLogo();
			GameMenu::printBuilds(mapVariant);
			GameMenu::printColoredLines();
		}
		else if (ExitGame::isPressedESC(key))
		{
			GameMenu::checkExitScreen();
			GameMenu::printLogo();
			GameMenu::printBuilds(mapVariant);
			GameMenu::printColoredLines();
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

void GameManager::GameMenu::exitHelp()
{
	while (TRUE)
	{
		if (Help::isPressedE(Console::getPressedKey()))
		{
			Console::clearConsole(1, GM_LAST_ROW - 1);
			return;
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
}

void GameManager::GameMenu::printColoredLines(bool hasText)
{
	Console::moveCursor(0, GM_FIRST_ROW);
	Console::printEmptyLine(GM_CONSOLE_BACKGROUND_COLOR);

	if (hasText)
	{
		Console::moveCursor(0, GM_LAST_ROW);
		Console::printInThreeAlignments(" @Made by Deirror@", "Version 1.0", "Press H for help ",
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

void GameManager::GameMenu::checkExitScreen()
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
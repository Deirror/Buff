#pragma once
#include <Models/DisplayBuffer.hpp>

namespace GamePrints
{
	static const DisplayBuffer<28, 7> s_BuffLogo = {   "=-------------------------=",
														"|||||  ||  || |||||| ||||||",
														"||  || ||  || ||     ||    ",
														"|||||  ||  || |||||| ||||||",
														"||  || ||  || ||     ||    ",
														"|||||   ||||  ||     ||    ",
														"=-------------------------="   };

	static const DisplayBuffer<33, 6> s_ConfirmScreen = {" ","Do you confirm what you selected?",
														 " "," "," ","Press Y or N"};

	static const DisplayBuffer<26, 7> s_HelpScreen = {"/ ->Help Menu <-\\"," ","C - Randomly change color",
														 "Ctrl + SW - resize font", "ESC - Exit the game",
														  " ", "Press E to exit Help Menu"};

	static const DisplayBuffer<29, 4> s_ExitScreen = { " ", "Do you reallyy want to exit?"," ", "Press Y or N",};

	namespace Constants
	{
		static constexpr char s_RowToInsertInCS = 4;
	}

	static const DisplayBuffer<28, 7> s_MapVariantsOption = { "=-------------------------=",
															  "|\\ Choices For Playground |",
															  "|\\    (-)Alphabetic(-)    |",
															  "|\\    (-)Randomized(-)    |",
															  "|\\     (-)Imposter(-)     |",
															  "=-------------------------=",
																 "//Press a number(1-3)" };

	static const DisplayBuffer<21, 7> s_MapBuildsOption[] = {{"=-------------------=",
															"|\\Choices For Build |",
															"|\\   (-)Azbuki(-)   |",
															"|\\  (-)Xidiomas(-)  |",
															"|\\    (-)FAKT(-)    |",
															 "=-------------------=",
															"//Press a number(1-3)"},
															{"=-------------------=",
															"|\\Choices For Build |",
															"|\\   (-)ThePit(-)   |",
															"|\\  (-)Blocksmc(-)  |",
															"=-------------------=",
															"//Press a number(1-2)"},
															{"=-------------------=",
															 "|\\Choices For Build |",
															 "|\\   (-)DOOMz(-)    |",
															 "|\\    (-)BAK(-)     |",
															 "=-------------------=",
															 "//Press a number(1-2)" }};

	static const DisplayBuffer<33, 6> s_PlayAgainScreen = { " ","Do you want to play again?"," ","Press Y or N" };

	static const DisplayBuffer<34, 10> s_GameInterfaceHelp = { "/ ->Quick Game Interface Menu<- \\", " ", "A,S,D,W - Standart movement keys", "ESC - exit current game","R - restart current game"};
}
#pragma once

namespace MapSymbols
{
	constexpr char ce_WhiteSpace = ' ';

	namespace Borders
	{
		constexpr char ce_LRBorder = '|';
		constexpr char ce_ULBorder = '-';
		constexpr char ce_RAngleBorder = '/';
		constexpr char ce_LAngleBorder = '\\';

		inline bool isNotItemSymbolBorder(char itemSymbol)
		{
			return (itemSymbol != ce_ULBorder &&
				itemSymbol != ce_LRBorder &&
				itemSymbol != ce_LAngleBorder &&
				itemSymbol != ce_RAngleBorder);
		}
	}

	namespace Objects
	{
		constexpr char ce_Obsticle = '#';
		constexpr char ce_Player = '*';

		inline bool isValidItemSymbol(char itemSymbol)
		{
			return (itemSymbol != ce_Obsticle &&
					itemSymbol != ce_Player &&
					itemSymbol != ce_WhiteSpace &&
					Borders::isNotItemSymbolBorder(itemSymbol));
		}

		namespace Items
		{
			constexpr char ce_TeleportItem = '~';
		}
	}
}
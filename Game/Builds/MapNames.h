#pragma once
#include <Models/Buffer3D.hpp>

namespace MapNames
{
	static const Buffer2D<char, 12, 3> s_MapVariantsNames = { "|Alphabetic|","|Randomized|","|Imposter|" };

	static const Buffer3D<char, 3, 10, 3> s_MapBuildNames = { {"|Azbuki|","|Xidiomas|","|FAKT|"},
		                                                      {"|ThePit|", "|Blocksmc|"},
		                                                      {"|DOOMz|", "|BAK|"} };
}

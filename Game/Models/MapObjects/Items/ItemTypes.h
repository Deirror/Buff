#pragma once
#include "Item.h"
#include "TimyItem.h"
#include "TrollItem.h"
#include "TeleportItem.h"
//-----------------------------------
#include <Models/polymorphic_ptr.hpp>

enum class ItemType : unsigned char
{
	NormalItem,
	TeleportItem,
	TrollItem,
	TimyItem
};

ItemType getItemType(polymorphic_ptr<Item> item);
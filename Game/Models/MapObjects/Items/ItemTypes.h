#pragma once
#include "Item.h"
#include "NullItem.h"
#include "TimyItem.h"
#include "TrollItem.h"
#include "DeathItem.h"
#include "RandomItem.h"
#include "TeleportItem.h"
//-----------------------------------
#include <Models/polymorphic_ptr.hpp>

enum class ItemType : unsigned char
{
	NormalItem,
	NullItem,
	DeathItem,
	TeleportItem,
	TrollItem,
	TimyItem,
	RandomItem
};

ItemType getItemType(polymorphic_ptr<Item> item);
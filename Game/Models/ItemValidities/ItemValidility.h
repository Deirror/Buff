#pragma once
#include <Models/polymorphic_ptr.hpp>
//-----------------------------------
#include "../MapObjects/Items/Item.h"

struct ItemValidility
{
	virtual bool isItemValid(const polymorphic_ptr<Item>& item) const = 0;

	virtual ItemValidility* clone() const = 0;
	virtual ~ItemValidility() = default;
};

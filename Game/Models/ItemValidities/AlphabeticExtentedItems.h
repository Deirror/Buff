#pragma once
#include "AlphabeticOnlyItems.h"

struct AlphabeticExtentedItems : AlphabeticOnlyItems
{
	bool isItemValid(const polymorphic_ptr<Item>& item) const override;
	ItemValidility* clone() const override;
};


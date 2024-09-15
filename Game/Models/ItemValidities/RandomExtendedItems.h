#pragma once
#include "RandomOnlyItems.h"

struct RandomExtendedItems : RandomOnlyItems
{
	bool isItemValid(const polymorphic_ptr<Item>& item) const override;
	ItemValidility* clone() const override;
};


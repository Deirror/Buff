#pragma once
#include "ItemValidility.h"

struct RandomOnlyItems : ItemValidility
{
	bool isItemValid(const polymorphic_ptr<Item>& item) const override;
	ItemValidility* clone() const override;
};

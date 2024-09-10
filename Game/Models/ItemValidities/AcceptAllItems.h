#pragma once
#include "ItemValidility.h"

struct AcceptAllItems : ItemValidility
{
	bool isItemValid(const polymorphic_ptr<Item>& item) const override;
	ItemValidility* clone() const override;
};

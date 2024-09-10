#include "AlphabeticOnlyItems.h"

bool AlphabeticOnlyItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return ((item->getSymbol() >= 'A' && item->getSymbol() <= 'Z')||
            (item->getSymbol() >= 'a' && item->getSymbol() <= 'z'));
}

ItemValidility* AlphabeticOnlyItems::clone() const
{
    return new AlphabeticOnlyItems(*this);
}

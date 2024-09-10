#include "RandomOnlyItems.h"

bool RandomOnlyItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return (item->getSymbol() == '@');
}

ItemValidility* RandomOnlyItems::clone() const
{
    return new RandomOnlyItems(*this);
}

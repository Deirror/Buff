#include "RandomOnlyItems.h"
//----------------------------------
#include "../../Builds/MapSymbols.h"

bool RandomOnlyItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return (item->getSymbol() == MapSymbols::Objects::Items::ce_RandomItem);
}

ItemValidility* RandomOnlyItems::clone() const
{
    return new RandomOnlyItems(*this);
}

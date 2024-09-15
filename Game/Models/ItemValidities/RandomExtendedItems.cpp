#include "RandomExtendedItems.h"
//----------------------------------
#include "../../Builds/MapSymbols.h"

bool RandomExtendedItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return (RandomOnlyItems::isItemValid(item) ||
            MapSymbols::Objects::Items::isExtentedItem(item->getSymbol()));
}

ItemValidility* RandomExtendedItems::clone() const
{
    return new RandomExtendedItems(*this);
}

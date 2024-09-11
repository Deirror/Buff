#include "AlphabeticExtentedItems.h"
//----------------------------------
#include "../../Builds/MapSymbols.h"

bool AlphabeticExtentedItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return (AlphabeticOnlyItems::isItemValid(item) || 
            MapSymbols::Objects::Items::isExtentedItem(item->getSymbol()));
}

ItemValidility* AlphabeticExtentedItems::clone() const
{
    return new AlphabeticExtentedItems(*this);
}

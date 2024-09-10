#include "AcceptAllItems.h"

bool AcceptAllItems::isItemValid(const polymorphic_ptr<Item>& item) const
{
    return true;
}

ItemValidility* AcceptAllItems::clone() const
{
    return new AcceptAllItems(*this);
}

#include "ItemTypes.h"

ItemType getItemType(polymorphic_ptr<Item> item)
{
    if (dynamic_cast<TimyItem*>(item.get()))
    {
        return ItemType::TimyItem;
    }
    else if (dynamic_cast<TrollItem*>(item.get()))
    {
        return ItemType::TrollItem;
    }
    else if (dynamic_cast<TeleportItem*>(item.get()))
    {
        return ItemType::TeleportItem;
    }

    return ItemType::NormalItem;
}
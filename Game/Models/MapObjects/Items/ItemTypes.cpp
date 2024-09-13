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
    else if (dynamic_cast<RandomItem*>(item.get()))
    {
        return ItemType::RandomItem;
    }
    else if(dynamic_cast<NullItem*>(item.get()))
    {
        return ItemType::NullItem;
    }
    else if (dynamic_cast<DeathItem*>(item.get()))
    {
        return ItemType::DeathItem;
    }

    return ItemType::NormalItem;
}
#pragma once
#include "ItemValidities/AcceptAllItems.h"
#include "MapObjects/Items/Item.h"
#include "MapObjects/Obsticle.h"
#include "MapObjects/Player.h"
//-----------------------------------
#include <Models/polymorphic_ctr.hpp>
#include <Models/DisplayBuffer.hpp>
#include <Models/Dimension.h>

enum class MapSymbolType : uint8_t
{
	WhiteSpace,
	Obsticle,
	Border,
	Item
};

class Map
{
public:
	Map(Dimension dimensions, 
		uint8_t startSeconds = 0, 
		polymorphic_ptr<ItemValidility> itemCondition = make_polymorphic<AcceptAllItems>());

	void print() const;

	void setStartSeconds(uint8_t startSeconds);
	uint8_t getStartSeconds() const;

	void setPlayer(Coord playerCoords);
	Player getPlayer() const;

	void addObsticle(Obsticle obsticle);
	void addItem(const polymorphic_ptr<Item>& item);
	void addItem(polymorphic_ptr<Item>&& item);

	void removePlayer();
	void removeObsticle(Coord coords);
	void removeItem(Coord coords);

	MapSymbolType whatMapEntityIs(Coord coords) const;
	const polymorphic_ptr<Item>& getItem(Coord coords) const;

	void clear();

	void setDimensions(Dimension dimension);
	Dimension getDimensions() const;

	const polymorphic_ctr<Item>& getItems() const;
	size_t getItemsCount() const;

private:
	static constexpr Dimension s_MaxDimensions = { 58, 30 };
	static constexpr Dimension s_MinDimensions = { 26, 14 };

	static bool areDimensionsInRange(Dimension dimensions);

	void placeMapEntity(MapEntity mapEntity);
	void removeMapEntity(Coord coords);

	void addBorders();
	void addAngles();

	void addDashes(uint8_t row);
	void addPipes(uint8_t row);

	bool isValidCoord(Coord coords) const;

	bool isBorder(Coord coords) const;
	bool isObsticle(Coord coords) const;
	bool isWhiteSpace(Coord coords) const;
	bool isPlayer(Coord coords) const;

	bool isItem(Coord coords) const;

	bool areSpawnCoordsSet() const;

	DisplayBuffer<s_MaxDimensions.Width, s_MaxDimensions.Height> m_MapBuffer;
	Dimension m_Dimensions;

	polymorphic_ptr<ItemValidility> m_ItemsCondition;

	std::vector<Obsticle> m_Obsticles;
	polymorphic_ctr<Item> m_Items;

	Player m_Player;
	uint8_t m_StartSeconds = 0;
};
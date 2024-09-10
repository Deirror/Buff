#include "Map.h"
//-------------------------------
#include "../Builds/MapSymbols.h"
//-------------------------------
#include <stdexcept>

Map::Map(Dimension dimensions, uint8_t startSeconds, polymorphic_ptr<ItemValidility> itemCondition)
	: m_StartSeconds(startSeconds), m_ItemsCondition(itemCondition)
{
	setDimensions(dimensions);

	addBorders();
}

void Map::print() const
{
	for (uint8_t iter = 0; iter < m_Dimensions.Height; iter++)
	{
		Console::printLine(m_MapBuffer[iter].data(), Console::Alignment::Center);
	}
}

void Map::setStartSeconds(uint8_t startSeconds)
{
	m_StartSeconds = startSeconds;
}

uint8_t Map::getStartSeconds() const
{
	return m_StartSeconds;
}

void Map::setPlayer(Coord playerCoords)
{
	if (!isValidCoord(playerCoords))
	{
		throw std::out_of_range("The given coords are out of range");
	}

	if (!isWhiteSpace(playerCoords))
	{
		throw std::invalid_argument("The given player can't be placed. Other map object has already been placed");
	}

	m_Player.setCoords(playerCoords);
	placeMapEntity(m_Player);
}

Player Map::getPlayer() const
{
	return m_Player;
}

void Map::addObsticle(Obsticle obsticle)
{
	if (!isValidCoord(obsticle.getCoords()))
	{
		throw std::out_of_range("The given coords are out of range");
	}

	if (!isWhiteSpace(obsticle.getCoords()))
	{
		throw std::invalid_argument("The given obsticle can't be placed. Other map object has already been placed");
	}

	m_Obsticles.emplace_back(std::move(obsticle));
	placeMapEntity(obsticle);
}

void Map::addItem(const polymorphic_ptr<Item>& item)
{
	if (!isValidCoord(item->getCoords()))
	{
		throw std::out_of_range("The given coords are out of range");
	}

	if (!isWhiteSpace(item->getCoords()))
	{
		throw std::invalid_argument("The given item can't be placed. Other map object has already been placed");
	}

	if (!MapSymbols::Objects::isValidItemSymbol(item->getSymbol()))
	{
		throw std::invalid_argument("The given item has invalid item symbol");
	}

	if (m_ItemsCondition->isItemValid(item))
	{
		throw std::invalid_argument("The given item isn't valid for this map");
	}

	m_Items.push_back(item);
	placeMapEntity(*item);
}

void Map::addItem(polymorphic_ptr<Item>&& item)
{
	if (!isValidCoord(item->getCoords()))
	{
		throw std::out_of_range("The given coords are out of range");
	}

	if (!isWhiteSpace(item->getCoords()))
	{
		throw std::invalid_argument("The given item can't be placed. Other map object has already been placed");
	}

	if (!MapSymbols::Objects::isValidItemSymbol(item->getSymbol()))
	{
		throw std::invalid_argument("The given item has invalid item symbol");
	}

	if (!m_ItemsCondition->isItemValid(item))
	{
		throw std::invalid_argument("The given item isn't valid for this map");
	}

	m_Items.emplace_back(std::move(item));
	placeMapEntity(*item);
}

void Map::removePlayer()
{
	removeMapEntity(m_Player.getCoords());
	m_Player.setCoords(Coord());
}

void Map::removeObsticle(Coord coords)
{
	if (!isObsticle(coords))
	{
		throw std::invalid_argument("The given coords don't point at an obsticle");
	}

	for (auto iter = m_Obsticles.begin(); iter != m_Obsticles.end(); iter++)
	{
		if (iter->getCoords() == coords)
		{
			std::swap(*iter, *m_Obsticles.end());
			m_Obsticles.pop_back();
			removeMapEntity(coords);

			break;
		}
	}
}

void Map::removeItem(Coord coords)
{
	if (!isItem(coords))
	{
		throw std::invalid_argument("The given coords don't point at an item");
	}

	for (auto iter = m_Items.begin(); iter != m_Items.end(); iter++)
	{
		if (iter->get()->getCoords() == coords)
		{
			m_Items.removeAt(m_Items.end() - iter);
			removeMapEntity(coords);

			break;
		}
	}
}

MapSymbolType Map::whatMapEntityIs(Coord coords) const
{
	if (isWhiteSpace(coords) || isPlayer(coords))
	{
		return MapSymbolType::WhiteSpace;
	}
	else if (isObsticle(coords))
	{
		return MapSymbolType::Obsticle;
	}
	else if(isBorder(coords))
	{
		return MapSymbolType::Border;
	}

	return MapSymbolType::Item;
}

const polymorphic_ptr<Item>& Map::getItem(Coord coords) const
{
	if (!isItem(coords))
	{
		throw std::invalid_argument("The given coords don't point at an item");
	}

	for (const auto& item : m_Items)
	{
		if (item->getCoords() == coords)
		{
			return item;
		}
	}

	return nullptr;
}

bool Map::areSpawnCoordsSet() const
{
	return m_Player.areCoordsSet();
}

void Map::clear()
{
	for (auto iter = m_Items.rbegin(); iter != m_Items.rend(); iter++)
	{
		removeMapEntity(iter->get()->getCoords());
		m_Items.pop_back();
	}

	for (auto iter = m_Obsticles.rbegin() - 1; iter != m_Obsticles.rend(); iter++)
	{
		removeMapEntity(iter->getCoords());
		m_Obsticles.pop_back();
	}

	removePlayer();
}

void Map::setDimensions(Dimension dimension)
{
	if (!areDimensionsInRange(dimension))
	{
		throw std::out_of_range("The given dimensions are out of range");
	}

	m_Dimensions = dimension;
}

Dimension Map::getDimensions() const
{
	return m_Dimensions;
}

size_t Map::getItemsCount() const
{
	return m_Items.size();
}

bool Map::areDimensionsInRange(Dimension dimensions)
{
	return (dimensions >= s_MinDimensions && dimensions <= s_MaxDimensions);
}

void Map::placeMapEntity(MapEntity mapEntity)
{
	Coord coords = mapEntity.getCoords();
	uint8_t symbol = mapEntity.getSymbol();

	m_MapBuffer[(m_Dimensions.Height - 1) - coords.Y][coords.X] = symbol;
}

void Map::removeMapEntity(Coord coords)
{
	static const MapEntity whiteSpace = {coords, MapSymbols::ce_WhiteSpace};
	placeMapEntity(whiteSpace);
}

void Map::addBorders()
{
	addDashes(0);
	addDashes(m_Dimensions.Height - 1);
	
	addAngles();

	for (uint8_t row = 1; row < m_Dimensions.Height - 1; row++)
	{
		addPipes(row);
	}
}

void Map::addAngles()
{
	m_MapBuffer[0][0] = MapSymbols::Borders::ce_RAngleBorder;
	m_MapBuffer[0][m_Dimensions.Width - 1] = MapSymbols::Borders::ce_LAngleBorder;

	m_MapBuffer[m_Dimensions.Height - 1][0] = MapSymbols::Borders::ce_LAngleBorder;
	m_MapBuffer[m_Dimensions.Height - 1][m_Dimensions.Width - 1] = MapSymbols::Borders::ce_RAngleBorder;
}

void Map::addDashes(uint8_t row)
{
	for (uint8_t col = 1; col < m_Dimensions.Width - 1; col++)
	{
		m_MapBuffer[row][col] = MapSymbols::Borders::ce_ULBorder;
	}
}

void Map::addPipes(uint8_t row)
{
	m_MapBuffer[row][0] = MapSymbols::Borders::ce_LRBorder;
	m_MapBuffer[row][m_Dimensions.Width - 1] = MapSymbols::Borders::ce_LRBorder;

	for (uint8_t col = 1; col < m_Dimensions.Width - 1; col++)
	{
		m_MapBuffer[row][col] = MapSymbols::ce_WhiteSpace;
	}
}

bool Map::isValidCoord(Coord coords) const
{
	return ((coords.X > 0 && coords.X < m_Dimensions.Width - 1) &&
			(coords.Y > 0 && coords.Y < m_Dimensions.Height - 1));
}

bool Map::isBorder(Coord coords) const
{
	return !isValidCoord(coords);
}

bool Map::isWhiteSpace(Coord coords) const
{
	return (m_MapBuffer[(m_Dimensions.Height - 1) - coords.Y][coords.X] == MapSymbols::ce_WhiteSpace);
}

bool Map::isPlayer(Coord coords) const
{
	return (m_MapBuffer[(m_Dimensions.Height - 1) - coords.Y][coords.X] == MapSymbols::Objects::ce_Player);
}

bool Map::isItem(Coord coords) const
{
	return (!isBorder(coords) && !isWhiteSpace(coords) && !isObsticle(coords) && !isPlayer(coords));
}

bool Map::isObsticle(Coord coords) const
{
	return (m_MapBuffer[(m_Dimensions.Height - 1) - coords.Y][coords.X] == MapSymbols::Objects::ce_Obsticle);
}
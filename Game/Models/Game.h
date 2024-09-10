#pragma once
#include "Map.h"
//-----------------------
#include <Models/Timer.h>

class Game
{
public:
	Game(const Map& map);
	const Map& getMap() const;

	void startTimer();

	uint8_t getPlayedTime() const;
	Player  getCurrentPlayer() const;

	uint8_t  getLeftTime() const;
	uint16_t getPoints() const;

	bool isEnded() const;

	bool areAllItemsCollected() const;
	bool isTimeOut() const;

	void decrementLeftTime();
	void updateCurrentPlayer(Coord coords);

	void setPoints(uint16_t  points);
	void setLeftTime(uint8_t leftTime);

	void addCollectedItemCoords(Coord coords);

	uint8_t getCollectedItems() const;

	bool hasCollectedItem(Coord coords) const;
	void updateGameStats(polymorphic_ptr<Item> item);

private:
	void calculateUncollectableItemsCount();

	Map m_Map;

	Timer m_PlayedTime;

	Player m_CurrentPlayer;

	uint8_t  m_LeftTime = NULL;
	uint16_t m_Points = NULL;

	std::vector<Coord> m_CollectedItemsCoords;
	uint8_t m_UncollectableItems = NULL;
};
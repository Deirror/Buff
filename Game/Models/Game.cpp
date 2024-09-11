#include "Game.h"

Game::Game(const Map& map) 
    : m_Map(map), 
      m_CurrentPlayer(map.getPlayer()), 
      m_LeftTime(map.getStartSeconds()) 
{
    calculateUncollectableItemsCount();
}

const Map& Game::getMap() const
{
    return m_Map;
}

void Game::startTimer()
{
    m_PlayedTime.start();
}

void Game::endTimer()
{
    m_PlayedTime.report();
}

const Timer& Game::getPlayedTime() const
{
    return m_PlayedTime;
}

Player Game::getCurrentPlayer() const
{
    return m_CurrentPlayer;
}

uint8_t Game::getLeftTime() const
{
    return m_LeftTime;
}

uint16_t Game::getPoints() const
{
    return m_Points;
}

bool Game::isEnded() const
{
    return (isTimeOut() || areAllItemsCollected());
}

bool Game::areAllItemsCollected() const
{
    return (m_CollectedItemsCoords.size() == (m_Map.getItemsCount() - m_UncollectableItems));
}

bool Game::isTimeOut() const
{
    return (m_LeftTime == NULL);
}

void Game::decrementLeftTime()
{
    m_LeftTime--;
}

void Game::updateCurrentPlayerCoords(Coord coords)
{
    m_CurrentPlayer.setCoords(coords);
}

void Game::setPoints(uint16_t points)
{
    m_Points = points;
}

void Game::setLeftTime(uint8_t leftTime)
{
    m_LeftTime = leftTime;
}

void Game::addCollectedItemCoords(Coord coords)
{
    m_CollectedItemsCoords.push_back(coords);
}

uint8_t Game::getCollectedItemsCount() const
{
    return m_CollectedItemsCoords.size();
}

bool Game::hasCollectedItemCoords(Coord coords) const
{
    for (const auto itemCoords : m_CollectedItemsCoords)
    {
        if (itemCoords == coords)
        {
            return TRUE;
        }
    }

    return FALSE;
}

void Game::updateGameStats(polymorphic_ptr<Item> item)
{
    if (!item)
    {
        throw std::invalid_argument("The given item is null");
    }

    item->modifyPoints(m_Points);
    item->modifySeconds(m_LeftTime);
}

void Game::calculateUncollectableItemsCount()
{
    const polymorphic_ctr<Item>& items = m_Map.getItems();

    for (const auto& item : items)
    {
        if (!item->isCollectable())
        {
            m_UncollectableItems++;
        }
    }
}
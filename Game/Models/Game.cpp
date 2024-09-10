#include "Game.h"

Game::Game(const Map& map) 
    : m_Map(map), 
      m_CurrentPlayer(map.getPlayer()), 
      m_LeftTime(map.getStartSeconds()) {}

const Map& Game::getMap() const
{
    return m_Map;
}

void Game::startTimer()
{
    m_PlayedTime.start();
}

uint8_t Game::getPlayedTime() const
{
    return m_PlayedTime.getDuration();
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
    return (m_CollectedItemsCoords.size() == m_Map.getItemsCount());
}

bool Game::isTimeOut() const
{
    return (m_LeftTime == NULL);
}

void Game::decrementLeftTime()
{
    m_LeftTime--;
}

void Game::updateCurrentPlayer(Coord coords)
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

uint8_t Game::getCollectedItems() const
{
    return m_CollectedItemsCoords.size();
}

bool Game::hasCollectedItem(Coord coords) const
{
    for (const auto itemCoords : m_CollectedItemsCoords)
    {
        if (itemCoords == coords)
        {
            return true;
        }
    }

    return false;
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

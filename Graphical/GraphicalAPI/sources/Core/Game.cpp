/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include "Core/Game.hpp"
#include <cstdlib>
#include <iostream>

zapi::Game::Game(const std::string &title)
: window(title)
, tiles()
, teams()
{
    std::srand(std::time(nullptr));
    initialize();
}

void zapi::Game::initialize()
{
    for (float i = 0, x = 0, y = 0; i != 900; i++, x += 100) {
        if (x >= 3000) {
            x = 0;
            y += 100;
        }
        tiles.push_back(Tile(sf::Vector2f(100, 100), sf::Vector2f(x, y)));
    }
}

void zapi::Game::start()
{
    loop();
}

void zapi::Game::loop()
{
    while (window.isOpen()) {
        window.update();
        window.drawEntities(tiles);
        for (auto &team : teams)
            window.drawEntities(team.getPlayers());
        window.display();
    }
}

void zapi::Game::addTeam(const std::string &teamName)
{
    teams.push_back(Team(teamName));
}

void zapi::Game::addPlayer(const std::string &teamName, int id, const sf::Vector2f &position)
{
    for (auto &team : teams)
        if (team.getName() == teamName) {
            zapi::Tile *tile = findTile(position);
            team.addPlayer(id, tile, position + sf::Vector2f(50 - 32, 50 - 32));
            return;
        }
    addTeam(teamName);
    addPlayer(teamName, id, position);
}

zapi::Tile *zapi::Game::findTile(const sf::Vector2f &position)
{
    unsigned int index = ((int)position.x / 100) + (((int)position.y / 100) * 30);
    return &tiles[index];
}

void zapi::Game::movePlayer(unsigned int id, ORIENTATION direction)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            team.getPlayer(id).move(direction);
            team.getPlayer(id).resetTile(findTile(team.getPlayer(id).getPosition()));
            return;
        }
    }
}

void zapi::Game::dropResourcePlayer(unsigned int id, RESOURCE_NUMBER index)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            auto player = team.getPlayer(id);
            player.dropResource(index);
            return;
        }
    }
}

void zapi::Game::pickUpResourcePlayer(unsigned int id, RESOURCE_NUMBER index)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            auto player = team.getPlayer(id);
            player.pickUpResource(index);
        }
    }
}

void zapi::Game::updateTile(sf::Vector2f vector, std::vector<zapi::Resource> &res)
{
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tiles[i].getPosition() == vector) {
            tiles[i].updateResource(res);
            return;
        }
    }
}

void zapi::Game::removePlayer(unsigned int id)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            team.removePlayer(id);
            return;
        }
    }
}

void zapi::Game::updatePlayerOrientation(unsigned int id, ORIENTATION direction)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            team.updatePlayerOrientation(id, direction);
            return;
        }
    }
}

void zapi::Game::levelUpPlayer(unsigned int id)
{
    for (auto &team : teams) {
        if (team.checkPlayer(id)) {
            auto player = team.getPlayer(id);
            player.levelUp();
            return;
        }
    }
}

zapi::Player zapi::Game::getPlayer(unsigned int id)
{
    for (auto &team : teams)
        if (team.checkPlayer(id))
            return team.getPlayer(id);
    return Player(-1, nullptr);
}

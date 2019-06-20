/*
** EPITECH PROJECT, 2019
** Tile.cpp
** File description:
** Tile implementation
*/

#include <cstdlib>
#include "Tile.hpp"

zapi::Tile::Tile(sf::Texture *tileTexture, sf::Texture *resourceTexture, const sf::Vector2f &size, const sf::Vector2f &position)
: Entity(position)
, size(size)
, resources()
, sprite()
{
    sprite.setTexture(*tileTexture);
    sprite.setPosition(position);

    for (int i = 0; i != 7; i++)
        resources.push_back(Resource(resourceTexture, sf::Vector2f(size.x/8, size.y/8), position + sf::Vector2f((std::rand()%((int)size.x - (int)size.x/8)), (std::rand()%((int)size.y - (int)size.y/8)))));
}

void zapi::Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void zapi::Tile::removeResource(RESOURCE_NUMBER index)
{
    resources[index]--;
}

void zapi::Tile::addResource(RESOURCE_NUMBER index)
{
    resources[index]++;
}

void zapi::Tile::updateResource(std::vector<Resource> res)
{
    resources = res;
}
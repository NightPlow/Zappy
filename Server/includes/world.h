/*
** EPITECH PROJECT, 2018
** world.h
** File description:
** world generation header
*/

#pragma once

#include "map.h"
#include "teams.h"
#include "resources.h"
#include "graphical/protocols.h"
#include "linked_list.h"

struct tile_content_s {
    int *resources; // -1 at the end
    linked_list_t players_id; // of type unsigned int
    int player_nb;
};

typedef struct tile_content_s tile_content_t;

struct player_s {
    unsigned int id;
    unsigned int team_id;
    uint8_t level;
    unsigned int hp;
    enum ORIENTATION direction;
    unsigned int resources[DEFAULT_RESOURCES_NUMBER];
    unsigned int x;
    unsigned int y;
};

typedef struct player_s player_t;

struct world_s {
    size_t width;
    size_t height;
    unsigned int f;
    tile_content_t **tiles;
    resource_t *resources; // available resources
    linked_list_t players; // of type struct player_s
    team_t *teams; // End with a team at 0
};

typedef struct world_s world_t;

world_t generate_world(const size_t width, const size_t height,
        const size_t f, const char *resources_filename);
void generate_resources(int **resources, const resource_t *available);
tile_content_t **init_tiles(const size_t width, const size_t height,
        const int max_resources);
void update_world_resources(world_t *world);
world_t *worlddup(world_t *world);
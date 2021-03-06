/*
** EPITECH PROJECT, 2018
** world_generation.c
** File description:
** generate world
*/

#include <stdlib.h>
#include <string.h>

#include "resources.h"
#include "world.h"
#include "graphical/protocols.h"
#include "error.h"

void generate_resources(int **resources, const resource_t *available,
        int percentage_scale)
{
    if (resources == 0x0 || available == 0x0)
        return;
    for (size_t i = 0 ; i < DEFAULT_RESOURCES_NUMBER ; i++)
        (*resources)[i] +=
            ((rand() % 100) < available[i].percentage / percentage_scale)
                ? 1 : 0;
}

tile_content_t **init_tiles(const size_t width, const size_t height,
        const int max_resources)
{
    tile_content_t **tiles = 0x0;

    if (width == 0 || height == 0)
        return (0x0);
    tiles = calloc(1, width * sizeof(tile_content_t *));
    check_malloc(tiles);
    for (size_t i = 0 ; i < width ; i++) {
        tiles[i] = calloc(1, height * sizeof(tile_content_t));
        check_malloc(tiles[i]);
        for (size_t j = 0 ; j < height ; j++) {
            tiles[i][j].resources = calloc(1,
                    (max_resources + 1) * sizeof(int));
            check_malloc(tiles[i][j].resources);
            tiles[i][j].resources[max_resources] = -1;
        }
    }
    return (tiles);
}

int generate_world(world_t *world, const char *resources_filename)
{
    size_t max_resources = 0;

    world->resources = parse_resources(resources_filename);
    while (world->resources[max_resources++].name != 0x0);
    world->tiles = init_tiles(world->width, world->height, max_resources);
    update_world_resources(world, 1);
    return (0);
}

world_t *worlddup(world_t *world)
{
    world_t *new = calloc(sizeof(world_t), 1);

    new->width = world->width;
    new->height = world->height;
    new->f = world->f;
    new->tiles = world->tiles;
    new->resources = world->resources;
    new->players = world->players;
    return (new);
}

void update_world_resources(world_t *world, int percentage_scale)
{
    for (size_t x = 0 ; x < world->width ; x++) {
        for (size_t y = 0 ; y < world->height ; y++) {
            generate_resources(&world->tiles[x][y].resources,
                    world->resources, percentage_scale);
        }
    }
}

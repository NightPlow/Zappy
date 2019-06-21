/*
** EPITECH PROJECT, 2018
** elevation_handlers.c
** File description:
** Elevation handlers - Unit Tests
*/

#include <criterion/criterion.h>
#include "ai/handlers/movement_handlers.h"

Test(elevation_handler, test_elevation_handler)
{
    world_t world = generate_world(4, 4, 0, 0x0);
    player_t *player1 = 0x0;
    player_t *player2 = 0x0;

    add_player(&world, 0);
    add_player(&world, 1);
    player1 = (player_t *) world.players.head->data;
    player1->x = 1;
    player1->y = 1;
    player2 = (player_t *) world.players.head->next->data;
    append(&world.tiles[1][1].players_id, &player1->id);
    append(&world.tiles[1][1].players_id, &player2->id);
    world.tiles[1][1].resources[1] = 1;
    elevation_handler(&world, player1, 0x0);
    cr_assert_eq(strcmp(get_response(),
                "Elevation underway\nCurrent level: 1\n"), 0);
}
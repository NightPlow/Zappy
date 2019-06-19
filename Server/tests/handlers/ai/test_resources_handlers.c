/*
** EPITECH PROJECT, 2018
** resources_handlers.c
** File description:
** Resources handlers - Unit Tests
*/

#include <criterion/criterion.h>
#include "ai/handlers/resources_handlers.h"

Test(take_object_handler, test_take_object_handler)
{
    const char *args[] = {"Linemate", NULL};
    world_t world = generate_world(4, 4, 0, 0x0);
    player_t *head = 0x0;

    world.f = 100;
    add_player(&world, 0);
    head = (player_t *) world.players.head->data;
    head->x = 1;
    head->y = 1;
    world.tiles[1][1].resources[1] = 1;
    take_object_handler(&world, head, 100, args);
    cr_assert_eq(head->resources[1], 1);
    cr_assert_eq(world.tiles[1][1].resources[1], 0);
}

Test(set_down_object_handler, test_set_down_object_handler)
{
    const char *args[] = {"Linemate", NULL};
    world_t world = generate_world(4, 4, 0, 0x0);
    player_t *head = 0x0;
    int old_resources_nbr_on_tile = 0;

    world.f = 100;
    add_player(&world, 0);
    head = (player_t *) world.players.head->data;
    head->x = 1;
    head->y = 1;
    head->resources[1] = 1;
    old_resources_nbr_on_tile = world.tiles[1][1].resources[1];
    set_down_object_handler(&world, head, 100, args);
    cr_assert_eq(head->resources[1], 0);
    cr_assert_eq(world.tiles[1][1].resources[1], old_resources_nbr_on_tile + 1);
}

Test(inventory_handler, test_inventory_handler)
{
    world_t world = generate_world(4, 4, 0, 0x0);
    player_t *head = 0x0;

    world.f = 100;
    add_player(&world, 0);
    head = (player_t *) world.players.head->data;
    head->x = 1;
    head->y = 1;
    head->resources[1] = 1;
    head->resources[2] = 5;
    head->resources[5] = 3;
    inventory_handler(&world, head, 100, 0x0);
}

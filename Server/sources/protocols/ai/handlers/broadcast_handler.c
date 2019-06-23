/*
** EPITECH PROJECT, 2018
** player_info_handlers.c
** File description:
** Handle every action on player informations.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "ai/handlers/broadcast_handler.h"

void broadcast(client_t (*clients)[MAX_CLIENT], world_t *world,
        player_t *player)
{
    int k = 0;
    char *res = 0x0;
    player_t *tmp = 0x0;

    if (!player->broadcast_text)
        return;
    for (int i = 0 ; i < MAX_CLIENT ; i++) {
        if ((*clients)[i].client_nb == (int) player->id ||
                (*clients)[i].type != AI || (*clients)[i].client_nb == -1)
            continue;
        player_t *tmp = get_player(world->players,
                (*clients)[i].client_nb);
        k = getBroadcastTile(world, player, tmp);
        k += ((tmp->orientation - 1) * 2) % 8;
        asprintf(&res, "message %d, %s\n", k, player->broadcast_text);
        write((*clients)[i].sockfd, res, strlen(res));
        free(player->broadcast_text);
        player->broadcast_text = 0x0;
    }
}

int getBroadcastTile(world_t *world, player_t *src_player, player_t *dest_player)
{
    unsigned int xc = 0;
    unsigned int yc = 0;
    unsigned int tangente = 0;
    unsigned int alpha = 0;

    if (src_player->x - dest_player->x > world->width / 2)
        dest_player->x += world->width;
    if (src_player->y - dest_player->y > world->height / 2)
        dest_player->y += world->height;
    xc = src_player->x;
    yc = dest_player->y;
    tangente = xc / yc;
    alpha = atan(tangente);
    alpha = (dest_player->y > src_player->y) ? alpha + 180 : alpha;
    return ((alpha - 22.5) / 45 + 1);
}

int broadcast_handler(world_t *world, player_t *player,
        const char __attribute__((unused)) **args)
{
    if (!args || !args[0])
        return (TOO_FEW_PARAMETERS);
    else if (args[1])
        return (TOO_MUCH_PARAMETERS);
    player->broadcast_text = calloc(1, sizeof(char) * (strlen(args[0]) + 1));
    strcpy(player->broadcast_text, args[0]);
    set_response("ok\n");
    return (NO_ERROR);
}

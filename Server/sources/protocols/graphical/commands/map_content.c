/*
** EPITECH PROJECT, 2018
** handle_map_content.c
** File description:
** handle map_content
*/

#include <string.h>
#include <unistd.h>

#include "graphical/commands.h"
#include "graphical/protocols.h"
#include "world.h"

int assign_map_content(world_t *world, int sockfd)
{
    sender_t senders[MAX_SENDERS] = {{0}};

    senders[WORLD_SENDER_POS] = (sender_t){world, sizeof(world_t), sockfd, 0};
    senders[CUSTOM_SENDER_POS].is_last = 1;
    return (send_map_content(convert_senders_to_data(senders)));
}

int send_map_content(const void *data)
{
    sender_t *senders = get_senders_from_data(data);
    size_t size = PKT_HDR_LEN + SRV_TILE_CONTENT_LEN;
    world_t *world = 0x0;
    char *to_write = 0x0;
    int subid = SRV_TILE_CONTENT;

    if (count_senders(senders) != 1)
        return (-1);
    world = (world_t*)(senders[0].data);
    for (unsigned int i = 0 ; i < world->width ; i++) {
        for (unsigned int j = 0 ; j < world->height ; i++) {
            subid = (j + 1 == world->height && i + 1 == world->width)
                ? 1 : SRV_TILE_CONTENT;
            to_write = write_tile_content(&world->tiles[i][j], i, j, subid);
            write(senders[0].sockfd, to_write, size);
            free(to_write);
        }
    }
    free(senders);
    return (CLT_MAP_CONTENT);
}

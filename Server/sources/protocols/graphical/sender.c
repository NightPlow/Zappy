/*
** EPITECH PROJECT, 2018
** sender.c
** File description:
** handle sender
*/

#include <stdlib.h>
#include <string.h>

#include "graphical/commands.h"

sender_t *get_senders_from_data(const void *data)
{
    int *magic_num = (int *)(data);
    int offset = sizeof(int);
    sender_t *senders = 0x0;
    sender_t *tmp = 0x0;
    size_t size = 0;

    if (*magic_num != SENDER_MAGIC_NUM)
        return 0x0;
    do {
        senders = realloc(senders, (size + 2) * sizeof(sender_t));
        tmp = senders + size;
        tmp = memcpy(tmp, data + offset, sizeof(sender_t));
        *(tmp + 1) = (sender_t){0};
        size++;
        offset += sizeof(sender_t);
    } while (!senders[size - 1].is_last);
    return (senders);
}

void *convert_senders_to_data(const sender_t *senders)
{
    int i = 0;
    int magic_num = SENDER_MAGIC_NUM;
    int offset = SENDER_MAGIC_NUM_LEN;
    char *data = 0x0;
    char *tmp = 0x0;

    if (senders == 0x0)
        return (0x0);
    data = malloc(SENDER_MAGIC_NUM_LEN);
    data = memcpy(data, &magic_num, SENDER_MAGIC_NUM_LEN);
    while (!senders[i].is_last) {
        data = realloc(data, offset + (sizeof(sender_t) * 2));
        tmp = data + offset;
        tmp = memcpy(tmp, &senders[i++], sizeof(sender_t));
        offset += sizeof(sender_t);
    }
    if (i == 0)
        data = realloc(data, offset + sizeof(sender_t));
    tmp = data + offset;
    tmp = memcpy(tmp, &senders[i], sizeof(sender_t));
    return (data);
}

size_t count_senders(const sender_t *senders)
{
    size_t size = 0;

    while (!senders[size++].is_last);
    return (size);
}

void destroy_senders(sender_t *senders)
{
    size_t i = 0;

    while (!senders[i].is_last)
        free((char *)senders[i++].data);
    free((char *)senders[i].data);
    free(senders);
}

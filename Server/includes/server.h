/*
** EPITECH PROJECT, 2018
** server.h
** File description:
** server header
*/

/**
 * \file server.h
 * \brief server functions.
 * \date Jun, 23 2019
 *
 */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/select.h>

#include "client.h"
#include "graphical/protocols.h"
#include "ai/protocols.h"
#include "world.h"

#define DEFAULT_PORT_AI 6000
#define DEFAULT_PORT_GRAPH 6001
#define DEFAULT_FREQUENCE 1000
#define DEFAULT_CLIENT_NB 4
#define DEFAULT_MAP_WIDTH 5
#define DEFAULT_MAP_HEIGHT 5

struct input_s {
    unsigned int port;
    unsigned int width;
    unsigned int height;
    unsigned int client_nbr;
    unsigned int frequence;
    char **names;
    char *resources_filename;
};

typedef struct input_s input_t;

struct server_s {
    int sockfd;
    unsigned int port;
    fd_set readfds;
    struct sockaddr_in sockaddr;
    struct client_s clients[MAX_CLIENT];
};

typedef struct server_s server_t;

struct game_s {
    phr_t handler_register;
    ahr_t action_register;
    world_t world;
};

typedef struct game_s game_t;

struct info_s {
    int port_ai;
    int port_graph;
    input_t input;
    server_t server_ai;
    server_t server_graph;
    game_t game;
};

typedef struct info_s info_t;

/* destroy_struct.c */

void free_array(char **array);
void free_input(input_t *input);

/* init_info.c */

int init_info(int ac, char **av, info_t *info);
void destroy_info(info_t *info);

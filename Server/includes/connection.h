/*
** EPITECH PROJECT, 2018
** connection.h
** File description:
** connection header
*/

/**
 * \file connection.h
 * \brief connection functions.
 * \date Jun, 23 2019
 *
 */

#pragma once

#include <sys/socket.h>
#include <string.h>

#include "server.h"
#include "client.h"

int init_connection(server_t *server, enum client_type type);
int set_fds(fd_set *readfds, client_t const clients[MAX_CLIENT],
    int const sockfd);
int get_new_connection(fd_set *readfds, client_t (*clients)[MAX_CLIENT],
    int const main_socket);

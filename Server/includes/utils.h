/*
** EPITECH PROJECT, 2018
** utils.h
** File description:
** utils header
*/

/**
 * \file utils.h
 * \brief utils  functions.
 * \date Jun, 23 2019
 *
 */

#pragma once

#define READ_SIZE 2048

char *get_next_line(int fd);

char **str_to_tab(char const *str, char const *separators);

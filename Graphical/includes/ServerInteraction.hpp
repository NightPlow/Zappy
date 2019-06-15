/*
** EPITECH PROJECT, 2018
** ServerInteraction.hpp
** File description:
** Protocol header
*/

#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <string>

#include "protocols.h"
#include "Errors.hpp"

namespace communication {

    class ServerInteraction {
    public:
        ServerInteraction(unsigned int port, const std::string &ipAddress);
        ServerInteraction();
        ~ServerInteraction() = default;

        void requestMapSize(void) const;
        void requestTileContent(void) const;
        void requestMapContent(void) const;
        void requestTeamsNames(void) const;
        void requestPlayerPosition(void) const;
        void requestPlayerLevel(void) const;
        void requestPlayerInventory(void) const;
        void requestTimeUnit(void) const;
        void requestTimeUpdate(void) const;
        
        unsigned int getSocket(void) const { return _sockfd; }
    private:
        void sendPacket(uint8_t id, uint16_t size, uint16_t subid) const;

        unsigned int _port;
        int _sockfd;
    };
}
/*
** EPITECH PROJECT, 2018
** ServerInteraction.cpp
** File description:
** Handle protocol
*/

#include "ServerInteraction.hpp"

communication::ServerInteraction::ServerInteraction(unsigned int port,
        const std::string &ipAddress) :
    events({"socket"}),
    port(port),
    sockfd(0)
{
    struct sockaddr_in sockaddr;

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    if (inet_aton(ipAddress.c_str(), &sockaddr.sin_addr) == -1)
        throw ServerInteractionErrors("Can't convert ip address");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        throw ServerInteractionErrors("Invalid Socket");
    std::cout << "Try connection to host: " << ipAddress;
    std::cout << "with socket " << sockfd << std::endl;
    if (connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1)
        throw ServerInteractionErrors("Unable to connect to server");
    std::cout << "Successful connection to host: " << ipAddress << std::endl;
}

communication::ServerInteraction::ServerInteraction() :
    events({"socket"}),
    port(0),
    sockfd(-1)
{
}

communication::ServerInteraction::~ServerInteraction()
{
    this->requestCloseConnection();
    close(sockfd);
    std::cout << "End connection" << std::endl;
}

void communication::ServerInteraction::setNonBlockingSocket(void)
{
    int flags = 0;

    flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

srv_map_size_t communication::ServerInteraction::requestMapSize(void) const
{
    communication::Packet<clt_map_size_t> pkt(CLT_MAP_SIZE, sockfd);
    communication::Packet<srv_map_size_t> pkt2(SRV_MAP_SIZE, sockfd);
    srv_map_size_t map = {0, 0};

    pkt << 0x0;
    pkt2 >> &map;
    return (map);
}

void communication::ServerInteraction::requestTileContent(unsigned int x,
        unsigned int y) const
{
    clt_tile_content_t tile = {x, y};
    communication::Packet<clt_tile_content_t> pkt(CLT_TILE_CONTENT, sockfd,
            CLT_TILE_CONTENT_LEN);

    pkt << &tile;
}

void communication::ServerInteraction::requestMapContent(void) const
{
    communication::Packet<clt_map_content_t> pkt(CLT_MAP_CONTENT, sockfd);

    pkt << 0x0;
}

void communication::ServerInteraction::requestTeamsNames(void) const
{
    communication::Packet<clt_teams_names_t> pkt(CLT_TEAMS_NAMES, sockfd);

    pkt << 0x0;
}

void communication::ServerInteraction::requestPlayerPosition(unsigned int id) const
{
    clt_player_pos_t player = {id};
    communication::Packet<clt_player_pos_t> pkt(CLT_PLAYER_POSITION, sockfd,
            CLT_PLAYER_POS_LEN);

    pkt << &player;
}

void communication::ServerInteraction::requestPlayerLevel(unsigned int id) const
{
    clt_player_level_t player = {id};
    communication::Packet<clt_player_level_t> pkt(CLT_PLAYER_LEVEL, sockfd,
            CLT_PLAYER_LEVEL_LEN);

    pkt << &player;
}

void communication::ServerInteraction::requestPlayerInventory(unsigned int id) const
{
    struct clt_player_inventory player = {id};
    communication::Packet<struct clt_player_inventory>
        pkt(CLT_PLAYER_INVENTORY, sockfd, CLT_PLAYER_INVENTORY_LEN);

    pkt << &player;
}

void communication::ServerInteraction::requestTimeUnit(void) const
{
    communication::Packet<char> pkt(CLT_TIME_UNIT_REQUEST, sockfd);

    pkt << 0x0;
}

void communication::ServerInteraction::requestTimeUpdate(void) const
{
    communication::Packet<char> pkt(CLT_TIME_UNIT_CHANGE, sockfd);

    pkt << 0x0;
}

void communication::ServerInteraction::requestCloseConnection(void) const
{
    clt_close_connection_t clt = {0};
    communication::Packet<clt_close_connection_t> pkt(CLT_CLOSE_CONNECTION, sockfd,
            CLT_CLOSE_CONNECTION_LEN);

    pkt << &clt;
    pkt >> &clt;
}

void communication::ServerInteraction::listenSocket(void)
{
    pkt_header_t hdr = {0, 0, 0, 0};
    char *data = 0x0;
    int result = 0;

    result = read(sockfd, &hdr, PKT_HDR_LEN);
    if (result <= 0)
        return;
    data = (char*)calloc(1, hdr.size);
    result = read(sockfd, data, hdr.size);
    if (result <= 0)
        return;
    events.notify("socket", hdr.id, data);
    free(data);
}

#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include <SFML/Network.hpp>

class Server{
    //The number of players connected to this server
    int player_count;
    sf::SelectorUDP selector;


    public:
        Server();

};


#endif // NETWORK_H_INCLUDED

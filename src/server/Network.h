/**
This class houses the server code for the game

*/

#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include "GameTimer.h"

//server port
const unsigned short SERVER_PORT = 9999;

using namespace std;
typedef pair<const sf::IPAddress, int> player;

class Server{
    //The number of players connected to this server
    int player_count;
    //sf::SelectorUDP selector;
    sf::IPAddress serverIP;
    //server socket
    sf::SocketUDP serverSocket;
    //Let's players join the server
    void playerJoinLoop(int numPlayers);
    //Runs the server in the background while the players play
    void serverLoop();
    //deprecated
    void getScores();
    //set of client addresses
    set<sf::IPAddress> addresses;
    //maps IP's to scores
    map<sf::IPAddress, int> scores;

    public:
        Server();

};

//Used to easily determine the winning player(s)
struct PlayerRepresentation
{
    std::string name;
    int score;

    PlayerRepresentation(std::string _name, int _score)
    : name(_name), score(_score){}

     bool operator< (const PlayerRepresentation& p) const;


};

//needed for sorting players
bool PlayerRepresentation::operator< (const PlayerRepresentation& p) const
{
  return (score < p.score);
}


Server::Server()
{
    //server IP
    serverIP = sf::IPAddress::GetLocalAddress();

    //bind server socket to port
    if (!serverSocket.Bind(SERVER_PORT))
    {
        cout <<" error starting server on port " << SERVER_PORT;
        exit(0);
    }
    //serverSocket.SetBlocking(false);

    cout << "Server started on " << serverIP.ToString() << ":" << SERVER_PORT << endl;
    cout << "Enter number of players for this server: ";
    cin >> player_count;
    cout << "Waiting for " << player_count << " players to join." << endl;
    playerJoinLoop(player_count);
    serverLoop();
}

//Waits for all players to join the game, then starts the game
void Server::playerJoinLoop(int numPlayers)
{
    unsigned short local_port = SERVER_PORT; //needed since the socket methods don't accept constants
    serverSocket.SetBlocking(false); //so the server doesn't hang
    int broadcast_num = 0; //keeps track of the number of broadcasts

    while (numPlayers > 0)
    {
        //refreshes the port every 10 broadcasts so that unsent packets don't accumulate
        if (broadcast_num > 10)
        {
            broadcast_num = 0;
            serverSocket.Unbind(); //flush socket
            serverSocket.Bind(local_port);
        }


        sf::Packet broadcastPacket;
        broadcastPacket << serverIP.ToString();
        serverSocket.Send(broadcastPacket, sf::IPAddress("255.255.255.255"), 9999); //UDP broadcast
        broadcast_num++;

        //cout << endl << "Server is broadcasting" << endl;

        sf::Packet receivedPacket;
        if (serverSocket.Receive(receivedPacket, serverIP, local_port) == sf::Socket::Done)
        {
            // Check that a connect message was sent
            string msg;
            string clientIP;
            receivedPacket >> msg;
            receivedPacket >> clientIP;
            cout << msg << endl;
            if (msg == "connect")
            {
                // Show the address of the sender
                std::cout << clientIP << " connected to the server" << std::endl;
                //store player info
                addresses.insert(clientIP);
                scores.insert(pair<sf::IPAddress, int>(sf::IPAddress(clientIP), 0));
                cout << "Waiting for " << --numPlayers << " more players to join." << endl;
            }
        }
        sf::Sleep(0.2f);
    }

    cout << "All players connected, game starting!" << endl;
    serverSocket.Unbind(); //unbind then rebind quickly to basically flush the socket
    serverSocket.Bind(local_port);

    sf::Packet startPacket;
    startPacket << "start";
    startPacket << player_count;
    set<sf::IPAddress>::iterator pos = addresses.begin();

    for (int i = 0; i < player_count; i++) //send start message to all players
    {
        sf::IPAddress address = *pos;
        serverSocket.Send(startPacket, address, local_port);
        pos++;
    }
}

void Server::serverLoop()
{
    bool gameOver = false;
    unsigned short local_port = SERVER_PORT; //needed since the socket methods don't accept constants
    GameTimer timer(300);
    timer.start();
    //keep looping until the time limit is reached
    while(!gameOver)
    {
        float time = timer.getTimeRemaining();
        if (time <= 0)
            gameOver = true;

            cout <<"Server time remaining " << time << " seconds" << endl;
        /*
        //update scores
        getScores();

        set<sf::IPAddress>::iterator pos = addresses.begin();
        for (int i = 0; i < player_count; i++)
        {
            if (scores[*pos] > 400)
                gameOver = true;

            pos++;
        }
        sf::Sleep(0.1f);*/
    }
    cout << "Sending GG packet to all clients" << endl;
    sf::Packet ggPacket;
    ggPacket << "GG";
    set<sf::IPAddress>::iterator pos = addresses.begin();

    for (int i = 0; i < player_count; i++) //send game over message to all players
    {
        sf::IPAddress address = *pos;
        serverSocket.Send(ggPacket, address, local_port);
        cout << "Sent gg to " << address << endl;
        pos++;
    }

    serverSocket.SetBlocking(true);

    //Get information from all players
    sf::Packet infoPacket;
    vector<PlayerRepresentation> list;
    for (int i = 0; i < player_count; i++)
    {
        cout << "Processing player" << i+1 << endl;
        sf::IPAddress address = *pos;
        serverSocket.Receive(infoPacket, address, local_port);
        std::string name;
        int score;
        infoPacket >> name;
        infoPacket >> score;
        cout << "Got name and score : " << name << " " << score << endl;
        list.push_back(PlayerRepresentation(name, score));
        pos++;

        cout << "Got score info from player " << address << endl;
    }

    sort(list.begin(), list.end()); //sort the players
    reverse(list.begin(), list.end()); //descending order

    //send the name of winner to all clients
    sf::Packet winnersPacket;
    winnersPacket << list[0].name;

    pos = addresses.begin();
    for (int i = 0; i < player_count; i++)
    {
        sf::IPAddress address = *pos;
        serverSocket.Send(winnersPacket, address, local_port);
        pos++;
        cout << "Sent winner name to player" << address << endl;
    }

    serverSocket.Close(); //Close server socket
}
/*
void Server::getScores()
{
    set<sf::IPAddress>::iterator pos = addresses.begin();
    unsigned short local_port = SERVER_PORT; //needed since the socket methods don't accept constants
    for (int i = 0; i < player_count; i++)
    {
            sf::Packet scorePacket;
            sf::IPAddress address = *pos;
            if (serverSocket.Receive(scorePacket, address , local_port) == sf::Socket::Done)
            {
                string msg;
                scorePacket >> msg;
                cout << "Server received " << msg << endl;
                if (msg != "score")
                    return;
                int score;
                scorePacket >> score;   //get score from packet
                scores.erase(address); //remove old score
                scores.insert(pair<sf::IPAddress, int>(address, score));   //insert updated score
                cout << "Updated score for player " << address.ToString() << ". It is now " << score << endl;
                pos++;
            }
            else
            {
                continue;
                pos++;
            }

    }
}*/

#endif // NETWORK_H_INCLUDED

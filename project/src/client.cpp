#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <ctime>
#include <exception>
#include <messages.hpp>
#include <thread>

#include "client.h"
#include "client_server_config.h"

Client::Client(sf::IpAddress ip_address, int port)
    : m_ip_adress(ip_address), m_port(port) {}

Client::Client(std::string str_ip, int port) {
    Client(sf::IpAddress(str_ip), port);
}

bool Client::connectToServer()
{
    m_socket = std::make_shared<sf::TcpSocket>();


    if (m_socket->connect(m_ip_adress, m_port) == sf::Socket::Done)
    {
        std::cout << "connected!" << std::endl;
        m_socket->setBlocking(false);
        // sf::Packet packet;

        // while (m_socket->receive(packet) != sf::Socket::Done) { }
        // if (packet.getDataSize() > 0)
        // {
        //     packet >> new_player_msg;
        //     m_id = new_player_msg.player_id;

        //     std::cout << "My ID is " << m_id << std::endl;
        // }
        // else
        // {
        //     throw std::runtime_error("Can't get user ID\n");
        // }

    }
    else 
    {
        throw std::runtime_error("Can't connect to server\n");
    }

    return true;
}

Client::~Client()
{
    m_socket->disconnect();
    std::cout << "Client disconnected" << std::endl;
}

void Client::RunClient()
{
    std::this_thread::sleep_for(std::chrono::seconds(5));

    while (true) {
    }
}

bool Client::SendToServer(sf::Packet& packet)
{
    sf::Socket::Status status = sf::Socket::Done;
    do
    {
        if(status == sf::Socket::Partial)
        {
            std::cout << "SendToServer: Partial" << std::endl;
        }
        status = m_socket->send(packet);

    } while (status == sf::Socket::Partial);

    if (status == sf::Socket::Done)
        return true;

    else
        return false;
}

bool Client::RecieveFromServer(sf::Packet& packet)
{
    sf::Socket::Status status;// = sf::Socket::Done;

    while ((status = m_socket->receive(packet)) && (status != sf::Socket::Done)) { }

    // do
    // {
    //     if(status == sf::Socket::Partial)
    //     {
    //         std::cout << "RecieveFromServer: Partial" << std::endl;
    //     }

    //     status = m_socket->receive(packet);
    // } while (status == sf::Socket::Partial);

    if (status == sf::Socket::Done)
        return true;

    else
        return false;
}

// int main()
// {
// sf::IpAddress ip = sf::IpAddress::getLocalAddress();
// std::cout << "Current IP" << ip << std::endl;

// int MyID;

// sf::TcpSocket *socket = new sf::TcpSocket;
// sf::SocketSelector selector;
// sf::Packet packet;

// if(socket->connect(ip, 2003) == sf::Socket::Done)
// {
//     std::cout << "connected!" << std::endl;
//     socket->setBlocking(false);

//     while (socket->receive(packet) != sf::Socket::Done) {}
//     if(packet.getDataSize() > 0)
//     {
//         packet >> MyID;
//         std::cout << "My ID is " << MyID << std::endl;
//     }
//     else
//     {
//         std::cout << "Cant get my ID" << std::endl;
//         return -1;
//     }

//     selector.add(*socket);

// }
// else
// {
//     std::cout << "can not connect!" << std::endl;
//     return -1;
// }

// std::cout << "Now you may send data to server" << std::endl;
// while(true)
// {
//     //if(selector.isReady(*socket))
//     //{
//         if(socket->receive(packet) == sf::Socket::Done)
//         {
//             int other_ID;
//             std::string text;
//             packet >> other_ID >> text;
//             std::cout << "Message from user with ID " << other_ID << ": " <<
//             text << std::endl;
//         }
//         // else
//         // {
//         //     std::cout << "Can't recieve message!" << std::endl;
//         // }
//     //}

//     std::cout << "Enter text: ";
//     std::string text;
//     std::cin >> text;

//
// }

//     Client client(sf::IpAddress::getLocalAddress(), 2000);

//     client.RunClient();

//     return 0;
// }
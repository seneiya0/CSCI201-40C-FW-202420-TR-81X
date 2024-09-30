#include "PracticalSocket.h"
#include <iostream>
#include <limits>
#include <string>

void resetStream();
// see server.cpp for lecture activity

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./client <server host>" << std::endl;
        return 1;
    }

    try
    {
        std::cout << argv[1] << std::endl;
        TCPSocket sock(argv[1], 9431);
        // int input = 0;
        std::string message;
        std::cout << "Enter a message for the server: ";
        std::getline(std::cin >> std::ws, message);

        uint32_t val = htonl(message.length());

        sock.send(&val, sizeof(val));
        sock.send(message.c_str(), message.length());
        if (sock.recvFully(&val, sizeof(val)) == sizeof(val))
        {
            val = ntohl(val);
            char *buffer = new char[val + 1];
            if (sock.recvFully(buffer, val) == val)
            {
                buffer[val] = '\0';
                std::cout << "\033[1m\033[38;5;27m";
                std::cout << "Server Response: " << buffer << std::endl;
            }
            delete[] buffer;
        }
    }
    catch (SocketException e)
    {
        std::cerr << e.what() << '\n';
    }
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** client
*/

#include <asio.hpp>
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./client_test <ip> <port>" << std::endl;
        return 84;
    }

    asio::io_context io;
    asio::ip::udp::resolver resolver(io);

    try {

        asio::ip::udp::endpoint receiverEndpoint = *resolver.resolve(asio::ip::udp::endpoint(asio::ip::make_address(av[1]), std::stoi(av[2]))).begin();
        asio::ip::udp::socket socket(io);

        socket.open(asio::ip::udp::v4());

        std::array<char, 13> sendBuff = {{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'}};

        socket.send_to(asio::buffer(sendBuff), receiverEndpoint);

        std::array<char, 128> recvBuff = {{0}};
        asio::ip::udp::endpoint senderEndpoint;
        size_t len = socket.receive_from(asio::buffer(recvBuff), senderEndpoint);

        std::cerr << "Received: " << recvBuff.data() << std::endl;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

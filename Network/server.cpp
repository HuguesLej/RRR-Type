/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** main
*/

#include <array>
#include <asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

std::string make_daytime_string()
{
    std::time_t now = std::time(0);

    return std::ctime(&now);
}

int main(void)
{
    asio::io_context io;

    try {

        asio::ip::address ip_address = asio::ip::make_address("10.19.255.82");
        asio::ip::udp::endpoint endpoint(ip_address, 12345);
        asio::ip::udp::socket socket(io, endpoint);

        std::cerr << "Server is running on " << socket.local_endpoint().address().to_string() << ":" << socket.local_endpoint().port() << std::endl;

        while (true) {
            std::array<char, 128> recvBuff = {{0}};
            asio::ip::udp::endpoint remoteEndpoint;

            socket.receive_from(asio::buffer(recvBuff), remoteEndpoint);

            std::cerr << "Received: " << recvBuff.data() << std::endl;

            std::string msg = make_daytime_string();
            std::error_code ignoredError;

            socket.send_to(asio::buffer(msg), remoteEndpoint, 0, ignoredError);
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

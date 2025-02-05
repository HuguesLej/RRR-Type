/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** main
*/

#include <array>
#include <asio.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

std::string make_daytime_string()
{
    std::time_t now = std::time(0);

    return std::ctime(&now);
}

class UDPServer
{
    public:
        UDPServer(asio::io_context &io, std::string ip, uint16_t port)
            : _socket(io, asio::ip::udp::endpoint(asio::ip::make_address(ip), port))
        {
            startReceive();
        }

    private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        std::array<char, 128> _recvBuff = {{0}};

        void startReceive()
        {
            _socket.async_receive_from(
                asio::buffer(_recvBuff),
                _endpoint,
                std::bind(&UDPServer::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
        }

        void handleReceive(const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error) {
                std::cerr << "Received: " << _recvBuff.data() << std::endl;

                std::shared_ptr<std::string> msg(new std::string(make_daytime_string()));

                _socket.async_send_to(
                    asio::buffer(*msg),
                    _endpoint,
                    std::bind(&UDPServer::handleSend, this, msg, asio::placeholders::error, asio::placeholders::bytes_transferred)
                );

                startReceive();
            }
        }

        void handleSend(std::shared_ptr<std::string>, const std::error_code &, std::size_t)
        {
        }
};

int main(void)
{
    asio::io_context io;

    try {

        // UDPServer server(io, "10.19.255.82", 12345);
        UDPServer server(io, "192.168.1.17", 12345);

        std::cerr << "Server is running on " << "10.19.255.82" << ":" << 12345 << std::endl;

        io.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

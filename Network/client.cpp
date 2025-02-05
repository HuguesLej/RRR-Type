/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** client
*/

#include <asio.hpp>
#include <iostream>
#include <istream>

class UDPClient
{
    public:
        UDPClient(asio::io_context &io, std::string ip, uint16_t port)
            : _socket(io), _endpoint(asio::ip::make_address(ip), port)
        {
            _socket.open(asio::ip::udp::v4());
            startSending();
            _uniqueId = std::rand() % 10;
        }

    private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        std::array<char, 128> _recvBuff = {{0}};
        uint8_t _uniqueId;

        void startSending()
        {
            // std::string msg = "Hello from client " + std::to_string(_uniqueId);
            std::string msg;

            while (msg.empty()) {
                std::getline(std::cin, msg);
            }

            _socket.async_send_to(
                asio::buffer(msg),
                _endpoint,
                std::bind(&UDPClient::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
        }

        void handleSend(const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error) {
                _socket.async_receive_from(
                    asio::buffer(_recvBuff),
                    _endpoint,
                    std::bind(&UDPClient::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
                );
            }
        }

        void handleReceive(const std::error_code &error, std::size_t)
        {
            if (!error) {
                std::cerr << "Received: " << _recvBuff.data() << std::endl;
                _recvBuff.fill(0);
                startSending();
            }
        }
};


int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./client_test <ip> <port>" << std::endl;
        return 84;
    }

    asio::io_context io;

    try {

        UDPClient client(io, av[1], std::stoi(av[2]));

        io.run();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

/*
** EPITECH PROJECT, 2025
** RRR-Type
** File description:
** client
*/

#include <asio.hpp>
#include <ctime>
#include <iostream>
#include <istream>

class UDPClient
{
    public:
        UDPClient(asio::io_context &io, std::string ip, uint16_t port)
            : _socket(io), _endpoint(asio::ip::make_address(ip), port), _timer(io, asio::chrono::seconds(0)),
            _recvStrand(asio::make_strand(io)), _sendStrand(asio::make_strand(io))
        {
            std::srand(std::time(0));
            _uniqueId = std::rand() % 10;

            _socket.open(asio::ip::udp::v4());

            startReceive();
            startTimer();
        }

    private:
        uint8_t _uniqueId;

        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        std::array<char, 128> _recvBuff = {{0}};

        asio::steady_timer _timer;

        asio::strand<asio::io_context::executor_type> _recvStrand;
        asio::strand<asio::io_context::executor_type> _sendStrand;

        void startReceive()
        {
            _socket.async_receive_from(
                asio::buffer(_recvBuff),
                _endpoint,
                asio::bind_executor(
                    _recvStrand,
                    std::bind(&UDPClient::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
                )
            );
        }

        void handleReceive(const std::error_code &error, std::size_t)
        {
            if (!error) {
                std::cerr << "Received: " << _recvBuff.data() << std::endl;
                _recvBuff.fill(0);

                startReceive();
            }
        }

        void startTimer()
        {
            _timer.expires_after(asio::chrono::seconds(5));
            _timer.async_wait(
                asio::bind_executor(
                    _sendStrand,
                    std::bind(&UDPClient::startSend, this)
                )
            );
        }

        void startSend()
        {
            std::shared_ptr<std::string> msg(new std::string("Hello from client " + std::to_string(_uniqueId)));

            _socket.async_send_to(
                asio::buffer(*msg),
                _endpoint,
                asio::bind_executor(
                    _sendStrand,
                    std::bind(&UDPClient::handleSend, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
                )
            );

            startTimer();
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

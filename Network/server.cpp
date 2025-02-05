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
#include <thread>
#include <unordered_set>

std::string make_daytime_string()
{
    std::time_t now = std::time(0);

    return std::ctime(&now);
}

class UDPServer
{
    public:
        UDPServer(asio::io_context &io, std::string ip, uint16_t port)
            : _socket(io, asio::ip::udp::endpoint(asio::ip::make_address(ip), port)), _timer(io, asio::chrono::seconds(0)),
            _recvStrand(asio::make_strand(io)), _sendStrand(asio::make_strand(io))
        {
            std::cerr << "Server is running on " << ip << ":" << std::to_string(port) << std::endl;

            startReceive();
            startTimer();
        }

    private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;
        std::array<char, 128> _recvBuff = {{0}};

        std::unordered_set<asio::ip::udp::endpoint> _clients;

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
                    std::bind(&UDPServer::handleReceive, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
                )
            );
        }

        void handleReceive(const std::error_code &error, std::size_t bytes_transferred)
        {
            if (!error) {
                std::cerr << "Received: " << _recvBuff.data() << std::endl;
                _recvBuff.fill(0);

                _clients.insert(_endpoint);

                startReceive();
            }
        }

        void startTimer()
        {
            _timer.expires_after(asio::chrono::seconds(5));
            _timer.async_wait(
                asio::bind_executor(
                    _sendStrand,
                    std::bind(&UDPServer::startSend, this)
                )
            );
        }

        void startSend()
        {
            std::shared_ptr<std::string> msg(new std::string(make_daytime_string()));

            for (const auto &client : _clients) {
                _socket.async_send_to(
                    asio::buffer(*msg),
                    client,
                    asio::bind_executor(
                        _sendStrand,
                        std::bind(&UDPServer::handleSend, this, msg, asio::placeholders::error, asio::placeholders::bytes_transferred)
                    )
                );
            }

            startTimer();
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
        std::vector<std::thread> workers;
        size_t maxThreads = std::thread::hardware_concurrency();

        if (maxThreads > 4) {
            maxThreads = 4;
        }

        for (size_t i = 0; i < maxThreads; i++) {
            workers.emplace_back([&io] {
                io.run();
            });
        }

        for (auto &w : workers) {
            w.join();
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

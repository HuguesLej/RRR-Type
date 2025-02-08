/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** ACommunication
*/

#ifndef ACOMMUNICATION_HPP_
    #define ACOMMUNICATION_HPP_

    #include <asio.hpp>
    #include <any>
    #include <optional>
    #include <thread>
    #include <vector>

    #include "SerializerManager.hpp"

class ACommunication
{
    public:
        ACommunication(asio::io_context &io, std::string ip, uint16_t port);
        virtual ~ACommunication() = default;

        std::optional<std::any> getRecvData();

        virtual bool isServer() = 0;

        virtual void startSend(const std::any &data) = 0;

    protected:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;

        std::vector<uint8_t> _recvBuff;
        std::vector<std::vector<uint8_t>> _recvPackets;

        asio::strand<asio::io_context::executor_type> _recvStrand;
        asio::strand<asio::io_context::executor_type> _sendStrand;

        std::vector<std::thread> _workers;

    private:
        virtual void handleSend(const std::error_code &error, std::size_t) = 0;

        virtual void startReceive() = 0;
        virtual void handleReceive(const std::error_code &error, std::size_t) = 0;
};

#endif /* !ACOMMUNICATION_HPP_ */

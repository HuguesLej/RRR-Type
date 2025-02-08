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
    #include <iostream>
    #include <optional>
    #include <thread>
    #include <vector>

    #include "SerializerManager.hpp"

class ACommunication
{
    public:
        ACommunication(asio::io_context &io);
        virtual ~ACommunication() = default;

        void setSendData(const std::any &data);

        std::optional<std::any> getRecvData();

        virtual bool isServer() = 0;

    protected:
        asio::strand<asio::io_context::executor_type> _recvStrand;
        asio::strand<asio::io_context::executor_type> _sendStrand;

        asio::steady_timer _timer;

        std::vector<uint8_t> _sendBuff;

        std::string _recvStr;
        std::vector<uint8_t> _recvBuff;
        std::vector<std::vector<uint8_t>> _recvPackets;

        std::vector<std::thread> _workers;

    private:
        virtual void startSend() = 0;
        virtual void sendData() = 0;
        virtual void handleSend(const std::error_code &error, std::size_t) = 0;

        virtual void startReceive() = 0;
        virtual void handleReceive(const std::error_code &error, std::size_t) = 0;
};

#endif /* !ACOMMUNICATION_HPP_ */

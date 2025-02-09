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
    #include <exception>
    #include <iostream>
    #include <mutex>
    #include <optional>
    #include <thread>
    #include <unordered_map>
    #include <vector>

    #include "SerializerManager.hpp"

class ACommunication
{
    public:

        class Error : public std::exception
        {
            public:
                enum class OriginType
                {
                    Server = 0,
                    Client = 1
                };

                Error(OriginType origin);
                ~Error() = default;

                const char *what() const noexcept override;

            private:
                std::string _msg;
        };

        ACommunication(asio::io_context &io);
        virtual ~ACommunication() = default;

        void setSendData(const std::any &data);

        std::optional<std::any> getRecvData();

        virtual bool isServer() = 0;

        virtual std::vector<std::pair<asio::ip::udp::endpoint, bool>> &getClients() = 0;

        virtual std::pair<std::string, uint16_t> getLocalAddressAndPort() = 0;

    protected:
        asio::io_context &_io;

        asio::strand<asio::io_context::executor_type> _recvStrand;
        asio::strand<asio::io_context::executor_type> _sendStrand;

        asio::steady_timer _timer;

        std::mutex _sendMutex;
        std::vector<std::vector<uint8_t>> _sendPackets;

        std::mutex _recvMutex;
        std::vector<std::vector<uint8_t>> _recvPackets;

        std::vector<std::thread> _workers;
        std::atomic<bool> _stop = false;

    private:
        virtual void startSend() = 0;
        virtual void sendData() = 0;
        virtual void handleSend(const std::error_code &error, std::size_t, std::shared_ptr<std::atomic<size_t>>) = 0;

        virtual void startReceive() = 0;
        virtual void handleReceive(std::shared_ptr<std::string> &data, const std::error_code &error, std::size_t) = 0;
};

#endif /* !ACOMMUNICATION_HPP_ */

/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPServerCommunication
*/

#ifndef UDP_SERVER_COMMUNICATION_HPP_
    #define UDP_SERVER_COMMUNICATION_HPP_

    #include <unordered_map>

    #include "ACommunication.hpp"

class UDPServerCommunication : public ACommunication
{
    public:
        UDPServerCommunication(asio::io_context &io, std::string ip, uint16_t port);
        ~UDPServerCommunication();

        bool isServer() override;

        std::unordered_map<asio::ip::udp::endpoint, bool> &getClients();

    private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;

        std::unordered_map<asio::ip::udp::endpoint, bool> _clients;

        void startSend() override;
        void sendData() override;
        void handleSend(const std::error_code &error, std::size_t, std::shared_ptr<std::atomic<size_t>> clientsCount) override;

        void startReceive() override;
        void handleReceive(std::shared_ptr<std::string> &data, const std::error_code &error, std::size_t) override;
};

#endif /* !UDP_SERVER_COMMUNICATION_HPP_ */

/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPServerCommunication
*/

#ifndef UDP_SERVER_COMMUNICATION_HPP_
    #define UDP_SERVER_COMMUNICATION_HPP_

    #include <iostream>
    #include <unordered_set>

    #include "ACommunication.hpp"

class UDPServerCommunication : public ACommunication
{
    public:
        UDPServerCommunication(asio::io_context &io, std::string ip, uint16_t port);
        ~UDPServerCommunication();

        bool isServer() override;

    private:
        std::unordered_set<asio::ip::udp::endpoint> _clients;

        void startReceive() override;
        void handleReceive(const std::error_code &error, std::size_t) override;
        void startSend(const std::any &data) override;
        void handleSend(const std::error_code &error, std::size_t) override;
};

#endif /* !UDP_SERVER_COMMUNICATION_HPP_ */

/*
** EPITECH PROJECT, 2025
** RRR-Type [WSL: Ubuntu]
** File description:
** UDPClientCommunication
*/

#ifndef UDP_CLIENT_COMMUNICATION_HPP_
    #define UDP_CLIENT_COMMUNICATION_HPP_

    #include "ACommunication.hpp"

class UDPClientCommunication : public ACommunication
{
    public:
        UDPClientCommunication(asio::io_context &io, std::string ip, uint16_t port);
        ~UDPClientCommunication();

        bool isServer() override;

        std::vector<std::pair<asio::ip::udp::endpoint, bool>> &getClients() override;

        std::pair<std::string, uint16_t> getLocalAddressAndPort() override;

    private:
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _endpoint;

        void startSend() override;
        void sendData() override;
        void handleSend(const std::error_code &error, std::size_t, std::shared_ptr<std::atomic<size_t>>) override;

        void startReceive() override;
        void handleReceive(std::shared_ptr<std::string> &data, const std::error_code &error, std::size_t) override;
};

#endif /* !UDP_CLIENT_COMMUNICATION_HPP_ */

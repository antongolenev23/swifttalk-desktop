#pragma once
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include "client_session.hpp"
#include "message.hpp"

namespace echo_desktop {

class Client {
public:
    Client(const std::string& host, uint32_t port);

    void connect();
    void disconnect();
    void send_message(const Message& msg);
    void receive_message();

private:
    std::string host_;
    uint32_t port_;
    boost::asio::io_context io_;
    std::unique_ptr<ClientSession> session_;
};

} // namespace echo_desktop

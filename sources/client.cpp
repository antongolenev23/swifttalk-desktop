#include "client.hpp"
#include "connection.hpp"
#include "client_session.hpp"
#include <boost/asio.hpp>
#include <iostream>

namespace echo_desktop {

using boost::asio::ip::tcp;

Client::Client(const std::string& host, uint32_t port)
    : host_(host), port_(port) {}

void Client::connect() {
    tcp::resolver resolver(io_);
    auto endpoints = resolver.resolve(host_, std::to_string(port_));
    tcp::socket socket(io_);
    boost::asio::connect(socket, endpoints);

    std::cout << "Connected to server " << host_ << ":" << port_ << "\n";

    auto conn = std::make_unique<Connection>(std::move(socket));
    session_ = std::make_unique<ClientSession>(std::move(conn));
    session_->start();
}

void Client::disconnect() {
    if (session_) {
        session_->stop();
        std::cout << "Disconnected from server\n";
    }
}

void Client::send_message(const Message& msg) {
    session_->send_message(msg);
}

void Client::receive_message() {
    session_->receive_message();
}

} // namespace echo_desktop

#pragma once 
#include <memory>
#include <string>
#include <iostream>
#include "connection.hpp"
#include "message.hpp"

namespace echo_desktop {

class ClientSession {
public:
    explicit ClientSession(std::unique_ptr<Connection> conn);

    void start();
    void stop();
    void receive_message();
    void send_message(const Message&);

private:
    std::unique_ptr<Connection> conn_;
};


} // namespace echo_desktop
#pragma once
#include <boost/asio.hpp>
#include <string>

namespace echo_desktop {

class Connection {
public:
    explicit Connection(boost::asio::ip::tcp::socket socket);
    ~Connection();

    std::string read();
    void write(const std::string& data);
    void close();

private:
    boost::asio::ip::tcp::socket socket_;
    bool closed_;
};

} // namespace echo_desktop

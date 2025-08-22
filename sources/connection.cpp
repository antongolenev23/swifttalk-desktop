#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include "connection.hpp"
#include "message.hpp"

namespace echo_desktop {

Connection::Connection(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)), closed_(false) {}

Connection::~Connection() {
    close();
}

// Чтение одной строки до '\n'
std::string Connection::read() {
    boost::asio::streambuf buf;
    boost::system::error_code ec;

    // Читаем до символа конца строки
    size_t len = boost::asio::read_until(socket_, buf, '\n', ec);
    if (ec) {
        throw std::runtime_error("Read error: " + ec.message());
    }

    std::istream is(&buf);
    std::string line;
    std::getline(is, line);
    return line;
}

// Запись строки с добавлением '\n'
void Connection::write(const std::string& data) {
    std::string msg = data + "\n"; // добавляем разделитель
    boost::system::error_code ec;
    boost::asio::write(socket_, boost::asio::buffer(msg), ec);
    if (ec) {
        throw std::runtime_error("Write error: " + ec.message());
    }
}

void Connection::close() {
    if (!closed_) {
        boost::system::error_code ec; 
        socket_.close(ec);
        if (ec) {
            std::cerr << "Error closing socket: " << ec.message() << "\n";
        }
        closed_ = true;
    }
}


} // namespace echo_desktop

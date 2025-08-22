#include "client_session.hpp"
#include <iostream>

namespace echo_desktop {

ClientSession::ClientSession(std::unique_ptr<Connection> conn)
    : conn_(std::move(conn)) {}

void ClientSession::start() {
    std::cout << "Session started\n";

    // Цикл: читаем ввод пользователя -> отправляем -> читаем ответ
    try {
        while (true) {
            std::string input;
            std::cout << "You: ";
            if (!std::getline(std::cin, input) || input == "/quit") {
                break; // пользователь вышел
            }

            send_message(Message(input));   // отправляем
            std::string reply = conn_->read(); // ждём ответ
            std::cout << "Server: " << reply << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Disconnected: " << e.what() << "\n";
    }
}

void ClientSession::stop() {
    std::cout << "Session stopped\n";
    conn_->close();
}

void ClientSession::receive_message() {
    try {
        std::string data = conn_->read();
        std::cout << "Received from server: " << data << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Handle incoming error: " << e.what() << "\n";
        stop();
    }
}

void ClientSession::send_message(const Message& msg) {
    conn_->write(msg.text() + "\n");
}

} // namespace echo_desktop

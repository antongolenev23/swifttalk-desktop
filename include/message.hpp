#pragma once
#include <string>
#include <chrono>

namespace echo_desktop {

class Message {
public:
    explicit Message(std::string text)
        : text_(std::move(text))
        , timestamp_(std::chrono::system_clock::now()) 
    {}

    std::string text() const noexcept { 
        return text_; 
    }
    std::chrono::system_clock::time_point get_timestamp() const noexcept {
        return timestamp_;
    }

private:
    std::string text_;
    std::chrono::system_clock::time_point timestamp_;
};

} // namespace echo_desktop

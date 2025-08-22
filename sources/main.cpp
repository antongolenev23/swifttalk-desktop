#include "client.hpp"

int main() {
    echo_desktop::Client client{"localhost", 8080};
    client.connect();
    client.disconnect();
}
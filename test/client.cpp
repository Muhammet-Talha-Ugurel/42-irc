#include "client.hpp"

Client::Client(int socket) : socket(socket) {}

int Client::get_socket() const {
    return socket;
}

void Client::set_nickname(const std::string& nickname) {
    this->nickname = nickname;
}

std::string Client::get_nickname() const {
    return nickname;
}

void Client::set_username(const std::string& username) {
    this->username = username;
}

void Client::set_hostname(const std::string& hostname) {
    this->hostname = hostname;
}

void Client::set_servername(const std::string& servername) {
    this->servername = servername;
}

void Client::set_realname(const std::string& realname) {
    this->realname = realname;
}

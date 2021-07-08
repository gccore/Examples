#include "demo_echo_web_socket.h"

namespace demo {
void echo_web_socket::handleNewMessage(drogon::WebSocketConnectionPtr const& connection,
                                       std::string&& message,
                                       drogon::WebSocketMessageType const& type) {
  LOG_DEBUG << "Type: " << static_cast<int>(type) << ".";
  connection->send(message);
}

void echo_web_socket::handleNewConnection(drogon::HttpRequestPtr const& request,
                                          drogon::WebSocketConnectionPtr const& connection) {
  //write your application logic here
}

void echo_web_socket::handleConnectionClosed(drogon::WebSocketConnectionPtr const& connection) {
  //write your application logic here
}
} // namespace demo

#pragma once

#include <drogon/WebSocketController.h>

namespace demo {
class echo_web_socket: public drogon::WebSocketController<echo_web_socket> {
 public:
  virtual void handleNewMessage(drogon::WebSocketConnectionPtr const& connection,
                                std::string&& message, drogon::WebSocketMessageType const& type) override;
  virtual void handleNewConnection(drogon::HttpRequestPtr const& request,
                                   drogon::WebSocketConnectionPtr const& connection) override;
  virtual void handleConnectionClosed(drogon::WebSocketConnectionPtr const& connection) override;

  WS_PATH_LIST_BEGIN
  WS_PATH_ADD("/echo");
  WS_PATH_LIST_END
};
} // namespace demo

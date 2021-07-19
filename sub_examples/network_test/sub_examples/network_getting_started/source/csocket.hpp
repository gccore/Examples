#pragma once

#include <exception>
#include <string>
#include <thread>
#include <atomic>

extern "C" {
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>
}

#include "global.hpp"
#include "constant.h"

namespace core {
struct exception final: std::exception {
  std::string message;
  exception(std::string const& message_)
    : message(message_) {
  }
  const char* what() const noexcept override {
    return message.c_str();
  }
};
} // namespace core

namespace core {
struct client_request final {
  sockaddr_in name = {0, 0, 0, 0};
  int client = 0;
  socklen_t length = sizeof(name);
  std::string echo_message;

  void check_request(int const socket_descriptor) {
    client = ::accept(socket_descriptor, reinterpret_cast<sockaddr*>(&name), &length);
    if (constant::socket::error == client) {
      throw core::exception("accept() return value: -1");
    } else {
      //      ::write(socket_descriptor, echo_message.c_str(), echo_message.size());
    }
  }
};

class socket final {
 private:
  int m_descriptor;
  sockaddr_in m_socketaddr;
  std::uint16_t m_port;
  std::thread m_thread;
  std::atomic_bool m_run_loop;
  std::string m_echo_message;

 private:
  bool is_failed() const noexcept {
    return constant::socket::error == m_descriptor;
  }

  void init_server() noexcept {
    m_socketaddr.sin_family = AF_INET;
    m_socketaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    m_socketaddr.sin_port = ::htons(m_port);
  }

  void set_port(std::uint16_t const port) {
    m_port = port;
  }

  void start_loop() {
    while (m_run_loop) {
      client_request request;
      request.echo_message = echo_message();
      request.check_request(m_descriptor);
    }
  }

 public:
  enum class mode {
    blocking,
    detach
  };
  enum class state {
    stopping,
    running
  };

 public:
  socket(int const domain = constant::socket::domain,
         int const type = constant::socket::type,
         int const protocol = constant::socket::protocol)
    : m_descriptor(::socket(domain, type, protocol)),
      m_run_loop(true) {
    if (is_failed()) {
      throw core::exception("socket() return value: -1");
    }
  }
  ~socket() {
  }

 public:
  socket& bind(std::uint16_t const port = core::config::port) {
    set_port(port);
    init_server();

    auto const result = ::bind(m_descriptor,
                               reinterpret_cast<sockaddr*>(&m_socketaddr),
                               sizeof(m_socketaddr));
    if (constant::socket::bind_success != result) {
      throw core::exception("bind() failed.");
    }

    return *this;
  }

  socket& listen() {
    auto const result = ::listen(m_descriptor, config::backlog);
    if (constant::socket::error == result) {
      throw core::exception("listen() return value: -1");
    }

    return *this;
  }

  socket& run(mode const m = mode::blocking) {
    switch (m) {
      case mode::blocking:
        start_loop();
        break;
      case mode::detach:
        m_thread = std::thread(&socket::start_loop, this);
        break;
    }

    return *this;
  }

  state loop_state() const {
    return m_run_loop ? state::running : state::stopping;
  }
  void set_loop_state(state const s) {
    m_run_loop = s == state::running ? true : false;
  }

  void block() {
    if (m_thread.joinable()) {
      m_thread.join();
    }
  }

  std::string const& echo_message() const {
    return m_echo_message;
  }
  std::string& echo_message() {
    return m_echo_message;
  }
};
} // namespace core

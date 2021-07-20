#pragma once

#include <exception>
#include <string>
#include <thread>
#include <atomic>

extern "C" {
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
}

#include "exception.hpp"
#include "constant.h"
#include "global.hpp"

namespace core {
struct client_request final {
  sockaddr_in name = {0, 0, 0, 0};
  int client = 0;
  socklen_t length = sizeof(name);
  std::string echo_message;

  ~client_request() {
    ::close(client);
  }

  void check_request(int const socket_descriptor) {
    client = ::accept(socket_descriptor, reinterpret_cast<sockaddr*>(&name), &length);
    if (constant::socket::error == client) {
      throw core::exception("accept() return value: -1");
    } else {
      ::write(client, echo_message.c_str(), echo_message.size());
    }
  }
};

class socket final {
 private:
  bool is_failed() const noexcept {
    return constant::socket::error == m_descriptor;
  }

  void init_common_socketaddr() noexcept {
    ::bzero(&m_socketaddr, sizeof(m_socketaddr));
    m_socketaddr.sin_family = AF_INET;
    m_socketaddr.sin_port = ::htons(m_port);
  }

  void init_server() noexcept {
    init_common_socketaddr();
    m_socketaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
  }

  void init_client() noexcept {
    init_common_socketaddr();
    m_socketaddr.sin_addr.s_addr = ::inet_addr(m_ip.c_str());
  }

  void set_port(std::uint16_t const port) noexcept {
    m_port = port;
  }

  void set_ip(std::string const& ip) noexcept {
    m_ip = ip;
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
  enum class socket_type {
    server,
    client
  };

 public:
  socket(socket_type const t,
         int const domain = constant::socket::domain,
         int const type = constant::socket::type,
         int const protocol = constant::socket::protocol)
    : m_descriptor(::socket(domain, type, protocol)),
      m_run_loop(t == socket_type::server),
      m_socket_type(t) {
    if (is_failed()) {
      throw core::exception("socket() return value: -1");
    }
  }
  socket()
    : socket(socket_type::server) {

  }
  ~socket() {
    ::close(m_descriptor);
  }

 public:
  socket& bind(std::uint16_t const port = core::config::port) {
    set_port(port);
    init_server();

    auto const result = ::bind(m_descriptor,
                               reinterpret_cast<sockaddr*>(&m_socketaddr),
                               sizeof(m_socketaddr));
    if (constant::socket::bind_success != result) {
      throw core::exception("bind() failed: " + std::string(strerror(errno)));
    }

    return *this;
  }

  socket& connect(std::string const& ip = core::config::ip,
                  std::uint16_t const port = core::config::port) {
    set_port(port);
    set_ip(ip);
    init_client();

    auto const result = ::connect(m_descriptor,
                                  reinterpret_cast<sockaddr*>(&m_socketaddr),
                                  sizeof(m_socketaddr));
    if (constant::socket::error == result) {
      throw core::exception("connect() failed: " + std::string(strerror(errno)));
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

  socket& read(std::size_t const length) {
    m_buffer.resize(length, constant::string::nul);
    auto const result = ::read(m_descriptor, m_buffer.data(), length);
    if (constant::socket::error == result) {
      throw core::exception("read() failed: " + std::to_string(result));
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
  std::string const& buffer() const {
    return m_buffer;
  }

 private:
  int m_descriptor;
  sockaddr_in m_socketaddr;
  std::uint16_t m_port;
  std::string m_ip;
  std::thread m_thread;
  std::atomic_bool m_run_loop;
  std::string m_echo_message;
  socket_type m_socket_type;
  std::string m_buffer;
};
} // namespace core

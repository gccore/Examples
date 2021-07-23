#pragma once

#include <exception>
#include <string>
#include <memory>
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
class socket;

struct client_request final {
  sockaddr_in name = {0, 0, 0, 0};
  std::unique_ptr<socket> client;
  socklen_t length = sizeof(name);
  std::string echo_message;

  ~client_request();

  void check_request(socket const& socket_descriptor);
};

class socket final {
 public:
  enum class state {
    stopping,
    running
  };
  enum class type {
    server,
    client
  };
  enum class option {
    reuse_address
  };

 public:
  operator int() const noexcept {
    return m_descriptor;
  }

 public:
  socket(type const t,
         int const domain = constant::socket::domain,
         int const type = constant::socket::type,
         int const protocol = constant::socket::protocol)
    : m_descriptor(::socket(domain, type, protocol)),
      m_run_loop(t == type::server),
      m_socket_type(t) {
    if (is_failed()) {
      throw core::exception("socket() return value: -1");
    }
  }
  socket() = default;
  socket(socket const& parent,
         sockaddr_in name,
         socklen_t length)
    : m_descriptor(::accept(parent,
                            reinterpret_cast<sockaddr*>(&name), &length)),
      m_run_loop(false), m_socket_type(type::client) {
    if (is_failed()) {
      throw core::exception("accept() failed: " + std::string(strerror(errno)));
    }
  }
  ~socket() {
    ::close(m_descriptor);
  }

 public:
  bool operator==(int const other) {
    return other == m_descriptor;
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

  socket& run() {
    start_loop();
    return *this;
  }

  socket& read(std::size_t const length) {
    m_buffer.resize(length, constant::string::nul);
    auto const result = ::read(m_descriptor, m_buffer.data(), length);
    if (constant::socket::error == result) {
      throw core::exception("read() failed: " + std::string(strerror(errno)));
    }

    return *this;
  }

  socket& send(std::string const& data,
               int const flags = constant::socket::empty) {
    auto const ret_value = ::send(m_descriptor, data.data(), data.size(), flags);
    if (ret_value != static_cast<int>(data.size())) {
      throw core::exception("read() failed: " + std::string(strerror(errno)));
    }
    return *this;
  }

  socket& send(int const flags = constant::socket::empty) {
    return send(m_buffer, flags);
  }

  socket& set_option(int const level, int const option_name,
                     void* const option_value, socklen_t const length) {
    auto const ret_value = ::setsockopt(m_descriptor,
                                        level, option_name,
                                        option_value, length);
    if (constant::socket::error == ret_value) {
      throw core::exception("setsockopt() failed: " + std::string(strerror(errno)));
    }
    return *this;
  }

  socket& set_option(option const ope) {
    int value = 1;
    return set_option(SOL_SOCKET, create_opetion(ope), &value, sizeof(value));
  }

  std::string receive(std::size_t const length,
                      int const flags = constant::socket::empty) {
    std::string result;
    result.resize(length, constant::string::nul);
    auto const ret_value = ::recv(m_descriptor, result.data(), length, flags);
    if (constant::socket::error == ret_value) {
      throw core::exception("recv() failed: " + std::string(strerror(errno)));
    }
    return result;
  }

  socket& delay(std::size_t const second) noexcept {
    std::this_thread::sleep_for(std::chrono::seconds(second));
    return *this;
  }

  state loop_state() const {
    return m_run_loop ? state::running : state::stopping;
  }
  void set_loop_state(state const s) {
    m_run_loop = s == state::running ? true : false;
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
  std::string& buffer() {
    return m_buffer;
  }

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
      request.check_request(*this);
    }
  }

  int create_opetion(option const ope) {
    int result = -1;
    switch (ope) {
      case option::reuse_address:
        result = SO_REUSEADDR;
        break;
    }
    return result;
  }

 private:
  int m_descriptor;
  sockaddr_in m_socketaddr;
  std::uint16_t m_port;
  std::string m_ip;
  std::atomic_bool m_run_loop;
  std::string m_echo_message;
  type m_socket_type;
  std::string m_buffer;
};

inline client_request::~client_request() {
  ::close(*client);
}

inline void client_request::check_request(socket const& socket_descriptor) {
  client = std::make_unique<core::socket>(socket_descriptor, name, length);
  std::cout << "[S] Received value: \"" << client->receive(25) << "\"" << std::endl;
  client->send(std::to_string(*client) + " : It's Okay");
}
} // namespace core

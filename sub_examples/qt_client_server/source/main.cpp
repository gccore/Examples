/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

#include <QApplication>
#include <QHostAddress>
#include <QHBoxLayout>
#include <QStringList>
#include <QDataStream>
#include <QByteArray>
#include <QUdpSocket>
#include <QTextEdit>
#include <QDialog>

namespace core {
constexpr auto port = 64353;
constexpr auto host = QHostAddress::LocalHost;
constexpr auto max_len = 512;

struct base_widget: QDialog {
  QTextEdit* m_logs;
  QUdpSocket* m_socket;
  base_widget() noexcept :
    m_logs(new QTextEdit), m_socket(new QUdpSocket(this)) {
    (new QHBoxLayout(this))->addWidget(m_logs);
    setup_client();
  }
  void setup_client() const noexcept {
    connect(m_socket, &QUdpSocket::errorOccurred, this, qOverload<QAbstractSocket::SocketError>(&base_widget::log));
    connect(m_socket, &QUdpSocket::stateChanged, this, qOverload<QAbstractSocket::SocketState>(&base_widget::log));
  }
  void log(QAbstractSocket::SocketError const e) noexcept {
    m_logs->append("<p style=\"color:red;\">" + QString::number(static_cast<int>(e)) + "</p>");
  }
  void log(QAbstractSocket::SocketState const s) noexcept {
    m_logs->append("<p style=\"color:green;\">" + QString::number(static_cast<int>(s)) + "</p>");
  }
};
} // namespace core

namespace clinet {
struct widget final: core::base_widget {
  widget() noexcept {
    setWindowTitle("client");
    setup_client();
  }
  void setup_client() const noexcept {
    m_socket->connectToHost(core::host, core::port, QIODevice::ReadWrite);
    m_socket->waitForConnected();
  }

  void send(QStringList const& data) noexcept {
    QByteArray socket_data;
    QDataStream serializer(&socket_data, QIODevice::WriteOnly);
    serializer << data;
    m_socket->write(socket_data);
  }
};
} // namespace client

namespace server {
struct widget final: core::base_widget {
  widget() noexcept {
    setWindowTitle("server");
    setup_server();
  }
  void setup_server() const noexcept {
    connect(m_socket, &QUdpSocket::readyRead, this, &widget::new_connection);
    m_socket->bind(core::host, core::port);
  }
  void new_connection() noexcept {
    QByteArray diagram;
    diagram.resize(core::max_len);
    m_socket->readDatagram(diagram.data(), core::max_len);

    QDataStream deserializer(&diagram, QIODevice::ReadOnly);
    QStringList data;
    deserializer >> data;

    for (auto const& i : data) {
      m_logs->append(i);
    }
  }
};
} // namespace client

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  clinet::widget c;
  server::widget s;

  c.send({"F1", "F2", "F3", "\n"});

  c.show(), s.show();
  return application.exec();
}

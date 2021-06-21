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

#include <QByteArray>
#include <QUdpSocket>
#include <QDebug>

#include <thread>

std::pair<bool, QString> sendMagicPacket(QString const& ip, QString const& mac) {
  std::pair<bool, QString> result = { true, "" };
  ///
  /// \note Constants from https://en.wikipedia.org/wiki/Wake-on-LAN#Magic_packet
  ///
  constexpr auto magicPacketLength = 102;
  constexpr auto payloadLength = 6;
  constexpr auto payloadValue = static_cast<char>(0xFF);
  constexpr auto defaultPort = 0;
  char toSend[magicPacketLength];

  for (int i = 0; i < payloadLength; ++i) {
    toSend[i] = payloadValue;
  }

  auto const macSplited = mac.split(':');
  auto const macLength = macSplited.size();

  for (int j = payloadLength; j < magicPacketLength; j += macLength) {
    for (int i = 0; i < macLength; ++i) {
      toSend[i + j] = static_cast<char>(macSplited[i].toUInt(nullptr, 16));
    }
  }

  QUdpSocket socket;
  auto const writtenSize = socket.writeDatagram(toSend, magicPacketLength,
                                                QHostAddress(ip), defaultPort);

  if (writtenSize != magicPacketLength) {
    result = { false, "writtenSize(" + QString::number(writtenSize)
               + ") != magicPacketLength(" + QString::number(magicPacketLength) + "): "
               + socket.errorString()
             };
  }

  return result;
}

int main() {
  std::thread([] {
    for (int i = 0; i < 5; ++i) {
      auto const result = sendMagicPacket("192.168.11.31", "1c:1c:1e:1f:19:15");
      if (not result.first) {
        qDebug() << result.second;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }).join();
}

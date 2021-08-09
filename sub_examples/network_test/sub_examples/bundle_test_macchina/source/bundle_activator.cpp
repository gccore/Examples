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

#include <Poco/OSP/BundleActivator.h>
#include <Poco/OSP/BundleContext.h>
#include <Poco/ClassLibrary.h>


namespace macchina_test {
class bundle_test: public Poco::OSP::BundleActivator {
 public:
  void start(Poco::OSP::BundleContext::Ptr pContext) {
    pContext->logger().information("Hello, world!");
  }

  void stop(Poco::OSP::BundleContext::Ptr pContext) {
    pContext->logger().information("Goodbye!");
  }
};
} // namespace macchina_test


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
POCO_EXPORT_CLASS(macchina_test::bundle_test)
POCO_END_MANIFEST

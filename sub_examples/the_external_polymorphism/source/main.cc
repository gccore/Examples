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
 * @gccore
 * g1999ramezani@gmail.com
 */

#include <iostream>
#include <memory>
#include <vector>

class Print {
 public:
  template <typename PrintType>
  Print(PrintType object)
      : pimpl_(std::make_unique<PrintAdapter<PrintType>>(std::move(object))) {}

  void print() const { pimpl_->print(); }

 private:
  struct PrintConcept {
    virtual ~PrintConcept() = default;
    virtual void print() const = 0;
  };

  template <typename Type>
  struct PrintAdapter final : public PrintConcept {
    constexpr PrintAdapter(Type object) noexcept : this_(std::move(object)) {}
    void print() const override { this_.print(); }
    Type this_;
  };

  std::unique_ptr<PrintConcept> pimpl_;
};

struct First {
  virtual ~First() = default;
  void print() const { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
struct Second {
  virtual ~Second() = default;
  void print() const { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main() {
  std::vector<Print> printable_list;
  printable_list.emplace_back(First());
  printable_list.emplace_back(Second());

  for (auto const& item : printable_list) item.print();
}

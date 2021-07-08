#pragma once

#include <drogon/HttpController.h>

namespace demo::v1::user_private {
struct data final {
  std::string user_name;
  std::string password;
  std::string token;
};
} // namespace demo::v1::user_private

namespace drogon {
template <>
inline demo::v1::user_private::data fromRequest(HttpRequest const& request) {
  auto json = request.getJsonObject();
  demo::v1::user_private::data data;
  if (json) {
    data.user_name = (*json)["user_name"].asString();
    data.token = (*json)["token"].asString();
    data.password = (*json)["password"].asString();
  }
  return data;
}
} // namespace drogon

namespace demo::v1 {
class user final: public drogon::HttpController<user> {
  using callback_t = std::function<void(drogon::HttpResponsePtr const&)>;

 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(user::login, "/token?user_id={1}&password={2}", drogon::Post);
  METHOD_ADD(user::get_info, "/{1}/info?token={2}", drogon::Get);
  METHOD_ADD(user::users_info, "/users", drogon::Post);
  METHOD_LIST_END

  void users_info(user_private::data&& data, callback_t&& callback) const;
  void login(drogon::HttpRequestPtr const& request,  callback_t&& callback,
             std::string&& user_id, std::string const& password);
  void get_info(drogon::HttpRequestPtr const& request,  callback_t&& callback,
                std::string user_id, std::string const& token) const;

};
} // namespace demo::v1

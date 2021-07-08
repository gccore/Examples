#pragma once

#include <drogon/HttpController.h>

namespace demo::v1 {
class user final: public drogon::HttpController<user> {
  using callback_t = std::function<void(drogon::HttpResponsePtr const&)>;

 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(user::login, "/token?user_id={1}&password={2}", drogon::Post);
  METHOD_ADD(user::get_info, "/{1}/info?token={2}", drogon::Get);
  METHOD_LIST_END

  void login(drogon::HttpRequestPtr const& reqest,  callback_t&& callback,
             std::string&& user_id, std::string const& password);
  void get_info(drogon::HttpRequestPtr const& reqest,  callback_t&& callback,
                std::string user_id, std::string const& token) const;

};
} // namespace demo::v1

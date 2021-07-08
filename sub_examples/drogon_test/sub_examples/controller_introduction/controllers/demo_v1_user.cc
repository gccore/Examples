#include "demo_v1_user.h"

#include <iostream>

namespace demo::v1 {
void user::login(drogon::HttpRequestPtr const& reqest, callback_t&& callback,
                 std::string&& user_id, std::string const& password) {
  LOG_DEBUG << "User: " << user_id << "(" << password << ") login.";
  Json::Value result;
  result["result"] = "okay";
  result["token"] = drogon::utils::getUuid();
  callback(drogon::HttpResponse::newHttpJsonResponse(result));
}

void user::get_info(drogon::HttpRequestPtr const& reqest, callback_t&& callback,
                    std::string user_id, std::string const& token) const {
  LOG_DEBUG << "User: " << user_id << "(" << token << ") information.";
  Json::Value result;
  result["result"] = "okay";
  result["user_name"] = "another-ghasem";
  result["user_id"] = user_id;
  result["gender"] = 1;
  callback(drogon::HttpResponse::newHttpJsonResponse(result));
}
} // namespace demo::v1

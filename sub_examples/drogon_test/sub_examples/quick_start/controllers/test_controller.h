#pragma once

#include <drogon/HttpSimpleController.h>

class test_controller final: public drogon::HttpSimpleController<test_controller> {
  using callback_t = std::function<void (const drogon::HttpResponsePtr&)>;

 public:
  virtual void asyncHandleHttpRequest(drogon::HttpRequestPtr const& req, callback_t&& callback) override;

  PATH_LIST_BEGIN
  PATH_ADD("/", drogon::Get, drogon::Post);
  PATH_ADD("/test", drogon::Get);
  PATH_LIST_END
};

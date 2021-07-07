#include "test_controller.h"

#include <iostream>

void test_controller::asyncHandleHttpRequest(drogon::HttpRequestPtr const& req, callback_t&& callback) {
  auto const respond = drogon::HttpResponse::newHttpResponse();
  respond->setStatusCode(drogon::k200OK);
  respond->setContentTypeCode(drogon::CT_TEXT_HTML);
  respond->setBody("Hello Ghasem");

  callback(respond);
}

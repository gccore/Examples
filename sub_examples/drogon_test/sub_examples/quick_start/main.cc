#include <drogon/drogon.h>

int main() {
  //Set HTTP listener address and port
  drogon::app().addListener("127.0.0.1", 8088);

  //Load config file
  //drogon::app().loadConfigFile("../config.json");
  //Run HTTP framework,the method will block in the internal event loop
  drogon::app().run();

  return 0;
}

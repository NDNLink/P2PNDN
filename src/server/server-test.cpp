#include "dhthelper.h"
#include "ndnhelper.h"
#include "ndnserver.h"

int main(int argc, char **argv)
{
  try
  {
    dht::DhtRunner *node =DhtHelper::getNode();
    std::string hostservice="udp4://192.0.2.1:6363";
    dht::Value value {(const uint8_t*)hostservice.data(), hostservice.size()};
    node->put("/prefix0",std::move(value));
    //uri example "udp4://192.0.2.1:6363"
    NdnServer server("/prefix0");
    server.run();
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return 1;
  }
}

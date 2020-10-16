#include "dhthelper.h"
#include "ndnhelper.h"
#include "ndnclient.h"

int main(int argc, char** argv)
{
  try {
	//DhtHelper dhtnode;
	dht::DhtRunner *node =DhtHelper::getNode();
	//TODO 
	node->get("/prefix0",[](const std::vector<std::shared_ptr<dht::Value>>& values) {
        // Callback called when values are found
        for (const auto& value : values)
            std::cout << "Found value: " << *value << std::endl;
        return true; // return false to stop the search
    });
	//dhtnode.getValue("/prefix0");
	//uri example: "udp4://192.0.2.1:6363"
	NdnHelper::FaceCreate("udp4://192.168.152.140:6363","/prefix0");
	NdnClient client("prefix0");
	client.run();
    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return 1;
  }
}

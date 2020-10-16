#include "dhthelper.h"
dht::DhtRunner *DhtHelper::m_node = new (std::nothrow) dht::DhtRunner;

DhtHelper::DhtHelper()
{
    m_node->run(4222, dht::crypto::generateIdentity(), true);
}

// void DhtHelper::putValue(const std::string &key, const dht::Value &value)
// {
//     m_node->put(key, std::move(value));
// }

// void DhtHelper::getValue(const std::string &key)
// {
//     m_node->get(key,[](const std::vector<std::shared_ptr<dht::Value>>& values){
//         for (const auto &value : values)
//         {
//             std::cout << "Found value" << *value << std::endl;
//         }
//         //TODO 
//         m_store->insert({key, std::make_shared(values)}); 
//         return true;
//     }
// }

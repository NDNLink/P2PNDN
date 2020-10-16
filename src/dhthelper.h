#pragma once
#include <opendht.h>
#include <new>
#include <string>
#include <vector>
#include <map>
class DhtHelper
{
private:
    DhtHelper();
    ~DhtHelper();
    class CGInstance
    {
    public:
        ~CGInstance()
        {
            if (m_node != nullptr)
            {
                m_node->join();
                delete m_node;
                m_node = nullptr;
            }
        }
    };
    static CGInstance gc;

public:
    static dht::DhtRunner *getNode()
    {
        return m_node;
    }
    //void putValue(const std::string &key, const dht::Value &value);
    //void getValue(const std::string &key);

private:
    static dht::DhtRunner *m_node;
    //std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<dht::Value>>>> m_store;
};
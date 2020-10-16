#include <ndn-cxx/security/key-chain.hpp>
#include <iostream>
#include "ndnserver.h"

NdnServer::NdnServer(const std::string &prefix) : m_prefix(prefix)
{
}
NdnServer::NdnServer() : m_prefix("/example0")
{
}
void NdnServer::run()
{
    m_face.setInterestFilter(m_prefix,
                             bind(&NdnServer::onInterest, this, _1, _2),
                             nullptr, // RegisterPrefixSuccessCallback is optional
                             bind(&NdnServer::onRegisterFailed, this, _1, _2));
    m_face.processEvents();
}

void NdnServer::onInterest(const ndn::InterestFilter &, const ndn::Interest &interest)
{
    std::cout << ">> I: " << interest << std::endl;

    static const std::string content("Hello, world! hello simon");

    // Create ndn::Data packet
    auto data = std::make_shared<ndn::Data>(interest.getName());
    data->setFreshnessPeriod(ndn::time::milliseconds(10000));
    data->setContent(reinterpret_cast<const uint8_t *>(content.data()), content.size());

    // Sign ndn::Data packet with default identity
    m_keyChain.sign(*data);
    // m_keyChain.sign(*data, signingByIdentity(<identityName>));
    // m_keyChain.sign(*data, signingByKey(<keyName>));
    // m_keyChain.sign(*data, signingByCertificate(<certName>));
    // m_keyChain.sign(*data, signingWithSha256());

    // Return ndn::Data packet to the requester
    std::cout << "<< D: " << *data << std::endl;
    m_face.put(*data);
}
void NdnServer::onRegisterFailed(const ndn::Name &prefix, const std::string &reason)
{
    std::cerr << "ERROR: Failed to register prefix '" << prefix
              << "' with the local forwarder (" << reason << ")" << std::endl;
    m_face.shutdown();
}
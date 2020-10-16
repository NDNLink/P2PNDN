#pragma once

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/signing-helpers.hpp>
#include <string>

class NdnServer
{
public:
  NdnServer(const std::string &prefix);

  NdnServer();

  void run();

private:
  void onInterest(const ndn::InterestFilter &, const ndn::Interest &interest);

  void onRegisterFailed(const ndn::Name &prefix, const std::string &reason);

private:
  ndn::Face m_face;
  ndn::KeyChain m_keyChain;
  std::string m_prefix;
};

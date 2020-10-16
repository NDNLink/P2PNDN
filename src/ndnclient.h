#pragma once 

#include <ndn-cxx/face.hpp>
#include <string>


class NdnClient
{
public:
  NdnClient();
  NdnClient(const std::string& name);
  void run();

private:
  void
  onData(const ndn::Interest&, const ndn::Data& data) const;
  void
  onNack(const ndn::Interest&, const ndn::lp::Nack& nack) const;
  void
  onTimeout(const ndn::Interest& interest) const;

private:
  ndn::Face m_face;
  std::string m_name;
};



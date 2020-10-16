#pragma once
#include <ndn-cxx/face.hpp>
#include <string>
#include <ndn-cxx/mgmt/nfd/control-command.hpp>
#include <ndn-cxx/mgmt/control-response.hpp>
#include <ndn-cxx/mgmt/nfd/controller.hpp>
#include <ndn-cxx/mgmt/nfd/control-parameters.hpp>

class NdnHelper
{
public:
   static void FaceCreate(const std::string &host, const std::string &prefix);

// private:
//     void OnFibAddNextHopSuccess(const ndn::nfd::ControlParameters parameters);
//     void OnFibAddNextHopFailure(const ndn::mgmt::ControlResponse response);
//     void OnFaceCreateSuccess(const ndn::nfd::ControlParameters parameters, const std::string &PrefixNameStr);
//     void OnFaceCreateFailure(const ndn::mgmt::ControlResponse response);
};
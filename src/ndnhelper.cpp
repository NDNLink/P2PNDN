#include "ndnhelper.h"
#include <ndn-cxx/encoding/block.hpp>
#include <ndn-cxx/encoding/tlv.hpp>
#include <ndn-cxx/encoding/tlv-nfd.hpp>
#include <ndn-cxx/net/face-uri.hpp>
#include <iostream>

void OnFibAddNextHopSuccess (const ndn::nfd::ControlParameters parameters) {
	printf("Adding next hop in fib succeeded \n");
}

void OnFibAddNextHopFailure (const ndn::mgmt::ControlResponse response) {
	printf("Adding next hop in fib failed \n");
}

// Get faceId from response and add fib entries for each prefix this IP serves
void OnFaceCreateSuccess (const ndn::nfd::ControlParameters parameters, const std::string& PrefixNameStr) {
	if (parameters.hasFaceId()) {
		unsigned long long faceId = parameters.getFaceId();
		printf("New face created. Id: %llu \n", faceId);

		//prefixList.parse();
		//for (auto prefixIterator = prefixList.elements_begin(); prefixIterator < prefixList.elements_end(); prefixIterator++) {
			// Control parameters include name and FaceId
			ndn::nfd::ControlParameters parameters;
			parameters.setFaceId(faceId);
			//ndn::Name prefixName = ndn::Name(reinterpret_cast<const char*>(prefixIterator->value()));
			ndn::Name prefixName = ndn::Name(PrefixNameStr);
			parameters.setName(prefixName);
			ndn::Face faceToNFD;
			ndn::KeyChain appKeyChain;
			ndn::nfd::Controller controller(faceToNFD, appKeyChain);
			controller.start<ndn::nfd::FibAddNextHopCommand>(parameters, &OnFibAddNextHopSuccess, &OnFibAddNextHopFailure);
			faceToNFD.processEvents();
		//}
	}
	else {
		// Assert
	}
}

void OnFaceCreateFailure (const ndn::mgmt::ControlResponse response) {
	unsigned int statusCode = response.getCode();
	if (statusCode == 409) {
		printf("Face already exists for this Uri: ");
		ndn::nfd::ControlParameters parameters;
		try {
		    parameters.wireDecode(response.getBody());
		    if (parameters.hasFaceId()) {
				unsigned long long faceId = parameters.getFaceId();
				printf("Id = %llu \n", faceId);
		    } else {
		    	// assert
		    }
		}
		catch (const ndn::tlv::Error& e) {
			printf("Error processing response \n");
		}
	} else {
		printf("Creating face failed with code %u \n", statusCode);
		std::cout<<response.getText()<<std::endl;
	}
}

void NdnHelper::FaceCreate(const std::string& host,const std::string& prefix)
{
    ndn::Face faceToNFD;
    ndn::KeyChain appKeyChain;
    ndn::nfd::Controller controller(faceToNFD,appKeyChain);
    ndn::nfd::ControlParameters parameters;
	//TODO 
    parameters.setUri(host);
    controller.start<ndn::nfd::FaceCreateCommand>(parameters,std::bind(&OnFaceCreateSuccess,_1,prefix),&OnFaceCreateFailure);
    faceToNFD.processEvents();  
}



// Author      : Meng Wang (mwang@orbe.us)
// Copyright   : Orbeus 2013 All right reserved
// Description :

#ifndef RESTAPI_H_
#define RESTAPI_H_

#include <string>
#include <map>

namespace Json {
	class Value;
}  // namespace

namespace rekognition_api {

bool APICall(const std::string& api_addr_base,
						 const std::map<std::string,
						 std::string>& query_config,
						 Json::Value* response);

}  // namespace rekognition_api
#endif // RESTAPI_H_

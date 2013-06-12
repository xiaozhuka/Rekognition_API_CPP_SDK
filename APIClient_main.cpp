// Author      : Meng Wang (mwang@orbe.us)
// Copyright   : Orbeus 2013 All right reserved
// Description :

#include "RESTapi.h"
#include "json/json.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Json::Value response;
	const string api_addr_base = "https://rekognition.com/func/api/?";
	map<string, string> query_config;

	// for testing only, please use client specific key and secret!
	query_config["api_key"] = "1234";
	query_config["api_secret"] = "5678";
	query_config["jobs"] = "face_part";
	query_config["urls"] = "http://rekognition.com/static/img/people.jpg";

	if (!rekognition_api::APICall(api_addr_base, query_config, &response)) {
		cerr << "API call failure!" << endl;
		return -1;
	}

	// For the format of the results, please refer to our doc:
	// http://rekognition.com/docs/
	const Json::Value face_detection = response["face_detection"];
	for (unsigned int i = 0; i < face_detection.size(); ++i) {
		double x, y, w, h;
		x = face_detection[i]["boundingbox"]["tl"]["x"].asDouble();
		y = face_detection[i]["boundingbox"]["tl"]["y"].asDouble();
		w = face_detection[i]["boundingbox"]["size"]["width"].asDouble();
		h = face_detection[i]["boundingbox"]["size"]["height"].asDouble();

		cout << "face " << i << ": [" << x << " " << y << " " << w << " " << h
				<< "]" << endl;
	}
	return 0;
}


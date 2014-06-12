// Author      : Meng Wang (mwang@orbe.us)
// Copyright   : Orbeus 2013 All right reserved
// Description : A test of C++ rekognition SDK. Tested in Ubuntu 12.04 and Windows8 + VisualStudio2013
#include "RESTapi.h"
#include "json/json.h"
#include "Base64Codec.h"

#include <fstream>
#include <sstream>
#include <streambuf>

using namespace std;

//#define CURL_TEST

#ifdef CURL_TEST

#include <curl/curl.h>
bool CurlTest()
{
	bool RetVal						= true;
	CURLcode ResCode				= CURL_LAST;
	CURL *curl						= NULL;
	string post_fields				= "";
	// const string api_addr_base		= "https://rekognition.com/func/api/?";
	const string api_addr_base = "http://google.com";

	cout << api_addr_base << endl;

	cout << "Starting CurlTest() ... \n";
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (!curl) {
		cerr << "CURL init error!" << endl;
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, api_addr_base.c_str());
	// curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	// curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	ResCode = curl_easy_perform(curl);
	cout << ResCode << endl;

	curl_easy_cleanup(curl);
	
	return RetVal;
}

int CurlTest2()
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://google.com");
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return 1;
}
#endif

int main(int argc, char **argv) {
#ifdef CURL_TEST
	if (CurlTest2()){
		cout << "Successfully finished CurlTest() \n";
		return 1;
	}
	cout << "Failed at CurlTest() \n";
	return 0;
#endif

	Json::Value response;
	const string api_addr_base = "http://rekognition.com/func/api/?";
	map<string, string> query_config;

	// for testing only, please use client specific key and secret!
	query_config["api_key"] = "YourAPIKey";  // **** CHANGE THIS ****
	query_config["api_secret"] = "YourAPISecret";  // **** CHANGE THIS ****
	query_config["jobs"] = "face";
	//query_config["urls"] = "http://rekognition.com/static/img/people.jpg";

	std::ifstream t("PathToYourImage/img.jpg", ios::binary);  // **** CHANGE THIS ****
	std::string buff_str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

	rekognition_api::Base64Codec base64_codec;
	string encoded;
	base64_codec.Encode(buff_str, &encoded);
	query_config["base64"] = encoded;

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


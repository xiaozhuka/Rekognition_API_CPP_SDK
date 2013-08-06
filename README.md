Version 1.0:
==========================
This C++ SDK intergrates ReKognition API. For more information about our ReKognition API, please read our documentation.

Usage:
==========================
<ol>
<il> Create response JSON object. </il>
 Json::Value response;
2. Specify API request in a map object.
const string api_addr_base = "https://rekognition.com/func/api/?";
map query_config;
query_config["api_key"] = "YOUR_API_KEY";
query_config["api_secret"] = "YOUR_API_SECRET";
query_config["jobs"] = "face_part";
query_config["urls"] = "http://rekognition.com/static/img/people.jpg";
3. Call API with APICall function.
rekognition_api::APICall(api_addr_base, query_config, &response);
</ol>

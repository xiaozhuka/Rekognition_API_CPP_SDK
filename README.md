Version 1.0:
==========================
This C++ SDK intergrates ReKognition API. For more information about our ReKognition API, please read our <a href="http://v2.rekognition.com/developer/docs">documentation</a>.

Usage:
==========================
<ol>
<li> Create response JSON object. </li>
<pre><code>Json::Value response;
</code></pre>
<li> Specify API request in a map object. </li>
<pre><code>const string api_addr_base = "https://rekognition.com/func/api/?";
map query_config;
query_config["api_key"] = "YOUR_API_KEY";
query_config["api_secret"] = "YOUR_API_SECRET";
query_config["jobs"] = "face_part";
query_config["urls"] = "http://rekognition.com/static/img/people.jpg";
</code></pre>
<li>  Call API with APICall function. </li>
<pre><code>rekognition_api::APICall(api_addr_base, query_config, &response);
</code></pre>
</ol>

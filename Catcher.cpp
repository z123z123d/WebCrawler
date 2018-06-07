#include<bits/stdc++.h>
#include<io.h>
#include "Catcher.h"
using namespace std;

Catcher:: Catcher() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

Catcher::~Catcher() {
	curl_global_cleanup();
}

void Catcher:: printLog(const string &Log) {
	fprintf (stderr, "%s\n", Log.c_str());
}

bool Catcher:: saveFile(const string &url, const string &fileName, const bool &isImage) {
	if (access(fileName.c_str(), 0) != -1) { //check whether the file exists
		printLog ("File exists, quit downloading.\n");
		return true;
	}
	CURLcode res;
	CURL *curl;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Firefox Browser"); //set an explorer attributively
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	freopen(fileName.c_str(), isImage? "wb" : "w", stdout);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK) { //fail to download image
		printLog("Fail to download image.\n");
		system(("rm " + fileName).c_str());
		return false;
	}
	return true;
}

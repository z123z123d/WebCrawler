#include<bits/stdc++.h>
#include<io.h>
#include "Catcher.h"
using namespace std;

void Catcher:: printLog(const string &Log) {
	fprintf (stderr, "%s\n", Log.c_str());
}

bool Catcher:: saveFile(const string &url, const string &fileName, const bool &isImage) {
	if (access(fileName.c_str(), 0) != -1) // check whether the file exists
		printLog ("File exists, continue downloading and cover it.\n");
	//cout << "Catcher:: saveFile (" << url << ")\n";
	CURLcode res;
	CURL *curl;
	FILE *fp = fopen(fileName.c_str(), isImage? "wb" : "w");
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Firefox Browser"); // set an explorer attributively
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1); // the following 3 lines set the relocation option
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // set the output file

	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK) { // fail to download file
		printLog("Fail to download " + url + ".\n");
		system(("rm " + fileName).c_str());
		return false;
	}
	fclose(fp);
	//printLog("Download successfully!");
	return true;
}

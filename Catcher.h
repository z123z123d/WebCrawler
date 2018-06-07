#pragma once
#include <bits/stdc++.h>
#include "curl/curl.h"
using namespace std;

class Catcher {
	static Catcher catcher;
	
	Catcher();
public:
    void printLog(const string &);
    bool saveFile(const string &, const string &, const bool & = 0);
    ~Catcher() = delete;
};

#pragma once
#include <bits/stdc++.h>
#include "curl/curl.h"
using namespace std;

class Catcher {
    CURL *curl;
public:
    Catcher();
    void printLog(const string &);
    bool saveFile(const string &, const string &, const bool & = 0);
    ~Catcher();
};

//static Catcher catcher;
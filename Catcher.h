#pragma once
#include <bits/stdc++.h>
#include "curl/curl.h"
using namespace std;

class Catcher {
    Catcher (const Catcher&) = delete;
    void operator = (const Catcher&) = delete;
    Catcher() { curl_global_init(CURL_GLOBAL_DEFAULT); }
    ~Catcher() { curl_global_cleanup(); }

public:
    void init() {}
    static Catcher& getCatcher() {
        static Catcher _catcher;
        return _catcher;
    }
    void printLog(const string &);
    bool saveFile(const string &, const string &, const bool & = 0);
};

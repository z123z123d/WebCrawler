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
    static Catcher& getCatcher() { // 通过getCatcher获得Catcher单例的引用
        static Catcher _catcher;
        return _catcher;
    }
    void printLog(const string &); // 将信息输出到终端
    bool saveFile(const string &, const string &, const bool & = 0); // 保存一个html/jpg文件(地址url)到本地文件(fileName),isImage代表其是否为Image
};

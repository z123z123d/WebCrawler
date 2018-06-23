#pragma once
#include <bits/stdc++.h>
#include "BaseCrawler.h"
#include "DoubanObject.h"
using namespace std;

static Catcher &catcher = Catcher:: getCatcher();

class DoubanCrawler : public BaseCrawler {
    vector<DataType> TargetDataList;
    vector<DoubanMovieObject*> ObjectList;
    virtual void addTargetData (const DataType &);
    virtual void addObject (BaseObject*);

public:
    virtual void init();
    virtual void work();
    bool getData (string content, BaseData *data); // 从content中抓取处一个数据(名称、评分等)data
    void readFile (const string&, string&); // 将一个文件所有内容读入字符串
    void downloadPics (DoubanMovieObject *); // 将一部电影的所有剧照下载到本地
    DoubanMovieObject* scanPage (const string&); // 扫描一个网页，返回一个Object，为该网页对应的电影
};

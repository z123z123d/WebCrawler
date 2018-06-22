#pragma once
#include <bits/stdc++.h>
#include "BaseCrawler.h"
#include "DoubanObject.h"
using namespace std;

static Catcher &catcher = Catcher:: getCatcher();

class DoubanCrawler : public BaseCrawler {
    vector<DataType> TargetDataList;
    vector<DoubanMovieObject*> ObjectList;
public:
    virtual void addTargetData (const DataType &); // add a kind of target data
    virtual void addObject (BaseObject*); // add an object(movie)
    virtual void init(); // the general interface of initialization
    virtual void work();
    bool getData (string content, BaseData *data);
    void readFile (const string&, string&);
    void downloadPics (DoubanMovieObject *);
    DoubanMovieObject* scanPage (const string&);
};

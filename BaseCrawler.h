#pragma once
#include <bits/stdc++.h>
#include "Catcher.h"
#include "BaseObject.h"
using namespace std;

class BaseCrawler {
    vector<BaseObject*> ObjectList;
    vector<DataType> TargetDataList;

/*
    ObjectList is the list of all the downloaded movies
    TargetDataList is the list of all the targeted data
*/

    virtual void addTargetData (const DataType &) = 0; // add a kind of target data
    virtual void addObject (const BaseObject* &) = 0; // add an object(movie)
public:
    virtual void init() = 0; // the general interface of initialization
    virtual void work() = 0; // the general interface of main work
};

#pragma once
#include <bits/stdc++.h>
using namespace std;

enum DataType {
    _name,
    _date,
    _director,
    _writers,
    _actors,
    _labels,
    _country,
    _language,
    _runtime,
    _producer,
    _earnings,
    _rate,
    _awards,
    _reviews,
    _photos,
};

class BaseData {
    DataType type;
public:
    virtual void setData() = 0;
    virtual void* getData() = 0;
    virtual void printData (const string &) = 0;
    virtual DataType getType() = 0;
};

class BaseObject {
    vector<BaseData*> DataSet;
public:
    virtual void initDataSet (const vector<DataType>&) = 0; // initialize the data set with the list of data type
    virtual vector<BaseData*> getDataSet() = 0;
    virtual void printObject (const string &) = 0;
    virtual int getDataSize() = 0;
};
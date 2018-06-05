#include <bits/stdc++.h>
#include "BaseObject.h"
using namespace std;

DataType BaseData:: getType() {
    return type;
}

void StringData:: setString(const string &_data) {
    data = _data;
}

string StringData::getString() const {
    return data;
}

void StringData::printData(const string &path) const {
    ofstream ouf (path.c_str());
    ouf << data;
}

void IntData:: setInt(const int &_data) {
    data = _data;
}

int IntData:: getInt() const {
    return data;
}

void IntData::printData(const string &path) const {
    ofstream ouf (path.c_str());
    ouf << data;
}

void DoubleData:: setDouble(const double &_data) {
    data = _data;
}

double DoubleData::getDouble() const {
    return data;
}

void DoubleData::printData(const string &path) const {
    ofstream ouf (path.c_str());
    ouf << data;
}

void VectorStringData::setString(const string &_data) {
    data.push_back (_data);
}

vector<string> VectorStringData::getVectorString() const {
    return data;
}

void VectorStringData::printData(const string &path) const {
    ofstream ouf (path.c_str());
    bool flag = 0;
    for (string it : data) {
        if (flag) ouf << " ";
        ouf << it;
        flag = 1;
    }
}

vector<BaseData*> BaseObject:: getDataSet() const {
    return DataSet;
};

int BaseObject:: getDataSize() const {
    return DataSet.size();
}

void BaseObject:: printObject (const string &path) const {
    for (int i = 0; i < DataSet.size(); i++)
        DataSet[i]-> printData (path);
}

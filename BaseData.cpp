#include <bits/stdc++.h>
#include "BaseData.h"
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

void StringData::printData(ofstream &ouf) {
    ouf << data;
}

void IntData:: setInt(const int &_data) {
    data = _data;
}

int IntData:: getInt() const {
    return data;
}

void IntData::printData(ofstream &ouf) {
    ouf << data;
}

void DoubleData:: setDouble(const double &_data) {
    data = _data;
}

double DoubleData::getDouble() const {
    return data;
}

void DoubleData::printData(ofstream &ouf) {
    ouf << data;
}

void VectorStringData::setString(const string &_data) {
    data.push_back (_data);
}

vector<string> VectorStringData::getVectorString() const {
    return data;
}

void VectorStringData::printData(ofstream &ouf) {
    bool flag = 0;
    for (string it : data) {
        if (flag) ouf << " / ";
        ouf << it;
        flag = 1;
    }
}

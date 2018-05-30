#include <bits/stdc++.h>
#include "BaseObject.h"
using namespace std;

DataType BaseData:: getType() {
    return type;
}

int BaseObject:: getDataSize() {
    return DataSet.size();
}

vector<BaseData*> BaseObject:: getDataSet() {
    return DataSet;
};

void BaseObject:: printObject() {
    for (int i = 0; i < DataSet.size(); i++)
        DataSet[i]-> printData();
}
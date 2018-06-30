#include <bits/stdc++.h>
#include "BaseObject.h"
using namespace std;

vector<BaseData*> BaseObject:: getDataSet() const {
    return DataSet;
};

void BaseObject:: printObject (ofstream &ouf) {
    for (int i = 0; i < DataSet.size(); i++)
        DataSet[i]-> printData (ouf);
}

int BaseObject:: getDataSize() const {
    return DataSet.size();
}

void BaseObject:: addData (BaseData *data) {
    DataSet.push_back (data);
}

BaseData* BaseObject:: getData (DataType type) const {
    for (auto it : DataSet)
        if (it->getType() == type)
            return it;
    return nullptr;
}
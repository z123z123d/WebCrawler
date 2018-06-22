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
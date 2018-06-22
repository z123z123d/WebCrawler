#include <bits/stdc++.h>
#include "DoubanObject.h"
using namespace std;

/*
void DoubanMovieObject:: initDataSet() {
    cout << "init" << endl;
    for (auto it : DoubanMovieDataList)
        DataSet.push_back (newData (it));
    cout << "init_succeed" << endl;
}
*/

void DoubanMovieObject:: addData (BaseData *data) {
    DataSet.push_back (data);
}

BaseData* DoubanMovieObject:: getData (DataType type) const {
    for (auto it : DataSet)
        if (it->getType() == type)
            return it;
    return nullptr;
}
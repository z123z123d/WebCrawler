#include <bits/stdc++.h>
#include "BaseCrawler.h"
using namespace std;

void BaseCrawler:: addTargetData (const DataType &datatype) {
    TargetDataList.push_back (datatype);
}

void BaseCrawler:: addObject (const BaseObject* &object) {
    ObjectList.push_back ((BaseObject*) object);
}

#pragma once
#include <bits/stdc++.h>
#include "BaseObject.h"
using namespace std;

static DataType DoubanMovieDataList[] = {
    _name,
    _date,
    _director,
    _writers,
    _actors,
    _labels,
    _country,
    _language,
    _runtime,
    _rating,
    _awards,
    _reviews,
    _photos,
};

class DoubanMovieObject : public BaseObject {
public:
    static BaseData* newData (DataType type) {
        BaseData *data = NULL;
        if (type == _rating)
            data = new DoubleData(type);
        else if (type == _date || type == _director || type == _country || type == _language || type == _runtime)
            data = new StringData(type);
        else
            data = new VectorStringData(type);
        return data;
    }
    void addData (BaseData*);
    BaseData* getData (DataType) const;
};

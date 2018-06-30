#pragma once
#include <bits/stdc++.h>
#include "BaseData.h"
using namespace std;

class BaseObject {
protected:
    vector<BaseData*> DataSet;
public:
    virtual vector<BaseData*> getDataSet() const; // 获取此Object内部数据集合
    virtual void printObject (ofstream &); // 输出数据，根据需要可重新实现
    virtual int getDataSize() const; // 获取数据集合大小
	virtual ~BaseObject() {
		for (auto it : DataSet)
			delete it;
	}
};

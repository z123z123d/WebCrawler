#pragma once
#include <bits/stdc++.h>
#include "Catcher.h"
#include "BaseObject.h"
using namespace std;

class BaseCrawler {
public:
    virtual void addTargetData (const DataType &) = 0; // 给爬虫新增一种需要爬的目标数据
    virtual void addObject (BaseObject*) = 0; // 给爬虫新增一个爬完的电影
    virtual void init() = 0;
    /* 初始化统一接口，从配置文件./crawler-configuration.txt里输入初始化信息：
     * 共15行，第i行一个整数0/1表示是否爬去DataType中第i种数据
     */
    virtual void work() = 0; // 爬虫主程序统一接口
	virtual ~BaseCrawler();
};

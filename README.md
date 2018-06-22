# OOP WebCrawler Project

## 5.30

目前已实现基类接口（主要以助教ppt上的实现方法为框架）

## 6.5

加入了基本数据类：IntData,DoubleData,StringData,VectorStringData。

对于电影的各项数据：如名字、日期、票房等，则分别采用其中一种数据类进行储存。（虽然感觉比较sb，但是对于每一类数据单独继承一个类感觉也很sb...）

## 6.7

更新了Catcher(.h/.cpp)的单例模式，修改了Catcher中的curl的init与clean_up方式。

更新了BaseCrawler(.h)中的init()接口。

## 6.22

更新了BaseObject的接口和Catcher的单例模式写法，以及Catcher里加入了重定向设置（爬douban的时候碰到了这个问题）

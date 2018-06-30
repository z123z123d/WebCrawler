#include <bits/stdc++.h>
#include "BaseCrawler.h"
using namespace std;

DataType getTypeId (string str) {
	if (str == "name")
		return DataType (0);
	if (str == "date")
		return DataType (1);
	if (str == "director")
		return DataType (2);
	if (str == "writers")
		return DataType (3);
	if (str == "actors")
		return DataType (4);
	if (str == "labels")
		return DataType (5);
	if (str == "country")
		return DataType (6);
	if (str == "language")
		return DataType (7);
	if (str == "runtime")
		return DataType (8);
	if (str == "producer")
		return DataType (9);
	if (str == "earnings")
		return DataType (10);
	if (str == "rating")
		return DataType (11);
	if (str == "awards")
		return DataType (12);
	if (str == "reviews")
		return DataType (13);
	if (str == "photos")
		return DataType (14);
}

vector<DataType> BaseCrawler:: readConfiguration (string File) {
	ifstream fin(File);
	vector<DataType> TargetDataList;
	string str, _str;
	int num;
	while (fin >> str) {
		fin >> _str;
		fin >> num;
		if (num)
			TargetDataList.push_back (getTypeId(str));
	}
	return TargetDataList;
}

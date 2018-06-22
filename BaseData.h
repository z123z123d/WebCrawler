#pragma once
#include <bits/stdc++.h>
using namespace std;

enum DataType {
    _name,
    _date,
    _director,
    _writers,
    _actors,
    _labels,
    _country,
    _language,
    _runtime,
    _producer,
    _earnings,
    _rating,
    _awards,
    _reviews,
    _photos,
};

class BaseData {
protected:
    DataType type;
public:
    BaseData (DataType _type): type(_type) {}
    virtual void setString(const string &) {};
    virtual void setInt(const int &) {};
    virtual void setDouble(const double &) {};

    virtual string getString() const {};
    virtual int getInt() const {};
    virtual double getDouble() const {};
    virtual vector<string> getVectorString() const {};

    virtual void printData (ofstream &) = 0;
    DataType getType();
};

class StringData : public BaseData {
    string data;
public:
    StringData (DataType _type): BaseData(_type) {}
    virtual void setString(const string &);
    virtual string getString() const;
    virtual void printData (ofstream &);
};

class IntData : public BaseData {
    int data;
public:
    IntData (DataType _type): BaseData(_type) {}
    virtual void setInt(const int &);
    virtual int getInt() const;
    virtual void printData (ofstream &);
};

class DoubleData : public BaseData {
    double data;
public:
    DoubleData (DataType _type): BaseData(_type) {}
    virtual void setDouble(const double &);
    virtual double getDouble() const;
    virtual void printData (ofstream &);
    DataType getType();
};

class VectorStringData : public BaseData {
    vector<string> data;
public:
    VectorStringData (DataType _type): BaseData(_type) {}
    virtual void setString(const string &); // add a string into data
    virtual vector<string> getVectorString() const;
    virtual void printData (ofstream &);
};

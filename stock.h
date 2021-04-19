#pragma once
#include <string>
#include <vector>
#include <utility>
using namespace std;
class Stock{

public:
    string name;
    double currentPrice;
    double historicPrice;
    double yearHigh;
    double yearLow;
    double yearAvg;
    double yearReturn;

    Stock(){
        name = "";
    }
    Stock(string name, double cPrice, double yHigh, double yLow, double hPrice, double yReturn, double yAvg){
        this->name = name;
        this->currentPrice = cPrice;
        this->historicPrice = hPrice;
        this->yearHigh = yHigh;
        this->yearLow = yLow;
        this->yearReturn = yReturn;
        this->yearAvg = yAvg;
    }
    bool operator< (const Stock& rhs){
        return name < rhs.name;
    }
    bool operator> (const Stock& rhs){
        return name > rhs.name;
    }
    bool operator<=(const Stock& rhs){
        return !(*this > rhs);
    }
    bool operator>=(const Stock& rhs){
        return !(*this < rhs);
    }
    bool operator==(const Stock& rhs){
        return !(*this < rhs) && !(*this > rhs);
    }
    bool operator!=(const Stock& rhs){
        return !(*this == rhs);
    }
};

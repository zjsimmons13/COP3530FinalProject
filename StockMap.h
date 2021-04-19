#pragma once
#include "stock.h"
using namespace std;
class StockMap{
    struct StockNode{
        StockNode* next; // single link list
        Stock* value;
        string key;
        StockNode(string key ,Stock* value, StockNode* next = nullptr ){
            this->key = key;
            this->value = value;
            this->next = next;
        }
        ~StockNode(){
            delete value;
        }
    };

    //private variables
    int buckets;
    int currentSize;
    const float MAX_LOAD_FACTOR = 1.0; // ideal for seperate chaining?
    StockNode** hashTable; //array of pointers

    //private function def
    int hash(string);
    void rehash();
    StockNode* recursiveInsert(string, Stock*, StockNode*, bool &);
    StockNode* recursiveInsertNoDuplicateCheck(string, Stock*, StockNode*);
    StockNode* recursiveErase(string, StockNode*, bool&);
    bool insertIntoHashTable(string, Stock*, StockNode**, bool = false);

    public:
    //public function def
    StockMap();
    StockMap(int);
    ~StockMap();
    bool insert(string, Stock*);
    Stock* find(string);
    bool erase(string);
    int size();
};


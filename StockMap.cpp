#include "StockMap.h"

// private functions
    int StockMap::hash(string key){ // returns bucket index for next insert
        int sum = 0;
        for(unsigned int i = 0; i < key.size(); i++){ // not very unique hashing but should work fine
            sum = (sum * 31) +((int)key[i] - 65); // Turns A-Z to (0 to 25) * times a prime because in lecture primes make good hash functions
        }
        return sum % buckets; // maps the key to a place in the hashtable
    }

    void StockMap::rehash(){ // makes a new hashTable double the size
        int oldBuckets = buckets;
        buckets *=2;
        StockNode ** oldTable = hashTable;
        hashTable = new StockNode*[buckets](); // () fills it with nullptr
        for(int i = 0; i < oldBuckets; i++){
            StockNode* start = oldTable[i];
            while(start){
                insertIntoHashTable(start->key,start->value,hashTable,true);
                start= start->next;
            }
        }
        delete[] oldTable;
    }

    StockMap::StockNode* StockMap::recursiveInsert(string key , Stock* value , StockNode* root , bool & sucessful){
        if(root){
            if(root->key != key){ // insert at end of list so duplicates are checked for
                root->next = recursiveInsert(key,value, root->next, sucessful);
                return root;
            }
            sucessful = false;
            return root; // duplicate dont insert
        }
        root = new StockNode(key, value); // root is nullptr so insert end reached without duplicates insert
        currentSize++;
        return root;
    }

    StockMap::StockNode* StockMap::recursiveInsertNoDuplicateCheck(string key , Stock* value , StockNode* root ){
        root = new StockNode(key,value,root);
        return root;
    }

    StockMap::StockNode* StockMap::recursiveErase(string key, StockNode* root, bool& sucessful){ // sucessful swapped to true if erase is completed
        if(root){
            if(root->key == key){
                StockNode * temp = root->next;
                delete root;
                sucessful = true;
                currentSize--;
                return temp;
            }
            root->next = recursiveErase(key,root->next, sucessful);
            return root;
        }
        return nullptr;
    }

    bool StockMap::insertIntoHashTable(string key , Stock* value, StockNode** table , bool rehash){ //rehash default is false so not a rehash insert
        StockNode* start = table[hash(key)];
        bool sucessful = true; // if fails will swap to false
        if(!rehash) // if not a rehash insert check for duplicates else don't this saves a lot of time during Rehash()
            start = recursiveInsert(key, value, start, sucessful);
        else
            start = recursiveInsertNoDuplicateCheck(key, value, start);
        table[hash(key)] = start;
        return sucessful;
    }


    // public functions
    StockMap::StockMap(){
        currentSize = 0;
        buckets = 10; // guess of how big to start 10?
        hashTable = new StockNode*[buckets](); // () fills it with nullptrs
    }

    StockMap::StockMap(int buckets){
        currentSize = 0;
        this->buckets = buckets; // start big if you are going to insert a lot
        hashTable = new StockNode*[buckets](); // () fills it with nullptrs
    }

    StockMap::~StockMap(){
        for(int i = 0; i < buckets; i++){
            StockNode* start = hashTable[i];
            while(start){
                StockNode* temp = start->next;
                delete start;
                start = temp;
            }
        }
        delete[] hashTable;
    }
    bool StockMap::insert(string key , Stock* value){
        bool sucessful = insertIntoHashTable(key,value,hashTable);
        if(currentSize/(float)buckets >= MAX_LOAD_FACTOR) // if unsucessful currentSize will be unchanged so no Rehash
            rehash();
        return sucessful;
    }

    Stock* StockMap::find(string key){
        StockNode* start = hashTable[hash(key)];
        while(start){
            if(start->key == key){
                return start->value;
            }
            start = start->next;
        }
        return nullptr;
    }

    bool StockMap::erase(string key){
        bool successful = false;
        hashTable[hash(key)] = recursiveErase(key,hashTable[hash(key)], successful);
        return successful;
    }

    int StockMap::size(){
        return currentSize;
    }

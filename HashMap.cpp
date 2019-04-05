//
// Created by Tristan Dam on 2019-02-27.
// The Youtube Series "How to Create A Hash Table in C++" by the
// Youtube Channel "Paul Programming" was referenced in the construction of this Project.

#include <iostream>
#include "HashMap.hpp"




// Default Hash Function

static unsigned int default_hash_function(const std::string& key)
{
    int hash = 0;
    for (int i = 0; i <key.length(); i++)
    {
        hash += (int)key[i];
    }
    return hash;
}

void HashMap::zeroFill(int* a, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        a[i] = 0;
    }
}

HashMap::HashFunction default_hasher = default_hash_function;

//HashMap::HashMap()
//:hasher{default_hasher},capacity{HashMap::initialBucketCount}
//{
//    HashItems = new Node*[capacity];
//    for (int i = 0; i<capacity; i++)
//    {
//        HashItems[i] = nullptr;
//    }
//
//
////    zeroFill(bucket_count_list,initialBucketCount);
//}

unsigned int HashMap::get_index(int hash) const
{
    return hash % capacity;
}

HashMap::HashMap(): HashMap(default_hasher){}

HashMap::HashMap(HashMap::HashFunction _hasher)
:hasher{_hasher},capacity{HashMap::initialBucketCount}
{
    HashItems = new Node*[capacity];
    for (int i = 0; i<capacity; i++)
    {
        HashItems[i] = nullptr;
    }
//
    bucket_count_list = new int[initialBucketCount];
    zeroFill(bucket_count_list,initialBucketCount);
    totalCount = 0;
}

HashMap::HashMap(const HashMap &hm)
:hasher{hm.hasher},totalCount{0},capacity{hm.capacity}
{
    HashItems = new Node*[capacity];
    bucket_count_list = new int[capacity];
    for (int i = 0; i<hm.capacity; i++)
    {
        HashItems[i] = nullptr;
    }
    for (int i = 0;i<hm.capacity;i++)
    {
        recursive_add(hm.HashItems[i]);
        bucket_count_list[i] = hm.bucket_count_list[i];
    }
    
}

HashMap::~HashMap() // DESTRUCTOR
{
    clear();
    delete[] HashItems;
}

HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != & hm)
    {
        //Node* newItems = new Node[hm.capacity];
        int* new_bucket_count_list = new int[hm.capacity];
        
        for (int i = 0; i<hm.capacity; i++)
        {
            new_bucket_count_list[i] = hm.bucket_count_list[i];
        }
        
        
        capacity = hm.capacity;
        hasher = hm.hasher;
        totalCount = 0;
        delete[] bucket_count_list;
        bucket_count_list = new_bucket_count_list;
        //delete[] HashItems;
        //HashItems = &newItems;
    }
    return *this;
}

//add

//clears all key/value pairs in the hashmap
// Referenced geeksforgeeks "deleting linked list" in writing of this function
void HashMap::clear()
{
    for (int i = 0;i<capacity;i++)
    {
        if (HashItems[i] != nullptr)
        {
            Node* current = HashItems[i];
            Node* next;
            
            while (current != nullptr)
            {
                next = current->next;
                delete current;
                current = next;
            }
            HashItems[i] = nullptr;
        }
        
    }
    zeroFill(bucket_count_list,capacity);
    totalCount = 0;
}

void HashMap::recursive_add(Node *n)
{
    //base case
    if(n == nullptr){
        return;
    }
    recursive_hash(n->next);
    add(n->key, n->value);
}

void HashMap::recursive_hash(Node *n)
    {
    //base case
    if(n == nullptr){
        return;
    }
    recursive_hash(n->next);
    add(n->key, n->value);
    delete n;
}

void HashMap::rehash()
{
    // Needs to:
    
    // Create a new bucket_count_list with 2x+1 spots.
    // Then initialize that
    int oldcapacity = capacity;
    capacity = (capacity*2)+1;
    
    Node ** HashItems_old = HashItems;
    HashItems = new Node*[capacity]; // IF YOU CREATE THIS WITHOUT SETTING THINGS TO NULLPOINTER RANDOM VALUES ARE IN THERE
    for (int i = 0; i<capacity; i++)
    {
        HashItems[i] = nullptr;
    }
    
    bucket_count_list = new int[capacity];
    zeroFill(bucket_count_list, capacity);
    totalCount = 0;
    
    for (int i = 0;i<oldcapacity;i++)
    {
        recursive_hash(HashItems_old[i]);        
    }
    
    // create a new bucket count list for the updated hashitems
    delete HashItems_old;
}

//void HashMap::printnode()

void HashMap::add(const std::string& key, const std::string& value)
{
    
    int index = get_index(hasher(key));
    
    if (HashItems[index] == nullptr)
    {
        Node* node_to_insert = new Node{key,value,nullptr};
        HashItems[index] = node_to_insert;
        bucket_count_list[index] += 1;
        totalCount++;
        //std::cout << "Inserting username " << key << " with value " << value << " into cell index " << index << std::endl;
    }
    else
    {
        
        Node* starting_node = HashItems[index];
        if (starting_node->key == key) // if the key is already in the map, do nothing and break.
        {
            //std::cout << "Key " << key << " is already in the Map, so do nothing." << std::endl;
            return;
        }
        
        while (starting_node->next != nullptr )
        {
            if (starting_node->next->key == key) // if the key is already in the map, do nothing and break.
            {
                //std::cout << "Key " << key << " is already in the Map, so do nothing." << std::endl;
                return;
            }
            starting_node = starting_node->next;
        }
        // If we get here, that means the key hasn't been found, so we need to add it.
        Node* node_to_add = new Node{key,value,nullptr};
        starting_node->next = node_to_add;
        //std::cout << "Inserting username " << key << " with value " << value << "into cell index " << index << std::endl;
        bucket_count_list[index] += 1;
        totalCount++;
    }
    if (loadFactor() > 0.8)
    {
        rehash();
    }
    
}
//remove

void HashMap::remove(const std::string& key)
{
    int index = get_index(hasher(key));
    Node* current_node = HashItems[index];
    
    if (current_node != nullptr)
    {
    if (current_node->key == key) // Checking if the first node matches the key
    {
        HashItems[index] = current_node->next;
        delete current_node;
        bucket_count_list[index]--;
        totalCount--;
        return;
    }
    
    while (current_node->next != nullptr) //iterate through the other nodes
    {
        if (current_node->next->key == key) // and check if it's the matching key
        {
            HashMap::Node* to_delete = current_node->next;
            current_node->next = current_node->next->next;
            delete to_delete;
            bucket_count_list[index]--;
            totalCount--;
            return;
        }
        
    }
        
}
}

bool HashMap::contains(const std::string& key) const
{
    int index = get_index(hasher(key));
    Node* node_to_check = HashItems[index];
    while (node_to_check != nullptr)
    {
        if (node_to_check->key == key)
        {
            //std::cout << "Found it. Key " << node_to_check->key << " is in the HashMap." << std::endl;
            return true;
        }
        node_to_check = node_to_check->next;
    }

    //std::cout << "Didn't find it. Key " << key << " is not in the HashMap." << std::endl;
     return false;
}
//value

std::string HashMap::value(const std::string& key) const
{
    int index = get_index(hasher(key));
    Node* node_to_check = HashItems[index];
    
    while (node_to_check != nullptr)
    {
        if (node_to_check->key == key)
        {
            //std::cout << "Found it. Key " << node_to_check->key << " has the value " <<                  node_to_check->value << std::endl;
            return node_to_check->value;
        }
        node_to_check = node_to_check->next;
    }

    //std::cout << "Didn't find it. Key " << key << " is not in the HashMap or has no value." << std::endl;
    return "";
}

// size() returns the number of key/value pairs stored in this HashMap.
unsigned int HashMap::size() const
{
    return totalCount;
}

// bucketCount() returns the number of buckets currently allocated in
// this HashMap.
unsigned int HashMap::bucketCount() const
{
    return capacity;
}

// loadFactor() returns the proportion of the number of key/value pairs
// to the number of buckets, a measurement of how "full" the HashMap is.
// For example, if there are 20 key/value pairs and 50 buckets, we would
// say that the load factor is 20/50 = 0.4.
double HashMap::loadFactor() const
{
    return (double)size()/(double)capacity;
}

// maxBucketSize() returns the number of key/value pairs stored in this
// HashMap's largest bucket.
unsigned int HashMap::maxBucketSize() const
{
    int current_max = bucket_count_list[0];
    int max_index = 0;
    int max_count = 0;
    
    for (int i =1; i<capacity;i++)
    {
        if (bucket_count_list[i] > current_max)
        {
            current_max = bucket_count_list[i];
            max_index = i;
        }
    }
    
    Node* current_node = HashItems[max_index];
    if (HashItems[max_index] != nullptr)
    {
        max_count++;
    }
    while (current_node->next!=nullptr)
    {
        max_count ++;
    }
    return max_count;
}



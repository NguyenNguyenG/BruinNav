// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

#ifndef MyMap_h
#define MyMap_h
#include <iostream>
#include "provided.h"
#include "support.h"

template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap();
    ~MyMap();
    void clear();
    int size() const;
    void associate(const KeyType& key, const ValueType& value);
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    
private:
    struct Node
    {
        Node(const KeyType& keyT, const ValueType& valueT)
        {
            left = right = nullptr;
            key = keyT;
            value = valueT;
        }
        Node* left;
        Node* right;
        KeyType key;
        ValueType value;
    };
    Node* head;
    int m_size;
    void clear(Node* curr);
};

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap()
{
    head = nullptr;
    m_size  = 0;
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const
{
    return m_size;
}

template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType, ValueType>::find(const KeyType& key) const
{
    Node* ptr = head;
    while(ptr != nullptr)
    {
        //return if found the key
        if(key == ptr -> key)
        {
            return &(ptr -> value);
        }
        // go to the left on bst if key is smaller
        else if(key < ptr -> key)
        {
            ptr = ptr -> left;
        }
        //otherwise go right
        else
            ptr = ptr -> right;
    }
    //no key is found
    return nullptr;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    //just make a new node if the map is empty
    if(head == nullptr)
    {
        m_size++;
       head = new Node(key, value);
       return;
    }
    Node* it = head;
    for(;;)
    {
        //if key is already exist just change its content
        if(key == it ->key)
        {
            it -> value = value;
            return;
        }
        //keep going to the left if possible on bst if the key is smaller than current key
        if(key < it -> key)
        {
            if(it -> left != nullptr)
            {
                it = it ->left;
            }
            //make new node once cannot go left anymore
            else
            {
                it -> left = new Node(key, value);
                m_size++;
                return;
            }
        }
        //keep going to the right if possible on bst if the key is bigger than current key
        else if(key > it ->key)
        {
            if(it -> right != nullptr)
            {
                it = it ->right;
            }
            //make new node once can't go right anymore
            else
            {
                it -> right = new Node(key, value);
                m_size++;
                return;
            }
        }
    }
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear()
{
    clear(head);
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear(Node* curr)
{
    if(curr == nullptr)
        return;
    clear(curr ->right);
    clear(curr -> left);
    delete curr;
}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap()
{
    clear();
}

#endif /* MyMap_h */

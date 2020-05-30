#pragma once

#include <iostream>
#include "ListNode.h"

template <typename T>
struct LinkedList
{
public: // private:
    ListNode<T>* _head = nullptr;

    LinkedList()
    {
    }

    void Add(T value)
    {
        auto newNode = new ListNode<T>();
        newNode->Value = value;

        if (_head == nullptr)
        {
            _head = newNode;
            return;
        }

        auto last = GetLast();
        last->Next = newNode;
    }

    ListNode<T>* GetHead()
    {
        return _head;
    }

    ListNode<T>* GetLast()
    {
        auto h = _head;

        while (h->Next != nullptr)
        {
            h = h->Next;
        }

        return h;
    }

    ListNode<T>* ElementAt(int pos)
    {
        auto h = _head;
        if (pos == 0) return h;

        int i = 0;
        while (i != pos && h->Next != nullptr)
        {
            h = h->Next;
            i++;
        }

        return h;
    }

    bool IsEmpty()
    {
        return _head == nullptr;
    }

    void RemoveLastNode()
    {
        auto last = GetLast();

        if (_head == last)
        {
            _head = nullptr;
            delete last;
            return;
        }

        auto preLastNode = _head;
        while (preLastNode->Next != last)
        {
            preLastNode = preLastNode->Next;
        }

        delete last;

        preLastNode->Next = nullptr;
    }
};

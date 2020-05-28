#pragma once

#include <iostream>

template <typename T>
struct Queue
{
public:
    Queue(int capacity)
    {
        _arr = new T[capacity];

        _count = 0;
        _rear = 0;

        _capacity = capacity;
    }

    ~Queue()
    {
        delete[] _arr;
    }

    bool Enqueue(T value)
    {
        if (IsFull()) return false;

        Insert(value);
        return true;
    }

    T Dequeue()
    {
        if (IsEmpty())
        {
            throw new std::runtime_error("queue is empty");
        }

        auto frontElement = GetFront();

        ShiftInternalArrayUp();

        return frontElement;
    }

    bool IsEmpty()
    {
        return !_count;
    }

    bool IsFull()
    {
        return _count == _capacity;
    }

private:
    T* _arr;
    int _capacity;
    int _count;

    int _rear;

    void Insert(T value)
    {
        _arr[_rear] = value;
        _rear = (_rear + 1) % _capacity;

        _count++;
    }

    void ShiftInternalArrayUp()
    {
        for (int i = 0; i < _rear - 1; i++)
        {
            _arr[i] = _arr[i + 1];
        }

        _rear--; // это должно быть здесь?
        _count--;
    }

    T GetFront()
    {
        return _arr[0];
    }
};

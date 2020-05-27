#pragma once

template <typename T>
struct ListNode
{
public:
    T* Value = nullptr;
    ListNode<T>* Next = nullptr;

    ListNode()
    {
    }
};

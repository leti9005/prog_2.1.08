#pragma once

template <typename T>
struct ListNode
{
public:
    T Value;
    ListNode<T>* Next = nullptr;

    ListNode()
    {
    }
};

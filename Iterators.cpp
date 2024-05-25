#include "Iterators.h"

// iterator ////////////////////////////////////////////////////////

iterator::iterator(char* ptr)
    : ptr_(ptr)
{
}

iterator & iterator::operator++()
{
    ++ptr_;
    return *this;
}

iterator iterator::operator++(int) // (int) denotes the decrement
{
    iterator tmp = *this;
    ++ptr_;
    return tmp;
}

char & iterator::operator*()
{
    return *ptr_;
}

bool iterator::operator==(const iterator& other) const
{
    return ptr_ == other.ptr_;
}

bool iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

iterator iterator::operator+(int n) const
{
   iterator it = *this;
   it.ptr_ += n;
   return it;
}

iterator iterator::operator-(int n) const
{
   iterator it = *this;
   it.ptr_ -= n;
   return it;
}

iterator & iterator::operator+=(int n)
{
    ptr_ += n;
    return *this;
}

iterator & iterator::operator-=(int n)
{
    ptr_ -= n;
    return *this;
}

// const_iterator //////////////////////////////////////////

const_iterator::const_iterator(char* ptr)
    : ptr_(ptr)
{
}

const_iterator & const_iterator::operator++()
{
    ++ptr_;
    return *this;
}

const_iterator const_iterator::operator++(int) // (int) denotes the decrement
{
    const_iterator tmp = *this;
    ++ptr_;
    return tmp;
}

const char & const_iterator::operator*()
{
    return *ptr_;
}

bool const_iterator::operator==(const const_iterator& other) const
{
    return ptr_ == other.ptr_;
}

bool const_iterator::operator!=(const const_iterator& other) const
{
    return !(*this == other);
}

const_iterator const_iterator::operator+(int n) const
{
   const_iterator it = *this;
   it.ptr_ += n;
   return it;
}

const_iterator const_iterator::operator-(int n) const
{
   const_iterator it = *this;
   it.ptr_ -= n;
   return it;
}

const_iterator & const_iterator::operator+=(int n)
{
    ptr_ += n;
    return *this;
}

const_iterator & const_iterator::operator-=(int n)
{
    ptr_ -= n;
    return *this;
}

// reverse_iterator /////////////////////////////////////////////////////

reverse_iterator::reverse_iterator(char* ptr)
    : ptr_(ptr)
{
}

reverse_iterator& reverse_iterator::operator++()
{
    --ptr_;  // Move the pointer backward
    return *this;
}

reverse_iterator reverse_iterator::operator++(int)
{
    reverse_iterator tmp = *this;
    --ptr_;
    return tmp;
}

char& reverse_iterator::operator*()
{
    return *ptr_;
}

bool reverse_iterator::operator==(const reverse_iterator& other) const
{
    return ptr_ == other.ptr_;
}

bool reverse_iterator::operator!=(const reverse_iterator& other) const
{
    return !(*this == other);
}

reverse_iterator reverse_iterator::operator+(int n) const
{
    reverse_iterator it = *this;
    it.ptr_ -= n;
    return it;
}

reverse_iterator reverse_iterator::operator-(int n) const
{
    reverse_iterator it = *this;
    it.ptr_ += n;
    return it;
}

reverse_iterator & reverse_iterator::operator+=(int n)
{
    ptr_ -= n;
    return *this;
}

reverse_iterator & reverse_iterator::operator-=(int n)
{
    ptr_ += n;
    return *this;
}

// const_reverse_iterator /////////////////////////////////////////////////////

const_reverse_iterator::const_reverse_iterator(char* ptr)
    : ptr_(ptr)
{
}

const_reverse_iterator & const_reverse_iterator::operator++()
{
    --ptr_;  // Move the pointer backward
    return *this;
}

const_reverse_iterator const_reverse_iterator::operator++(int)
{
    const_reverse_iterator tmp = *this;
    --ptr_;
    return tmp;
}

const char& const_reverse_iterator::operator*()
{
    return *ptr_;
}

bool const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return ptr_ == other.ptr_;
}

bool const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return !(*this == other);
}

const_reverse_iterator const_reverse_iterator::operator+(int n) const
{
    const_reverse_iterator it = *this;
    it.ptr_ -= n;
    return it;
}

const_reverse_iterator const_reverse_iterator::operator-(int n) const
{
    const_reverse_iterator it = *this;
    it.ptr_ += n;
    return it;
}

const_reverse_iterator & const_reverse_iterator::operator+=(int n)
{
    ptr_ -= n;
    return *this;
}

const_reverse_iterator & const_reverse_iterator::operator-=(int n)
{
    ptr_ += n;
    return *this;
}

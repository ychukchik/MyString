#ifndef ITERATORS_H
#define ITERATORS_H

class iterator
{
    friend class MyString;
private:
    char* ptr_;
public:

    iterator(char* ptr);

    iterator & operator++();
    iterator operator++(int);
    char & operator*();
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator operator+(int n) const;
    iterator operator-(int n) const;
    iterator & operator+=(int n);
    iterator & operator-=(int n);
};

class const_iterator
{
    friend class MyString;
private:
    char* ptr_;
public:

    const_iterator(char* ptr);

    const_iterator & operator++();
    const_iterator operator++(int);
    const char & operator*();
    bool operator==(const const_iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    const_iterator operator+(int n) const;
    const_iterator operator-(int n) const;
    const_iterator & operator+=(int n);
    const_iterator & operator-=(int n);
};

class reverse_iterator
{
    friend class MyString;
private:
    char* ptr_;
public:
    reverse_iterator(char* ptr);

    reverse_iterator & operator++();
    reverse_iterator operator++(int);
    char & operator*();
    bool operator==(const reverse_iterator& other) const;
    bool operator!=(const reverse_iterator& other) const;
    reverse_iterator operator+(int n) const;
    reverse_iterator operator-(int n) const;
    reverse_iterator & operator+=(int n);
    reverse_iterator & operator-=(int n);
};

class const_reverse_iterator
{
    friend class MyString;
private:
    char* ptr_;
public:
    const_reverse_iterator(char* ptr);

    const_reverse_iterator & operator++();
    const_reverse_iterator operator++(int);
    const char& operator*();
    bool operator==(const const_reverse_iterator& other) const;
    bool operator!=(const const_reverse_iterator& other) const;
    const_reverse_iterator operator+(int n) const;
    const_reverse_iterator operator-(int n) const;
    const_reverse_iterator & operator+=(int n);
    const_reverse_iterator & operator-=(int n);
};

#endif // ITERATORS_H

#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

class AhoCorasick;

class MyIterator;
class iterator;
class const_iterator;
class reverse_iterator;
class const_reverse_iterator;

template <typename T>
struct IsValidType : std::false_type {};

template <>
struct IsValidType<iterator> : std::true_type {};
template <>
struct IsValidType<reverse_iterator> : std::true_type {};

class MyString
{
private:
    char* str_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    // The functions below are internal (auxiliary) for operators.
    // I put them in private so that only member-function can use them
    void CreateCopyArray(const char* arr, size_t str_size);                   // for constructors
    void OperatorAssignment(const char* arr, size_t arr_size);                // for operator=
    void OperatorConcatenate(MyString& ob, const char* arr, size_t str_size); // for operator+
public:

    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    const_reverse_iterator rcbegin() const;
    const_reverse_iterator rcend() const;

    MyString();
    MyString(const char* arr);
    MyString(std::initializer_list<char> il);
    MyString(const std::string& arr);
    MyString(const char* arr, size_t count);
    MyString(size_t count, char ch);
    MyString(const MyString& arr);
    MyString(MyString&& ob);
    MyString(int val);
    MyString(float floatValue);

    MyString & operator=(const MyString& ob);
    MyString & operator=(const char* arr);
    MyString & operator=(const std::string& arr);
    MyString & operator=(const char ch);
    MyString & operator=(MyString&& ob);

    MyString operator+(const MyString& ob);
    MyString operator+(const char* arr);
    MyString operator+(const std::string& arr);    

    MyString & operator+=(const char* arr);
    MyString & operator+=(const std::string& arr);    

    char & operator[](size_t index) const;
    const char & operator[](size_t index);

    char & operator[](iterator position) const;
    const char & operator[](iterator position);
    const char & operator[](const_iterator position);
    char & operator[](reverse_iterator position) const;
    const char & operator[](reverse_iterator position);
    const char & operator[](const_reverse_iterator position);

    bool operator>(const MyString& other)  const;
    bool operator<(const MyString& other)  const;
    bool operator>=(const MyString& other) const;
    bool operator<=(const MyString& other) const;
    bool operator!=(const MyString& other) const;
    bool operator==(const MyString& other) const;

    const char* c_str() const;
    const char* data() const;
    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    bool empty() const;
    void clear();
    void shrink_to_fit();
    char at(size_t index) const;
    long long int to_int() const;
    float to_float() const;

    char at(iterator position) const;
    char at(const_iterator position) const;
    char at(reverse_iterator position) const;
    char at(const_reverse_iterator position) const;

    friend std::ostream & operator<<(std::ostream& s, const MyString& ob);
    friend std::istream & operator>>(std::istream& s, MyString& ob);
    friend std::basic_ofstream<char>& operator<<(std::basic_ofstream<char>& file, const MyString& str);
    friend std::basic_ifstream<char>& operator>>(std::basic_ifstream<char>& file, MyString& str);

    void insert(size_t index, size_t count, char ch);
    void insert(size_t index, const char* str);
    void insert(size_t index, const char* str, size_t count);
    void insert(size_t index, const std::string& arr);
    void insert(size_t index, const std::string& arr, size_t count);
    void insert(size_t index, const MyString& inserted);

    void insert(iterator position, size_t count, char ch);
    void insert(iterator position, const char* str);
    void insert(iterator position, const char* str, size_t count);
    void insert(iterator position, const std::string& arr);
    void insert(iterator position, const std::string& arr, size_t count);
    void insert(iterator position, const MyString& inserted);

    void insert(reverse_iterator position, size_t count, char ch);
    void insert(reverse_iterator position, const char* str);
    void insert(reverse_iterator position, const char* str, size_t count);
    void insert(reverse_iterator position, const std::string& arr);
    void insert(reverse_iterator position, const std::string& arr, size_t count);
    void insert(reverse_iterator position, const MyString& inserted);

    void erase(size_t index, size_t count);

    void erase(iterator position, size_t count);
    void erase(reverse_iterator position, size_t count);

    void append(size_t count, char ch);
    void append(const char* str);
    void append(const char* str, size_t index, size_t count);
    void append(const std::string& arr);
    void append(const std::string& arr, size_t index, size_t count);

    void append(const char* str, iterator position, size_t count);
    void append(const std::string& arr, iterator position, size_t count);
    void append(const char* str, reverse_iterator position, size_t count);
    void append(const std::string& arr, reverse_iterator position, size_t count);

    void replace(size_t index, size_t count, const char* new_str);
    void replace(size_t index, size_t count, const std::string& arr);

    void replace(iterator position, size_t count, const char* new_str);
    void replace(iterator position, size_t count, const std::string& arr);
    void replace(reverse_iterator position, size_t count, const char* new_str);
    void replace(reverse_iterator position, size_t count, const std::string& arr);

    MyString substr(size_t index) const;
    MyString substr(size_t index, size_t count) const;

    MyString substr(iterator position) const;
    MyString substr(iterator position, size_t count) const;
    MyString substr(const_iterator position) const;
    MyString substr(const_iterator position, size_t count) const;
    MyString substr(reverse_iterator position) const;
    MyString substr(reverse_iterator position, size_t count) const;
    MyString substr(const_reverse_iterator position) const;
    MyString substr(const_reverse_iterator position, size_t count) const;

    size_t find(const char* substr) const;
    size_t find(const char* substr, size_t index) const;
    size_t find(const std::string& arr) const;
    size_t find(const std::string& arr, size_t index) const;
    std::vector<std::pair<size_t, size_t>> find(const AhoCorasick& ahoCorasick) const;

    size_t find(const char* substr, iterator position) const;
    size_t find(const std::string& arr, iterator position) const;
    size_t find(const char* substr, const_iterator position) const;
    size_t find(const std::string& arr, const_iterator position) const;
    size_t find(const char* substr, reverse_iterator position) const;
    size_t find(const std::string& arr, reverse_iterator position) const;
    size_t find(const char* substr, const_reverse_iterator position) const;
    size_t find(const std::string& arr, const_reverse_iterator position) const;

    void PrintString();

    ~MyString();
};

#endif // MYSTRING_H

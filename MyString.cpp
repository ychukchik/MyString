#include "MyString.h"
#include "AhoCorasick.h"
#include "Iterators.h"

// CONSTRUCTIONS ////////////////////////////////////////////////////////////////////

MyString::MyString() //default constructor
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

MyString::MyString(const char* arr) // char array constructor
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (arr)
    {
        capacity_ = strlen(arr) + 1;
        str_ = new char[capacity_];
        strcpy_s(str_, capacity_, arr);
        size_ = capacity_ - 1;
    }
}

MyString::MyString(std::initializer_list<char> il) // initializer list constructor
    : size_(il.size()), capacity_(size_ + 1)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (il.size())
    {
        str_ = new char[capacity_];
        size_t i = 0;
        for (char ch : il)
        {
            str_[i++] = ch;
        }
        str_[i] = '\0';
    }
    // no else. str_ == nullptr, size_ == capacity_ == 0
}

MyString::MyString(const std::string& arr) // std::string constructor
    : size_(arr.length()), capacity_(size_ + 1)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    CreateCopyArray(arr.c_str(), capacity_);
}

MyString::MyString(const char* arr, size_t count) // init class with count characters of  “char string”
    : size_(count), capacity_(count + 1)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    str_ = new char[capacity_];
    strncpy(str_, arr, size_);
    str_[size_] = '\0';
}

MyString::MyString(size_t count, char ch) // init class with count of characters
    : size_(count), capacity_(count + 1)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    str_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
        str_[i] = ch;
    }
    str_[count] = '\0';
}

MyString::MyString(const MyString& ob) // copy constructor
    : size_(ob.size_), capacity_(ob.capacity_)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (ob.str_)
    {
        CreateCopyArray(ob.str_, ob.capacity_);
    }
}

void MyString::CreateCopyArray(const char* arr, size_t str_size)
{
    str_ = new char[str_size];
    strcpy_s(str_, capacity_, arr);
}

MyString::~MyString()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    clear();
}

// OPERATORS ////////////////////////////////////////////////////////////////////

// CONCATENATE ------------------------------------------------------------------

MyString MyString::operator+(const MyString& ob) // concatenate with Mystring
{
    MyString res;
    OperatorConcatenate(res, ob.str_, ob.size_);
    return res;
}

MyString MyString::operator+(const char* arr) // concatenate with char array
{
    MyString res;
    OperatorConcatenate(res, arr, strlen(arr));
    return res;
}

MyString MyString::operator+(const std::string& arr) // concatenate with std::string
{
    MyString res;
    OperatorConcatenate(res, arr.c_str(), arr.size());
    return res;
}

void MyString::OperatorConcatenate(MyString& ob, const char* arr, size_t str_size)
{
    ob.size_ = size_ + str_size; // the length of the str_ consists of the old length and the length of the added array/string/object
    ob.capacity_ = ob.size_ + 1;
    ob.str_ = new char[ob.capacity_];
    if (str_)
        strncpy(ob.str_, str_, capacity_);
    else
        ob.str_[0] = '\0';
    strncat(ob.str_, arr, str_size);
    ob.str_[ob.size_] = '\0';
}

// CONCATENATE WITH ASSIGNMENT ----------------------------------------------------------

//MyString & MyString::operator+=(const char* arr) утечка памяти
//{
//    *this = *this + MyString(arr);
//    return *this;
//}

MyString & MyString::operator+=(const char* arr)
{
    if (arr)
    {
        size_t arr_size = strlen(arr);
        size_t new_size = size_ + arr_size;
        if (new_size >= capacity_)
        {
            // Expand the buffer if it's not large enough
            size_t new_capacity = new_size + 1;
            char* new_str = new char[new_capacity];

            // Copy the existing string to the new buffer
            if (str_ != nullptr) {
                strncpy(new_str, str_, size_);
            }
            new_str[size_] = '\0';

            // Concatenate the new string to the end
            strncat(new_str, arr, arr_size);
            new_str[new_capacity - 1] = '\0';

            // Clear the old data, update size and capacity, and assign the new buffer
            clear();
            size_ = new_capacity - 1;
            capacity_ = new_capacity;
            str_ = new_str;
        }
        else
        {
            // If there's enough space, simply concatenate the new string
            strncat(str_, arr, arr_size);
            size_ = new_size;
        }
    }
    return *this;
}

MyString & MyString::operator+=(const std::string& arr)
{
    return *this += arr.c_str();
}

// ASSIGNMENT ---------------------------------------------------------------------------

MyString & MyString::operator=(const MyString& ob) // copy assignment
{
    // we must handle the case &ob == this (when an object assigns itself), otherwise in the
    // function OperatorAssignment() memory will be cleared in str_.
    if (&ob == this) // checking the equality of addresses
        return *this;
    OperatorAssignment(ob.str_, ob.size_);
    return *this;
}

MyString & MyString::operator=(const char* arr) // char string assignment
{
    if (arr)
        OperatorAssignment(arr, strlen(arr));
    else
    {
        str_[0] = '\0';
        size_ = 0;
    }
    return *this;
}

MyString & MyString::operator=(const std::string& arr) // std::string assignment
{
    OperatorAssignment(arr.c_str(), arr.size());
    return *this;
}

MyString & MyString::operator=(const char ch) // char assignment
{
//    OperatorAssignment(ch, 1); we can't use it since it's a symbol

    if (capacity_ <= 1) // there is no memory for the symbol. need to reallocate
    {
        clear();
        str_ = new char[2]; // we allocate memory only for the symbol
        capacity_ = 2;
    } // otherwise, capacity_ remains the same, and we just add a character and end the string
    str_[0] = ch;
    str_[1] = '\0';
    size_ = 1;
    return *this;
}

void MyString::OperatorAssignment(const char* arr, size_t arr_size)
{
    if (capacity_ > arr_size)   // if there is enough free space, we do not reallocate the memory, just clear the array
        str_[0] = '\0';
    else                        // otherwise, we delete everything and reallocate memory
    {
        clear();
        capacity_ = arr_size + 1;
        str_ = new char[capacity_];
    }
    strcpy_s(str_, capacity_, arr);
    size_ = arr_size;
}

// INDEX ---------------------------------------------------------------------------

char & MyString::operator[](size_t index) const // const index operator
{
    //std::cout << "const operator[]" << std::endl; // for debugging. you can check that this particular operator is being called
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

const char & MyString::operator[](size_t index)       // index operator
{
    //std::cout << "not const operator[]" << std::endl;
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

// LEXICOGRAPHICALLY COMPARING ------------------------------------------------------

bool MyString::operator>(const MyString& ob) const
{
    return strcmp(str_, ob.str_) > 0;
}

bool MyString::operator<(const MyString& ob) const
{
    return strcmp(str_, ob.str_) < 0;
}

bool MyString::operator>=(const MyString& ob) const
{
    return !(*this < ob);
}

bool MyString::operator<=(const MyString& ob) const
{
    return !(*this > ob);
}

bool MyString::operator==(const MyString& ob) const
{
    return strcmp(str_, ob.str_) == 0;
}

bool MyString::operator!=(const MyString& ob) const
{
    return !(*this == ob);
}

// OTHER OPERATORS ------------------------------------------------------

const char* MyString::c_str() const // return a pointer to null-terminated character array
{
    return str_;
}

const char* MyString::data() const // return a pointer to array data that not required to be null-terminated
{

    return str_;
}

size_t MyString::size() const // return the number of char elements in string
{
    return size_;
}

size_t MyString::length() const // same as size
{
    return size_;
}

size_t MyString::capacity() const // return the current amount of allocated memory for array
{
    return capacity_;
}

bool MyString::empty() const // true if string is empty
{
    return (!str_);
}

void MyString::clear() // remove all char element in string
{
    if (str_)
    {
        delete[] str_;
        str_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
}

void MyString::shrink_to_fit() // reduce the capacity to size
{
    if (capacity_ - size_ > 1)
    {
        size_t tmp_size_ = size_;
        char* tmp_str_ = new char[tmp_size_ + 1];
        strcpy_s(tmp_str_, capacity_, str_);
        clear();
        capacity_ = tmp_size_ + 1;
        CreateCopyArray(tmp_str_, capacity_);
        size_ = tmp_size_;
        delete[] tmp_str_;
    }
}

std::ostream & operator<<(std::ostream &s, const MyString &ob)
{
    if (ob.str_)
        s << ob.str_;
    else
        s << "{null}";
    return s;
}

std::istream & operator>>(std::istream& s, MyString& ob)
{
    const int bufferSize = 1024;
    char* buffer = new char[bufferSize];

    if (s.getline(buffer, bufferSize)) {
        ob = buffer;
    }

    return s;
}

// INSERT ////////////////////////////////////////////////////////////////////

void MyString::insert(size_t index, size_t count, char ch)
{
    if (index > size_ || count == 0) throw std::out_of_range("index out of range");

    MyString inserted(count, ch);
    insert(index, inserted);
}

void MyString::insert(size_t index, const char* str)
{
    if (index > size_) throw std::out_of_range("index out of range");
    else if (!str)throw std::out_of_range("str == nullptr");

    MyString inserted(str);
    insert(index, inserted);
}

void MyString::insert(size_t index, const char* str, size_t count)
{
    if (index > size_) throw std::out_of_range("index out of range");
    else if (!str)throw std::out_of_range("str == nullptr");

    MyString inserted(str, count);
    insert(index, inserted);
}

void MyString::insert(size_t index, const std::string& arr)
{
    if (index > size_) throw std::out_of_range("index out of range");

    MyString inserted(arr);
    insert(index, inserted);
}

void MyString::insert(size_t index, const std::string& arr, size_t count)
{
    if (index > size_) throw std::out_of_range("index out of range");

    MyString inserted(arr.substr(0, count));
    insert(index, inserted);
}

void MyString::insert(size_t index, const MyString& inserted)
{
    if (index > size_) throw std::out_of_range("index out of range");

    size_t new_size = size_ + inserted.size();

    // Need to increase the capacity
    if (new_size >= capacity_)
    {
        size_t new_capacity = new_size + 1;
        char* new_str = new char[new_capacity];

        // Copy the data to the insertion position
        strncpy(new_str, str_, index);

        // Copy the inserted line
        strncpy(new_str + index, inserted.c_str(), inserted.size());

        // Copy the rest of the data after insertion
        strncpy(new_str + index + inserted.size(), str_ + index, size_ - index);

        new_str[new_capacity - 1] = '\0';

        // Release the current memory and update
        clear();
        size_ = new_size;
        capacity_ = new_capacity;
        str_ = new_str;
    }
    else
    {
        // Shift the characters to the right to make room for insertion
        for (size_t i = size_; i >= index; --i)
        {
            str_[i + inserted.size()] = str_[i];
        }

        // Inserting a line into the current line
        for (size_t i = 0; i < inserted.size(); ++i)
        {
            str_[index + i] = inserted[i];
        }

        size_ = new_size;
    }
}


// ERASE ////////////////////////////////////////////////////////////////////

void MyString::erase(size_t index, size_t count) // erase count of char at index position
{
    if (index < size_)
    {
        size_t chars_to_erase = std::min(count, size_ - index); // Determine the number of characters that we will delete
        for (size_t i = index; i < size_ - chars_to_erase; ++i)
        {
            str_[i] = str_[i + chars_to_erase]; // Shift the characters to the left by the number of characters to be deleted
        }
        size_ -= chars_to_erase;
        str_[size_] = '\0';
    }
    else
        throw std::out_of_range("index out of range");
}

// APPEND ////////////////////////////////////////////////////////////////////

void MyString::append(size_t count, char ch)
{
    *this = *this + MyString(count, ch);
}

void MyString::append(const char* str)
{
    *this = *this + MyString(str);
}

void MyString::append(const char* str, size_t index, size_t count)
{
    *this = *this + MyString(str + index, count);
}

void MyString::append(const std::string& arr)
{
    *this = *this + MyString(arr);
}

void MyString::append(const std::string& arr, size_t index, size_t count)
{
    *this = *this + MyString(arr.substr(index, count));
}


// REPLACE ////////////////////////////////////////////////////////////////////

void MyString::replace(size_t index, size_t count, const char* str) // replace a count of char at index by “string”
{
//    MultiReplace(index, count, str);
    if (str && index < size_)
    {
        //count = std::min(count, size_ - index); // Limit the value of count so as not to go beyond the line

        if(count + index >= size_)
            throw std::out_of_range("count + index out of range");

        size_t str_len = strlen(str);
        size_t new_str_len = size_ - count + str_len;
        char* new_str = new char[new_str_len + 1];

        // Copy the part of the string to the index that needs to be replaced
        strncpy(new_str, str_, index);
        new_str[index] = '\0';

        // Copy a new line
        strncpy(new_str + index, str, str_len);

        // Copy the rest of the original line
        strncpy(new_str + index + str_len, str_ + index + count, size_ - index - count);
        new_str[new_str_len] = '\0';

        // Free the old memory and update the data
        clear();
        size_ = new_str_len;
        capacity_ = new_str_len + 1;
        CreateCopyArray(new_str, new_str_len);
        delete[] new_str;
    }
}

void MyString::replace(size_t index, size_t count, const std::string& arr) // replace a count of char at index by std::string
{
    replace(index, count, arr.c_str());
}

// SUBSTR ////////////////////////////////////////////////////////////////////

MyString MyString::substr(size_t index) const // return a substring starts with index position
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    return MyString(str_ + index); // Returning a new MyString starting from the given position
}

MyString MyString::substr(size_t index, size_t count) const // return a count of substring’s char starts with index position
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    // We limit the value of count so as not to go beyond the line
    count = std::min(count, size_ - index);

    return MyString(str_ + index, count); // Returning a new MyString starting from a given position of a given count
}

// FIND //////////////////////////////////////////////////////////////////////

size_t MyString::find(const char* substr) const
{
    return find(substr, 0);
}

size_t MyString::find(const char* substr, size_t index) const
{
    if (substr == nullptr || index >= size_)
    {
        throw std::out_of_range("substr == nullptr || index >= size_");
    }

    const char* result = std::strstr(str_ + index, substr); // Looking for a substring starting from a given position

    if (result == nullptr)
    {
        throw std::out_of_range("result == nullptr");
    }

    return result - str_; // Calculate the index of the first character of the found substring
}

size_t MyString::find(const std::string& arr) const
{
    return find(arr.c_str(), 0);
}

size_t MyString::find(const std::string& arr, size_t index) const
{
    return find(arr.c_str(), index);
}

// PRINT ALL ///////////////////////////////////////////////////////////////////////////////////////////////////////

void MyString::PrintString()
{
    if (str_)
        std::cout << str_ << " (size = " << size() << ", capacity = " << capacity() << ")" << std::endl << std::endl;
    else
        std::cout << "{null}" << " (size = " << size() << ", capacity = " << capacity() << ")" << std::endl << std::endl;
}

// ADDITIONAL FUNCTIONALITY ////////////////////////////////////////////////////////////////////////////////////////

MyString::MyString(MyString&& ob) // move constructor
    : str_(ob.str_), size_(ob.size_), capacity_(ob.capacity_)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ob.size_ = 0;
    ob.capacity_ = 0;
    ob.str_ = nullptr;
}

MyString & MyString::operator=(MyString&& ob) // move assignment
{
    // we must handle the case &ob == this (when an object assigns itself), otherwise in the
    // function OperatorAssignment() memory will be cleared in str_.
    if (&ob != this)
    {
        // Releasing current resources
        clear();

        // Transferring resources from ob to the current object
        size_ = ob.size_;
        capacity_ = ob.capacity_;
        str_ = ob.str_;

        // Clearing ob
        ob.size_ = 0;
        ob.capacity_ = 0;
        ob.str_ = nullptr;
    }
    return *this;
}

MyString::MyString(int hex_val) // conversion constructor for integer types
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    int requiredSize = snprintf(nullptr, 0, "0x%X", hex_val); // Determine the size of the string required to represent the number in hexadecimal form

    capacity_ = requiredSize + 1; // Allocate memory for the line
    str_ = new char[capacity_];

    snprintf(str_, capacity_, "0x%X", hex_val); // Convert an integer to a string in hexadecimal form and store it in the myString object

    size_ = requiredSize;
}

MyString::MyString(float floatValue) // conversion constructor for float types
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    int requiredSize = snprintf(nullptr, 0, "%f", floatValue);

    capacity_ = requiredSize + 1;
    str_ = new char[capacity_];

    snprintf(str_, capacity_, "%f", floatValue);

    size_ = requiredSize;
}

std::basic_ofstream<char>& operator<<(std::basic_ofstream<char>& file, const MyString& str) // The operator for writing a myString object to a file
{
    if (str.size_ > 0 && str.str_)
    {
        file.write(str.str_, str.size_);
    }
    return file;
}

std::basic_ifstream<char>& operator>>(std::basic_ifstream<char>& file, MyString& str) // Operator for reading a myString object from a file
{
    // Determine the maximum size of the buffer to read
    const size_t maxBufferSize = 4096;
    char buffer[maxBufferSize];

    str.clear();

    // Read the data from the file and add it to the myString string
    while (file)
    {
        file.read(buffer, maxBufferSize);
        size_t bytesRead = static_cast<size_t>(file.gcount());
        if (bytesRead > 0)
        {
            str.append(buffer);
        }
    }

    return file;
}

char MyString::at(size_t index) const // return the index element of string if exist, otherwise throw an exception
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return str_[index];
}

long long int MyString::to_int() const // perform conversion from string to integer types: char, short,int an other
{
    for (size_t i = 0; i < size_; ++i)
    {
        if (!isdigit(str_[i]))
            throw std::out_of_range("!isdigit(str_[i])");
    }
    return std::stoi(str_);
}

float MyString::to_float() const
{
    // Pointer to the character that ends the parsing
    char* endptr;

    // Use strtof to parse the string as a floating-point number
    float result = strtof(str_, &endptr);

    // Check for parsing errors
    if (*endptr != '\0')
    {
        throw std::invalid_argument("Invalid float conversion");
    }

    return result;
}

std::vector<std::pair<size_t, size_t>> MyString::find(const AhoCorasick& ahoCorasick) const
{
    return ahoCorasick.FindKeywords(*this);
}

// ITERATORS //////////////////////////////////////////////////////////////////////////////////////////////////////

// iterator -------------------------------------------------------------------------------------------------------

iterator MyString::begin() const
{
    return iterator(str_);
}

iterator MyString::end() const
{
    return iterator(str_ + size_);
}

void MyString::insert(iterator position, size_t count, char ch)
{
    MyString inserted(count, ch);
    insert(position, inserted);
}

void MyString::insert(iterator position, const char* str)
{
    MyString inserted(str);
    insert(position, inserted);
}

void MyString::insert(iterator position, const char* str, size_t count)
{
    MyString inserted(str, count);
    insert(position, inserted);
}

void MyString::insert(iterator position, const std::string& arr)
{
    MyString inserted(arr);
    insert(position, inserted);
}

void MyString::insert(iterator position, const std::string& arr, size_t count)
{
    MyString inserted(arr.substr(0, count));
    insert(position, inserted);
}

void MyString::insert(iterator position, const MyString& inserted)
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }
    size_t insert_size = inserted.size();
    size_t new_size = size_ + insert_size;

    // Need to increase the capacity
    if (new_size >= capacity_)
    {
        size_t new_capacity = new_size + 1;
        char* new_str = new char[new_capacity];

        // Copy the data to the insertion position
        std::copy(str_, position.ptr_, new_str);

        // Copy the inserted line
        std::copy(inserted.str_, inserted.str_ + insert_size, new_str + (position.ptr_ - str_));

        // Copy the rest of the data after insertion
        std::copy(position.ptr_, str_ + size_, new_str + (position.ptr_ - str_) + insert_size);

        // Release the current memory and update
        clear();
        size_ = new_size;
        capacity_ = new_capacity;
        str_ = new_str;
    }
    else
    {
        // If there is enough memory, just insert
        std::copy_backward(position.ptr_, str_ + size_, str_ + new_size);
        std::copy(inserted.str_, inserted.str_ + insert_size, position.ptr_);
        size_ = new_size;
    }
}

void MyString::erase(iterator position, size_t count)
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }
    if (position != end())
    {
        iterator i_start = position;
        iterator i_end = position;

        for (size_t i = 0; i < count && i_end != end(); ++i)
        {
            ++i_end;
        }

        while (i_end != end())
        {
            *i_start = *i_end;
            ++i_start;
            ++i_end;
        }
        size_ -= count;
        str_[size_] = '\0';
    }
    else
    {
        throw std::out_of_range("Iterator out of range");
    }
}

void MyString::append(const char* str, iterator position, size_t count)
{
    if (count == 0) return;
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t insertPos = position.ptr_ - str_;
    insert(insertPos, str, count);
}

void MyString::append(const std::string& arr, iterator position, size_t count)
{
    append(arr.c_str(), position, count);
}

void MyString::replace(iterator position, size_t count, const char* new_str)
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t replacePos = position.ptr_ - str_;

    erase(position, count);
    insert(begin() + replacePos, new_str);
}

void MyString::replace(iterator position, size_t count, const std::string& arr)
{
    replace(position, count, arr.c_str());
}

MyString MyString::substr(iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t start = position.ptr_ - str_;
    size_t sub_size = size_ - start;

    return MyString(str_ + start, sub_size);
}

MyString MyString::substr(iterator position, size_t count) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t start = position.ptr_ - str_;
    size_t substringSize = std::min(count, size_ - start);

    return MyString(str_ + start, substringSize);
}

size_t MyString::find(const char* substr, iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    // Start the search from the position specified by the iterator
    const char* result = std::strstr(position.ptr_, substr);

    if (result == nullptr)
    {
        throw std::out_of_range("result == nullptr");
    }

    return result - str_; // Return the index of the first character of the found substring
}

size_t MyString::find(const std::string& arr, iterator position) const
{
    return find(arr.c_str(), position);
}

char MyString::at(iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ >= str_ + size_)
    {
        throw std::out_of_range("Iterator position is out of range");
    }
    return *position;
}

char & MyString::operator[](iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ >= str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }
    return *position;
}

const char & MyString::operator[](iterator position)
{
    if (position.ptr_ < str_ || position.ptr_ >= str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }
    return *position;
}

// const_iterator -------------------------------------------------------------------------------------------------------

const_iterator MyString::cbegin() const
{
    return const_iterator(str_);
}

const_iterator MyString::cend() const
{
    return const_iterator(str_ + size_);
}

const char & MyString::operator[](const_iterator position)
{
    if (position.ptr_ < str_ || position.ptr_ >= str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }
    return *position;
}

MyString MyString::substr(const_iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t start = position.ptr_ - str_;
    size_t sub_size = size_ - start;

    return MyString(str_ + start, sub_size);
}

MyString MyString::substr(const_iterator position, size_t count) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t start = position.ptr_ - str_;
    size_t substringSize = std::min(count, size_ - start);

    return MyString(str_ + start, substringSize);
}

size_t MyString::find(const char* substr, const_iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    // Start the search from the position specified by the iterator
    const char* result = std::strstr(position.ptr_, substr);

    if (result == nullptr)
    {
        throw std::out_of_range("result == nullptr");
    }

    return result - str_; // Return the index of the first character of the found substring
}

size_t MyString::find(const std::string& arr, const_iterator position) const
{
    return find(arr.c_str(), position);
}

char MyString::at(const_iterator position) const
{
    if (position.ptr_ < str_ || position.ptr_ >= str_ + size_)
    {
        throw std::out_of_range("Iterator position is out of range");
    }
    return *position;
}

// reverse_iterator -------------------------------------------------------------------------------------------------------

reverse_iterator MyString::rbegin() const
{
    return reverse_iterator(str_ + size_);
}

reverse_iterator MyString::rend() const
{
    return reverse_iterator(str_);
}

void MyString::insert(reverse_iterator position, size_t count, char ch)
{
    MyString inserted(count, ch);
    insert(position, inserted);
}

void MyString::insert(reverse_iterator position, const char* str)
{
    MyString inserted(str);
    insert(position, inserted);
}

void MyString::insert(reverse_iterator position, const char* str, size_t count)
{
    MyString inserted(str, count);
    insert(position, inserted);
}

void MyString::insert(reverse_iterator position, const std::string& arr)
{
    MyString inserted(arr);
    insert(position, inserted);
}

void MyString::insert(reverse_iterator position, const std::string& arr, size_t count)
{
    MyString inserted(arr.substr(0, count));
    insert(position, inserted);
}

void MyString::insert(reverse_iterator position, const MyString& inserted)
{
    size_t insertPos = position.ptr_ - str_;

    if (insertPos > size_)
    {
        throw std::out_of_range("Insert position out of range.");
    }

    size_t new_size = size_ + inserted.size_;

    if (new_size >= capacity_)
    {
        size_t new_capacity = std::max(new_size + 1, 2 * capacity_);
        char* new_str = new char[new_capacity];

        // Copy the data before the insertion point
        strncpy(new_str, str_, insertPos);

        // Copy the inserted string
        strncpy(new_str + insertPos, inserted.str_, inserted.size_);

        // Copy the rest of the data after insertion
        strncpy(new_str + insertPos + inserted.size_, str_ + insertPos, size_ - insertPos + 1);

        // Release the current memory and update
        clear();
        size_ = new_size;
        capacity_ = new_capacity;
        str_ = new_str;
    }
    else
    {
        // Shift the characters to the right to make room for insertion
        for (size_t i = size_; i >= insertPos; --i)
        {
            str_[i + inserted.size_] = str_[i];
        }

        // Insert the string into the current string
        for (size_t i = 0; i < inserted.size_; ++i)
        {
            str_[insertPos + i] = inserted.str_[i];
        }

        size_ = new_size;
    }
}

void MyString::erase(reverse_iterator position, size_t count)
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position
    if (index <= size_)
    {
        size_t chars_to_erase = std::min(count, size_ - index);
        for (size_t i = index + chars_to_erase; i <= size_; ++i)
        {
            str_[i - chars_to_erase] = str_[i];
        }
        size_ -= chars_to_erase;
        str_[size_] = '\0';
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

void MyString::append(const char* str, reverse_iterator position, size_t count)
{
    if (count == 0) return;
    if (position.ptr_ < str_ || position.ptr_ > str_ + size_)
    {
        throw std::out_of_range("Invalid iterator position");
    }

    size_t insertPos = position.ptr_ - str_;
    insert(insertPos, str, count);
}

void MyString::append(const std::string& str, reverse_iterator position, size_t count)
{
    append(str.c_str(), position, count);
}

void MyString::replace(reverse_iterator position, size_t count, const char* new_str)
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        size_t chars_to_replace = std::min(count, size_ - index);
        size_t new_str_length = strlen(new_str);
        size_t size_difference = new_str_length - chars_to_replace;

        if (size_ + size_difference >= capacity_)
        {
            // If the capacity is not sufficient, reallocate memory
            size_t new_capacity = size_ + size_difference + 1;
            char* new_buffer = new char[new_capacity];

            // Copy the characters before the replacement
            strncpy(new_buffer, str_, index);

            // Copy the new string
            strncpy(new_buffer + index, new_str, new_str_length);

            // Copy the characters after the replacement
            strncpy(new_buffer + index + new_str_length, str_ + index + chars_to_replace, size_ - index - chars_to_replace);

            // Clean up the old memory and update
            clear();
            size_ += size_difference;
            capacity_ = new_capacity;
            str_ = new_buffer;
        }
        else
        {
            // Shift the characters to the right if needed
            if (size_difference != 0)
            {
                for (size_t i = size_; i > index + chars_to_replace; --i)
                {
                    str_[i + size_difference] = str_[i];
                }
                size_ += size_difference;
            }

            // Copy the new string into the replaced position
            strncpy(str_ + index, new_str, new_str_length);
        }
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

void MyString::replace(reverse_iterator position, size_t count, const std::string& arr)
{
    replace(position, count, arr.c_str());
}

MyString MyString::substr(reverse_iterator position) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position

    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    return MyString(str_ + index);
}

MyString MyString::substr(reverse_iterator position, size_t count) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position

    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    // Limit the value of count to ensure it does not go beyond the string
    count = std::min(count, size_ - index);

    return MyString(str_ + index, count);
}

size_t MyString::find(const char* substr, reverse_iterator position) const
{
    // Calculate the starting index based on the reverse_iterator position
    size_t start_index = size_ - (position.ptr_ - str_);

    if (start_index < size_)
    {
        const char* result = strstr(str_ + start_index, substr);
        if (result)
        {
            // Calculate the actual position of the found substring in the original order
            return size_ - (result - str_);
        }
    }

    return std::string::npos; // Return npos if substring is not found
}

size_t MyString::find(const std::string& substr, reverse_iterator position) const
{
    return find(substr.c_str(), position);
}

char MyString::at(reverse_iterator position) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

char & MyString::operator[](reverse_iterator position) const
{
    size_t index = size_ - (position.ptr_ - str_ - 1); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

const char & MyString::operator[](reverse_iterator position)
{
    size_t index = size_ - (position.ptr_ - str_ - 1); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

// const_reverse_iterator -------------------------------------------------------------------------------------------------------

const_reverse_iterator MyString::rcbegin() const
{
    return const_reverse_iterator(str_ + size_);
}

const_reverse_iterator MyString::rcend() const
{
    return const_reverse_iterator(str_);
}

MyString MyString::substr(const_reverse_iterator position) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position

    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    return MyString(str_ + index);
}

MyString MyString::substr(const_reverse_iterator position, size_t count) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position

    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }

    // Limit the value of count to ensure it does not go beyond the string
    count = std::min(count, size_ - index);

    return MyString(str_ + index, count);
}

size_t MyString::find(const char* substr, const_reverse_iterator position) const
{
    // Calculate the starting index based on the reverse_iterator position
    size_t start_index = size_ - (position.ptr_ - str_);

    if (start_index < size_)
    {
        const char* result = strstr(str_ + start_index, substr);
        if (result)
        {
            // Calculate the actual position of the found substring in the original order
            return size_ - (result - str_);
        }
    }

    return std::string::npos; // Return npos if substring is not found
}

size_t MyString::find(const std::string& substr, const_reverse_iterator position) const
{
    return find(substr.c_str(), position);
}

char MyString::at(const_reverse_iterator position) const
{
    size_t index = size_ - (position.ptr_ - str_); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

const char & MyString::operator[](const_reverse_iterator position)
{
    size_t index = size_ - (position.ptr_ - str_ - 1); // Calculate the index based on the reverse_iterator position
    if (index < size_)
    {
        return str_[index];
    }
    else
    {
        throw std::out_of_range("index out of range");
    }
}

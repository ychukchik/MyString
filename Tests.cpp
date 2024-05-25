#include <iostream>

#include "Tests.h"
#include "MyString.h"
#include "MyException.h"
#include "AhoCorasick.h"
#include "Iterators.h"

static int tests_count = 0;
static int tests_failed = 0;

int safe_strcmp(const char* str1, const char* str2)
{
    if (str1 == nullptr && str2 == nullptr) return 0;
    else if (str1 == nullptr) return -1;
    else if (str2 == nullptr) return 1;

    return strcmp(str1, str2);
}

template <typename T>
void MyCompare(const T& actual, const T& expected)
{
    ++tests_count;
    if (actual != expected)
    {
        ++tests_failed;
        std::cout << "Comparison failed. Actual:" << actual << "Expected:" << expected << std::endl;
    }
}

void MyCompare(const MyString& str, const char* exp_str, size_t exp_size, size_t exp_capacity)
{
    ++tests_count;
    if (safe_strcmp(str.c_str(), exp_str) || str.size() != exp_size || str.capacity() != exp_capacity)
    {
        ++tests_failed;
        std::cout << "Comparison failed. Actual:   " << str.c_str() << " (size = " << str.size() << ", capacity = " << str.capacity() << ")"
                  << std::endl << "                   Expected: "<< exp_str << " (size = " << exp_size << ", capacity = " << exp_capacity << ")"
                  << std::endl << std::endl;
    }
}

void ResultTests()
{
    std::cout << "TEST RESULTS"   << std::endl;
    std::cout << "Total tests: "  << tests_count << std::endl;
    std::cout << "Tests failed: " << tests_failed << std::endl << std::endl;
}


void TestConstructors()
{
    // default constructor
    MyString str1;
    str1.PrintString();
    MyCompare(str1, (const char*)(nullptr), 0, 0);


    // char array constructor
    MyString str2("Hello, world");
    str2.PrintString();
    MyCompare(str2, (const char*)("Hell, world"), 12, 13);

    char arr1[] = "The cat (Felis catus), commonly referred to as the domestic cat or house cat, is the only domesticated species in the family Felidae. Recent advances in archaeology and genetics have shown that the domestication of theThe cat (Felis catus), commonly.The cat (Felis catus), commonly referred to as the domestic cat or house cat, is the only domesticated species in the family Felidae. Recent advances in archaeology and genetics have shown that the domestication of theThe cat (Felis catus), commonly.The cat (Felis catus), commonly referred to as the domestic cat or house cat, is the only domesticated species in the family Felidae. Recent advances in archaeology and genetics have shown that the domestication of theThe cat (Felis catus), commonly.";
    MyString str3(arr1);
    str3.PrintString();
    MyCompare(str3, (const char*)("Hi"), 2, 3);

    char* arr2 = nullptr;
    MyString str4(arr2);
    str4.PrintString();
    MyCompare(str4, (const char*)(nullptr), 0, 0);

    // initializer list constructor
    MyString str5({'A', 'p', 'p', 'l', 'e'});
    str5.PrintString();
    MyCompare(str5, (const char*)("Apple"), 5, 6);

    MyString str6({});
    str6.PrintString();
    MyCompare(str6, (const char*)(nullptr), 0, 1);

    // std::string constructor
    std::string arr3 = "Bananas";
    MyString str7(arr3);
    str7.PrintString();
    MyCompare(str7, (const char*)("Bananas"), 7, 8);

    // init class with count characters of  “char string”
    char arr4[] = "Orange juice";
    MyString str8(arr4, 4);
    str8.PrintString();
    MyCompare(str8, (const char*)("Oran"), 4, 5);

    char arr5[] = "Tomato";
    MyString str9(arr5, 0);
    str9.PrintString();
    MyCompare(str9, (const char*)(""), 0, 1);

    // init class with count of characters
    MyString str10(10, '#');
    str10.PrintString();
    MyCompare(str10, (const char*)("##########"), 10, 11);

    // copy constructor
    // default constructor ->
    MyString str11;
    MyString str12(str11);
    str11.PrintString();
    str12.PrintString();
    MyCompare(str11, (const char*)(nullptr), 0, 0);
    MyCompare(str12, (const char*)(nullptr), 0, 0);

    // char array constructor ->
    MyString str13("Cucumber");
    MyString str14(str13);
    str13.PrintString();
    str14.PrintString();
    MyCompare(str13, (const char*)("Cucumber"), 8, 9);
    MyCompare(str14, (const char*)("Cucumber"), 8, 9);

    // initializer list constructor ->
    MyString str15({'E', 'g', 'g'});
    MyString str16(str15);
    str15.PrintString();
    str16.PrintString();
    MyCompare(str15, (const char*)("Egg"), 3, 4);
    MyCompare(str16, (const char*)("Egg"), 3, 4);

    // std::string constructor
    std::string arr6 = "Mango";
    MyString str17(arr6);
    MyString str18(str17);
    str17.PrintString();
    str18.PrintString();
    MyCompare(str17, (const char*)("Mango"), 5, 6);
    MyCompare(str18, (const char*)("Mango"), 5, 6);

    // init class with count characters of  “char string”
    char arr7[] = "Strawberry";
    MyString str19(arr7, 2);
    MyString str20(str19);
    str19.PrintString();
    str20.PrintString();
    MyCompare(str19, (const char*)("St"), 2, 3);
    MyCompare(str20, (const char*)("St"), 2, 3);

    // init class with count of characters
    MyString str21(4, '@');
    MyString str22(str21);
    str21.PrintString();
    str22.PrintString();
    MyCompare(str21, (const char*)("@@@@"), 4, 5);
    MyCompare(str22, (const char*)("@@@@"), 4, 5);

    ResultTests();
}

void TestCopyAssignment()
{
    // copy assignment
    // small str -> big str (I test it because operator= has selection condition)
    MyString str1("cats and dogs");
    MyString str2("will be deleted");
    str1.PrintString();
    str2.PrintString();
    str2 = str1;
    str2.PrintString();

    // big -> small
    MyString str3("cats, mice and dogs");
    MyString str4("will be deleted");
    str3.PrintString();
    str4.PrintString();
    str4 = str3;
    str4.PrintString();

    // equal
    MyString str5("wont be deleted");
    MyString str6("will be deleted");
    str5.PrintString();
    str6.PrintString();
    str6 = str5;
    str6.PrintString();

    // empty -> full
    MyString str9;
    MyString str10("will be deleted");
    str9.PrintString();
    str10.PrintString();
    str10 = str9;
    str10.PrintString();

    // full -> empty
    MyString str7("very interesting text");
    MyString str8;
    str7.PrintString();
    str8.PrintString();
    str8 = str7;
    str8.PrintString();
}

void TestCharStringAssignment()
{
    // char string assignment
    // small str -> big str
    MyString str1("will be deleted");
    char arr1[] = "cats and dogs";
    str1 = arr1;
    str1.PrintString();

    // big -> small
    MyString str2("will be deleted");
    char arr2[] = "cats, mice and dogs";
    str2 = arr2;
    str2.PrintString();

    // equal
    MyString str3("will be deleted");
    char arr3[] = "wont be deleted";
    str3 = arr3;
    str3.PrintString();

    // empty -> full
    MyString str4("will be deleted");
    char* arr4 = nullptr;
    str4 = arr4;
    str4.PrintString();

    // full -> empty
    MyString str5;
    char arr5[] = "Objects sometimes correspond to things found in the real world";
    str5 = arr5;
    str5.PrintString();
}

void TestStringAssignment()
{
    // std::string assignment
    // small str -> big str
    MyString str1("will be deleted");
    std::string arr1 = "cats and dogs";
    str1 = arr1;
    str1.PrintString();

    // big -> small
    MyString str2("will be deleted");
    std::string arr2 = "cats, mice and dogs";
    str2 = arr2;
    str2.PrintString();

    // equal
    MyString str3("will be deleted");
    std::string arr3 = "wont be deleted";
    str3 = arr3;
    str3.PrintString();

    // empty -> full
    MyString str4("will be deleted");
    std::string arr4 = "";
    str4 = arr4;
    str4.PrintString();

    // full -> empty
    MyString str5;
    std::string arr5 = "Objects sometimes correspond to things found in the real world";
    str5 = arr5;
    str5.PrintString();
}

void TestCharAssignment()
{
    // char assignment
    // ch -> empty
    MyString str1;
    char ch1 = '#';
    str1 = ch1;
    str1.PrintString();

    // ch -> full
    MyString str2("some text");
    char ch2 = '%';
    str2 = ch2;
    str2.PrintString();
}

void TestConcatenate()
{
    //concatenate with Mystring
    // empty str3
    MyString str1("hel"), str2("lo"), str3;
    str3 = str1 + str2;
    str3.PrintString();

    // not empty str6
    MyString str4("wo"), str5("rld"), str6("very long str");
    str6 = str4 + str5;
    str6.PrintString();

    // more concatenate
    MyString str7("I "), str8("love "), str9("OOP!"), str10;
    str10 = str7 + str8 + str9;
    str10.PrintString();

    // empty second summand
    MyString str11, str12;
    str12 = str10 + str11;
    str12.PrintString();

    // empty first summand
    MyString str13;
    str13 = str11 + str10;
    str13.PrintString();

    // empty all summands
    MyString str14, str15, str16;
    str16 = str14 + str15;
    str16.PrintString();

    // concatenate with char array
    // MyString + "char"
    MyString str17("Object-oriented programming "), str18;
    str18 = str17 + "is a programming paradigm";
    str18.PrintString();

    // MyString + ""
    MyString str19("It based on the concept of objects "), str20;
    str20 = str19 + "";
    str20.PrintString();

    // empty MyString + "char"
    MyString str21, str22;
    str22 = str21 + "It can contain data and code";
    str22.PrintString();

    // concatenate with std::string
    MyString str23("OOP languages are diverse, "), str24;
    std::string arr1 = "but the most popular ones are class-based";
    str24 = str23 + arr1;
    str24.PrintString();
}

void TestConcatenateWithAssignment()
{
    // assignment concatenate with char array
    // empty += empty
    MyString str1;
    char* arr1 = nullptr;
    str1 += arr1;
    str1.PrintString();

    // empty += full
    MyString str2;
    char arr2[] = "Methods can access and modify the object's data fields";
    str2 += arr2;
    str2.PrintString();

    // full += empty
    MyString str3("Methods can access and modify the object's data fields");
    char* arr3 = nullptr;
    str3 += arr3;
    str3.PrintString();

    //full += full (small capacity)
    MyString str4("Methods can access ");
    char arr4[] = "and modify the object's data fields";
    str4 += arr4;
    str4.PrintString();

    // full += full (big capacity)
    MyString str5("Many of the most widely used programming languages (such as C++, Java, Python, etc.) are multi-paradigm");
    MyString str6("C++, Java, Python ");
    str5 = str6; // I want big capacity
    char arr5[] = "are multi-paradigm";
    str5 += arr5;
    str5.PrintString();


    // assignment concatenate with std::string
    // empty += empty
    MyString str7;
    std::string arr6;
    str7 += arr6;
    str7.PrintString();

    // empty += full
    MyString str8;
    std::string arr7 = "Object-oriented programming uses objects";
    str8 += arr7;
    str8.PrintString();

    // full += empty
    MyString str9("Not all of the associated techniques and structures are supported directly in languages that claim to support OOP");
    std::string arr8;
    str9 += arr8;
    str9.PrintString();

    //full += full (small capacity)
    MyString str10("Variables that can store information formatted in");
    std::string arr9 = " a small number of built-in data types like integers and alphanumeric characters";
    str10 += arr9;
    str10.PrintString();

    // full += full (big capacity)
    MyString str11("Many of the most widely used programming languages (such as C++, Java, Python, etc.) are multi-paradigm");
    MyString str12("C++, Java, Python ");
    str11 = str12; // I want big capacity
    char arr10[] = "are multi-paradigm";
    str11 += arr10;
    str11.PrintString();
}

void TestIndex()
{
    // test index-function
    MyString str1 = "cat";
    std::cout << "str1[0] = " << str1[0] << std::endl;
    std::cout << "str1[1] = "  << str1[1] << std::endl;
    std::cout << "str1[2] = "  << str1[2] << std::endl;
    //std::cout << "str1[3] = "  << str1[3] << std::endl; // going outside the array returns throw

    // test const index-function
    const MyString str2("dog");
    char ch = str2[1];
    std::cout << "ch = " << ch << std::endl;
}

void TestLexicographicallyComparing()
{
    MyString a, b;
    a = "abcd";
    b = "abce";
    std::cout << "(a==b) = " << (a==b) << ", (a!=b) = " << (a!=b) << ", (a>b) = " << (a>b)
              << ", (a>=b) = " << (a>=b) << ", (a<b) = " << (a<b) << ", (a<=b) = " << (a<=b) << std::endl;
}

void TestAnotherOperators()
{
    // return a pointer to null-terminated character array
    MyString a0 = "cat";
    std::cout << a0.c_str() << std::endl;

    // return a pointer to array data that not required to be null-terminated
    MyString a1("Hello world!");
    std::string s1;
    s1 = a1.data();
    std::cout << s1 << std::endl;

    // return the number of char elements in string
    MyString a2("Hello world!");
    std::cout << a2.size() << std::endl;

    // same as size
    MyString a3("Hello world!");
    std::cout << a3.length() << std::endl;

    // return the current amount of allocated memory for array
    MyString a4("Hello world!");
    std::cout << a4.capacity() << std::endl;

    // true if string is empty
    MyString a5("Hello world!");
    std::cout << a5.empty() << std::endl;

    MyString a6;
    std::cout << a6.empty() << std::endl;

    // remove all char element in string
    MyString a7("Hello world!");
    std::cout << a7 << std::endl;
    a7.clear();
    std::cout << a7 << std::endl;

    // reduce the capacity to size
    MyString a8("Many of the most widely used programming languages (such as C++, Java, Python, etc.) are multi-paradigm");
    MyString a9("C++, Java, Python ");
    a8 = a9; // I want big capacity
    a8.PrintString();
    a8.shrink_to_fit();
    a8.PrintString();

    MyString a10("In class-based languages the classes are defined beforehand"); // capacity_ shouldn't change
    a10.PrintString();
    a10.shrink_to_fit();
    a10.PrintString();
}

void TestInputOperator()
{
    MyString a;
    std::cout << "Введите строку: ";
    std::cin >> a;
    std::cout << "Вы ввели: " << a << std::endl;
}

void TestInsert()
{
    // insert count of char in index position
    MyString a1 = "aaaaa";
    a1.PrintString();
    a1.insert(0, 1, '!');  // zero character
    a1.PrintString();
    a1.insert(3, 2, '@');  // usual
    a1.PrintString();
    try {
        a1.insert(0, 0, '#');  // do not insert characters
    }  catch (std::out_of_range& e) {
        std::cout << "Good error: " << e.what() << std::endl;
    }
    a1.PrintString();
    a1.insert(7, 1, '%');  // getting index one to the end of the array
    a1.PrintString();
    try {
        a1.insert(15, 5, '*'); // getting index out of the array
    }  catch (std::out_of_range& e) {
        std::cout << "Good error: " << e.what() << std::endl;
    }
    a1.PrintString();
    a1.insert(9, 3, '*');  // getting index to the end of the array
    a1.PrintString();

    // insert null-terminated char string at index position
    MyString a2 = "aaaaa";
    a2.insert(1,"@@@@@"); // usual
    a2.PrintString();
    a2.insert(0,"**");    // zero character
    a2.PrintString();
    a2.insert(12,"&&&");  // getting index to the end of the array
    a2.PrintString();
    a2.insert(14,"!");    // getting index one to the end of the array
    a2.PrintString();

    MyString a3 = "123456789";
    MyString a4 = "ab";
    a3 = a4;            // I want big capacity
    try {
        a3.insert(5, "!");  // I check that with a large capacity we will not be able to insert characters in the middle of an empty array
    }  catch (std::out_of_range& e) {
        std::cout << "Good error: " << e.what() << std::endl;
    }
    a3.PrintString();
    a3.insert(2, "$$"); // all ok
    a3.PrintString();

    // insert count of null-terminated char string at index position
    MyString a5 = "aaaaa";
    a5.insert(1,"@@@@@",2);
    a5.PrintString();

    // insert std::string at index position
    MyString a6("123456789");
    std::string arr1 = "qwerty";
    a6.insert(2, arr1);
    a6.PrintString();

    // insert count of std::string at index position
    MyString a7("123456789");
    std::string arr2 = "qwerty";
    a7.insert(4, arr2, 3);
    a7.PrintString();
}

void TestErase()
{
    MyString a1("Hello world!");
    a1.PrintString();
    a1.erase(5, 6);
    a1.PrintString();

    // from a2[0]
    MyString a2("123456789");
    a2.PrintString();
    a2.erase(0, 3);
    a2.PrintString();

    // erase end of a3
    MyString a3("123456789");
    a3.PrintString();
    a3.erase(6, 3);
    a3.PrintString();

    // erase end of a3 and out of str_
    MyString a4("123456789");
    a4.PrintString();
    a4.erase(6, 5);
    a4.PrintString();

    // erase all str
    MyString a5("123456789");
    a5.PrintString();
    a5.erase(0, 9);
    a5.PrintString();

    // erase 0 symbols
    MyString a6("123456789");
    a6.PrintString();
    a6.erase(6, 0);
    a6.PrintString();
}

void TestAppend()
{
    // append count of char
    MyString a1;
    a1.append(3,'!');
    a1.PrintString();
    a1.append(3,'@');
    a1.PrintString();


    // append null-terminated char string
    // -> full
    MyString a2;
    a2.append("Hello");
    a2.PrintString();
    a2.append(" world");
    a2.PrintString();

    // -> empty (no capacity)
    MyString a3;
    a3.PrintString();
    a3.append("Hello");
    a3.PrintString();

    // -> full (with capacity) (we check that the capacity has not changed)
    MyString a4("1234567890");
    a4.erase(2, 8);
    a4.append("Hello");
    a4.PrintString();

    //append empty
    a4.append("");
    a4.PrintString();


    // append a count of null-terminated char string by index position
    // usual
    MyString a5;
    a5.append("Hello world",0,6);
    a5.PrintString();
    a5.append("Hello world",6,5);
    a5.PrintString();

    // append full str
    MyString a6;
    a6.append("Hello world",0,11);
    a6.PrintString();

    // append empty str
    MyString a7;
    a7.append("Hello world",0,0);
    a7.PrintString();

    // incorrect index (nothing happens)
    MyString a8("123");
    a8.append("Hello world",11,5);
    a8.PrintString();


    // append std:: string
    // usual
    MyString a9;
    std::string s1="Hello ", s2="world";
    a9.append(s1);
    a9.PrintString();
    a9.append(s2);
    a9.PrintString();

    // empty str
    MyString a10("123456789");
    std::string s3 = "";
    a10.append(s3);
    a10.PrintString();


    // append a count of std:: string by index position
    MyString a11;
    std::string s4 = "Hello world";
    a11.append(s4,0,6);
    a11.PrintString();
    a11.append(s4,6,5);
    a11.PrintString();

    // incorrect index (nothing happens)
    try {
        a11.append(s4,15,6);
    }  catch (std::out_of_range& e) {
        std::cout << "Good error: " << e.what() << std::endl;
    }
}

void TestReplace()
{
    // replace a count of char at index by “string”
    // usual
    MyString a1 = "hello amazing world";
    a1.replace(6,7,"wonderful");
    a1.PrintString();

    // empty string
    MyString a2 = "hello amazing world";
    a2.replace(6,7,"");
    a2.PrintString();

    // incorrect index (exeption)
    MyString a3 = "hello amazing world";
    a3.replace(25,7,"wonderful");
    a3.PrintString();

    // incorrect count (count + index > size_) (exeption)
    MyString a4 = "hello amazing world";
    a4.replace(6,20,"wonderful");
    a4.PrintString();

    // count + index == size_ (exeption)
    MyString a5 = "hello amazing world";
    a5.replace(6,13,"wonderful");
    a5.PrintString();

    // count == 0
    MyString a6 = "hello amazing world";
    a6.replace(6,0,"wonderful");
    a6.PrintString();


    // replace a count of char at index by std::string
    MyString a7 = "hello amazing world";
    std::string s1 = "wonderful";
    a7.replace(6,7,s1);
    a7.PrintString();

}

void TestSubstr()
{
    // return a substring starts with index position
    // usual
    MyString a1 = "hello amazing world", a2;
    a2 = a1.substr(6);
    a2.PrintString();

    // index == 0
    MyString a3 = "hello amazing world", a4;
    a4 = a3.substr(0);
    a4.PrintString();

    // index == last symbol
    MyString a5 = "hello amazing world", a6;
    a6 = a5.substr(18);
    a6.PrintString();

    // incorrect index (exception)
//    MyString a7 = "hello amazing world", a8("1234");
//    a8 = a7.substr(19);
//    a8.PrintString();


    // return a count of substring’s char starts with index position
    // usual
    MyString a9 = "The cat (Felis catus), commonly referred to as the domestic cat or house cat, is the only domesticated species in the family Felidae. Recent advances in archaeology and genetics have shown that the domestication of the cat occurred in the Near East around 7500 BC. It is commonly kept as a house pet and farm cat, but also ranges freely as a feral cat avoiding human contact.It is valued by humans for companionship and its ability to kill vermin. Because of its retractable claws it is adapted to killing small prey like mice and rats. It has a strong flexible body, quick reflexes, sharp teeth, and its night vision and sense of smell are well developed. It is a social species, but a solitary hunter and a crepuscular predator.Cat communication includes vocalizations like meowing, purring, trilling, hissing, growling, and grunting as well as cat body language. It can hear sounds too faint or too high in frequency for human ears, such as those made by small mammals. It also secretes and perce1111ives pheromones.The cat (Felis catus), commonly referred to as the domestic cat or house cat, is the only domesticated species in the familyFelidae. Recent advances in archaeology and genetics have shown that the domestication of the cat occurred in the Near East around 7500 BC. It is commonly kept as a house pet and farm cat, but also ranges freely as a feral cat avoiding human contact.It is valued by humans for companionship and its ability to kill vermin.Because of its retractable claws it is adapted to killing small prey like mice and rats. It has a strong flexible body, quick reflexes, sharp teeth, and its night vision and sense of smell are well developed. It is a social species, but a solitary hunter and a crepuscular predator.Cat communication includes vocalizations like meowing, purring, trilling, hissing, growling, and grunting as well as cat body language. It can hear sounds too faint or too high in frequency for human ears, such as those made by small mammals. It also secretes and perce1111ives pheromones.", a10;
    a10 = a9.substr(6,7);
    a10.PrintString();

    // incorrect count
    MyString a11 = "hello amazing world", a12;
    a12 = a11.substr(6,20);
    a12.PrintString();

    // count == 0
    MyString a13 = "hello amazing world", a14;
    a14 = a13.substr(6,0);
    a14.PrintString();

}

void TestFind()
{
    // if founded return the index of substring
    // usual
    MyString a1 = "hello amazing world amazing";
    size_t i1 = a1.find("amazing");
    std::cout << i1 << std::endl;

    // empty find
    MyString a2 = "hello amazing world amazing";
    size_t i2 = a2.find("");
    std::cout << i2 << std::endl;

    // empty MyString
    MyString a3;
    size_t i3 = a3.find("amazing");
    std::cout << i3 << std::endl;

    // not find
    MyString a4 = "hello amazing world amazing";
    size_t i4 = a4.find("perfect");
    std::cout << i4 << std::endl;


    // same as find(“string”) but search starts from index position
    //usual
    MyString a5 = "hello amazing world amazing";
    int i5 = a5.find("amazing", 7);
    std::cout << i5 << std::endl;

    // incorrect index
    MyString a6 = "hello amazing world amazing";
    int i6 = a6.find("amazing", 50);
    std::cout << i6 << std::endl;


    // if founded return the index of substring (std::string)
    // usual
    MyString a7 = "hello amazing world amazing";
    std::string s7 = "amazing";
    int i7 = a7.find(s7);
    std::cout << i7 << std::endl;

    // std::strin is empty
    MyString a8 = "hello amazing world amazing";
    std::string s8 = "";
    int i8 = a8.find(s8);
    std::cout << i8 << std::endl;


    // same as find(“string”) but search starts from index position
    MyString a9 = "hello world hello amazing world amazing";
    std::string s9 = "world";
    int i9 = a9.find(s9, 8);
    std::cout << i9 << std::endl;
}

void TestException()
{
    try {
            [[maybe_unused]] int c = SomeTestFoo();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception was catched: " << e.what() << std::endl;
        }
}

int SomeTestFoo()
{
    int a = 10, b = 0;
    if (b == 0)
    {
        throw MyException("division by zero");
    }
    else return a/b;
}

void TestMoveConstructorAssignment()
{
    // constructor
    // from full
    MyString str1("Apple");
    str1.PrintString();
    MyString str2(std::move(str1));
    str2.PrintString();
    str1.PrintString();

    // from empty
    MyString str3;
    str1.PrintString();
    MyString str4(std::move(str3));
    str4.PrintString();
    str3.PrintString();

    // assignment
    // full -> full
    MyString str5("Banana"), str6("Pearch");
    str5.PrintString();
    str6.PrintString();
    str5 = std::move(str6);
    str5.PrintString();
    str6.PrintString();

    // full -> empty
    MyString str7, str8("Grape");
    str7.PrintString();
    str8.PrintString();
    str7 = std::move(str8);
    str7.PrintString();
    str8.PrintString();

    // empty -> full
    MyString str9("Watermelon"), str10;
    str9.PrintString();
    str6.PrintString();
    str9 = std::move(str10);
    str9.PrintString();
    str10.PrintString();

    // empty -> empty
    MyString str11, str12;
    str11.PrintString();
    str12.PrintString();
    str11 = std::move(str12);
    str11.PrintString();
    str12.PrintString();
}

void TestIntFloat()
{
    // integer
    MyString hexstr0 = 10;
    hexstr0.PrintString();
    MyString hexstr1 = 0xA;
    hexstr1.PrintString();
    MyString hexstr2 = 1234567890;
    hexstr2.PrintString();
    MyString hexstr3 = 0;
    hexstr3.PrintString();
    MyString hexstr4 = 16;
    hexstr4.PrintString();
    MyString hexstr5 = 256;
    hexstr5.PrintString();

    // float
    MyString hexstr6 = 0.12f;
    hexstr6.PrintString();
    MyString hexstr7 = 5.873421f;
    hexstr7.PrintString();
    MyString hexstr8 = 0.0f;
    hexstr8.PrintString();
    MyString hexstr9 = 1235.581f;
    hexstr9.PrintString();
}

void TestIOFile()
{
    MyString str1 = "Hello, World!";

    // Запись объекта MyString в файл
    std::ofstream outFile("D:\\Univer_files\\5sem\\OOP\\Lab1_MyString_new\\output.txt");
    if (outFile)
    {
        outFile << str1;
        outFile.close();
    }
    else
        std::cerr << "Failed to open output file." << std::endl;

    // Чтение объекта MyString из файла
    std::ifstream inFile("D:\\Univer_files\\5sem\\OOP\\Lab1_MyString_new\\input.txt");
    if (inFile)
    {
        MyString str2;
        inFile >> str2;
        std::cout << "Read from file: " << str2 << std::endl;
        inFile.close();
    }
    else
        std::cerr << "Failed to open input file." << std::endl;
}

void TestAt()
{
    // usual
    MyString str1("Hello, World!");
    str1.PrintString();
    char ch1 = str1.at(2);
    std::cout << "str1.at(2) = " << ch1 << std::endl;

    //incorrect index (exception)
    char ch2 = str1.at(13);
    std::cout << "str1.at(13) = " << ch2 << std::endl;
}

void TestToInt()
{
    // usual
    MyString str1("123");
    str1.PrintString();
    long long int i1 = str1.to_int();
    std::cout << "str1.to_int() = " << i1 << std::endl;

    //incorrect index (exception)
    MyString str2("abc");
    str1.PrintString();
    long long int i2 = 0;
    try {
            i2 = str2.to_int();
        }
        catch (const std::exception& e) {
            std::cerr << "Good error: " << e.what() << std::endl;
        }
    std::cout << "str2.to_int() = " << i2 << std::endl;
}

void TestToFloat()
{
    // usual
    MyString str1 = "3.14159";
    float fl1 = str1.to_float();
    std::cout << "fl1 = " << fl1 << std::endl << std::endl;

    // int
    MyString str2 = "15";
    float fl2 = str2.to_float();
    std::cout << "fl2 = " << fl2 << std::endl << std::endl;

    // null
    MyString str3 = "0";
    float fl3 = str3.to_float();
    std::cout << "fl3 = " << fl3 << std::endl << std::endl;

    // incorrect
    MyString str4 = "abc";
    try {
        float fl4 = str4.to_float();
        std::cout << "fl4 = " << fl4 << std::endl << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Good error: " << e.what() << std::endl << std::endl;
    }
}

void TestAhoCorasick()
{
    MyString text = "I like apples, bananas, and cherries. But apples are the best!";

    AhoCorasick ac; // This object is needed for the search

    // We write what we want to find in the text
    MyString keyword1 = "apples";
    MyString keyword2 = "banan";
    MyString keyword3 = "cherry";

    // Keywords are added to Bohr
    ac.AddKeyword(keyword1);
    ac.AddKeyword(keyword2);
    ac.AddKeyword(keyword3);

    // Building the suffix links in the Bohr
    ac.Build();

    // Vector with pairs. The pair contains the position in the text and the length of the keyword
    std::vector<std::pair<size_t, size_t>> keywordPositions = text.find(ac);

    // Print results
    for (size_t i = 0; i != keywordPositions.size(); ++i)
    {
        std::cout << "Found keyword at position " << keywordPositions[i].first << ": " << text.substr(keywordPositions[i].first, keywordPositions[i].second) << std::endl;
    }
}

void TestIterator()
{
    // insert
    MyString str1 = "This is a test string.";
    MyString str2 = "insertion ";

    iterator it1 = str1.begin();
    for (int i = 0; i < 10; ++i)
    {
        ++it1;
    }
    str1.insert(it1, str2);
    std::cout << str1 << std::endl;

    // erase
    MyString str3 = "Hello, World!";
    iterator it2 = str3.begin() + 5;

    str3.erase(it2, 7);
    std::cout << str3 << std::endl;

    // append
    MyString str4 = "I love ";
    iterator it3 = str4.end();

    const char* arr1 = "apples!";
    size_t count_arr = strlen(arr1);

    str4.append(arr1, it3, count_arr);
    std::cout << str4 << std::endl;

    // replace
    MyString str5("Hello, world!");
    iterator it4 = str5.begin() + 7;

    str5.replace(it4, 5, "people");
    std::cout << str5 << std::endl;

    // substr
    MyString str6 = "Hello, World!";

    iterator it5 = str6.begin();

    MyString str6_1 = str6.substr(it5);
    std::cout << "1: " << str6_1 << std::endl;

    it5 += 7;

    MyString str6_2 = str6.substr(it5, 5);
    std::cout << "2: " << str6_2 << std::endl;

    // find
    MyString str7("This is an example string for searching.");
    iterator it6 = str7.begin() + 5;

    const char* search_str = "example";
    size_t res = str7.find(search_str, it6);
    std::cout << res << std::endl;

    // at
    MyString str8 = "Hello, World!";
    iterator it7 = str8.begin() + 7;
    char ch1 = str8.at(it7);
    std::cout << ch1 << std::endl;

    // operator []
    MyString str9("Hello, World!");
    iterator it8 = str9.begin();
    char ch = str9[it8];
    std::cout << ch << std::endl;
}

void TestConstIterator()
{
    // substr
    MyString str6 = "Hello, World!";

    const_iterator it5 = str6.cbegin();

    //*it5 = '5'; // we can't do it

    MyString str6_1 = str6.substr(it5);
    std::cout << "1: " << str6_1 << std::endl;

    it5 += 7;

    MyString str6_2 = str6.substr(it5, 5);
    std::cout << "2: " << str6_2 << std::endl;

    // find
    MyString str7("This is an example string for searching.");
    const_iterator it6 = str7.cbegin() + 5;

    const char* search_str = "example";
    size_t res = str7.find(search_str, it6);
    std::cout << res << std::endl;

    // at
    MyString str8 = "Hello, World!";
    const_iterator it7 = str8.cbegin() + 7;
    char ch1 = str8.at(it7);
    std::cout << ch1 << std::endl;

    // operator []
    MyString str9("Hello, World!");
    const_iterator it8 = str9.cbegin();
    char ch = str9[it8];
    std::cout << ch << std::endl;
}

void TestReverseIterator()
{
    // insert
    MyString str1 = "This is a test string ";
    MyString str2 = "insert.";

    reverse_iterator it1 = str1.rbegin();
    str1.insert(it1, str2);
    std::cout << str1 << std::endl;

    // erase
    MyString str3 = "Hello, cool cat!";
    reverse_iterator it2 = str3.rbegin();
    it2 += 6;

    str3.erase(it2, 5);
    std::cout << str3 << std::endl;

    // append
    MyString str4 = "I love ";
    reverse_iterator it3 = str4.rbegin();

    const char* arr1 = "apples!";
    size_t count_arr = strlen(arr1);

    str4.append(arr1, it3, count_arr);
    std::cout << str4 << std::endl;

    // replace
    MyString str5("Hello, world!");
    reverse_iterator it4 = str5.rbegin() + 7;

    str5.replace(it4, 5, "people");
    std::cout << str5 << std::endl;

    // substr
    MyString str6 = "Hello, World!";

    reverse_iterator it5 = str6.rbegin();

    MyString str6_1 = str6.substr(it5);
    std::cout << "1: " << str6_1 << std::endl;

    it5 += 7;

    MyString str6_2 = str6.substr(it5, 5);
    std::cout << "2: " << str6_2 << std::endl;

    // find
    MyString str7("This is an example string for searching.");
    reverse_iterator it6 = str7.rbegin() + 5;

    const char* search_str = "example";
    size_t res = str7.find(search_str, it6);
    std::cout << res << std::endl;

    // at
    MyString str8 = "Hello, World!";
    reverse_iterator it7 = str8.rbegin() + 10;
    char ch1 = str8.at(it7);
    std::cout << ch1 << std::endl;

    // operator []
    MyString str9("Hello, World!");
    reverse_iterator it8 = str9.rbegin() + 2;
    char ch = str9[it8];
    std::cout << ch << std::endl;

    MyString str10("It is testing of reverse_iterator!");
    reverse_iterator it9 = str10.rbegin();
    while(it9++ != str10.rend())
    {
        std::cout << *it9;
    }
    std::cout << std::endl;
}

void TestConstReverseIterator()
{
    // substr
    MyString str6 = "Hello, World!";

    const_reverse_iterator it5 = str6.rcbegin();

    MyString str6_1 = str6.substr(it5);
    std::cout << "1: " << str6_1 << std::endl;

    it5 += 7;

    MyString str6_2 = str6.substr(it5, 5);
    std::cout << "2: " << str6_2 << std::endl;

    // find
    MyString str7("This is an example string for searching.");
    const_reverse_iterator it6 = str7.rcbegin() + 5;

    const char* search_str = "example";
    size_t res = str7.find(search_str, it6);
    std::cout << res << std::endl;

    // at
    MyString str8 = "Hello, World!";
    const_reverse_iterator it7 = str8.rcbegin() + 7;
    char ch1 = str8.at(it7);
    std::cout << ch1 << std::endl;

    // operator []
    MyString str9("Hello, World!");
    const_reverse_iterator it8 = str9.rcbegin();
    char ch = str9[it8];
    std::cout << ch << std::endl;
}

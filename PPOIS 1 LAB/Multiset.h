#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <stack>
#include <string>
#include <vector>

class Set {
public:
    Set();
    ~Set();

    void power();
    void clear();
    std::map<char, int> getElements();
    std::map<Set*, int> getSubsets();

    Set subtractElements(const Set& other) const;
    Set subtractSubsets(const Set& other) const;
    Set intersectElements(const Set& other) const;
    Set intersectSubsets(const Set& other) const;
    Set unionElements(const Set& other) const;
    Set unionSubsets(const Set& other) const;

    bool operator ==(const Set& set2) const;
    Set& operator[](const std::string& str);
    Set operator+(const Set* set) const;
    Set& operator+=(const Set* set);
    Set operator*(const Set* set) const;
    Set& operator*=(const Set* set);
    Set operator-(const Set* set) const;
    Set& operator-=(const Set* set);
    Set operator=(const Set* set);
    std::vector<Set> boolean() const;

    Set(const std::string& str);
    Set(const char*& str1);
    void removeDuplicateSubsets();
    void add(char element, int count = 1);
    void add(Set* element, int count);
    void deleteElement(char element, int count = 1);
    void show(int depth = 0) const;
private:
    std::map<char, int> setElement;
    std::map<Set*, int> setSubset;
};


int get(const std::vector<Set*>& mas, int& first, int& second);
int get(const std::vector<Set*>& mas, int first);
bool isBracket(const std::string& str);
void showBoolean(std::vector<Set> boolean);
int Subset(const std::string& string);
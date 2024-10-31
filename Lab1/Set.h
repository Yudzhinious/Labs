#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <stack>



class Set {
public:
    Set();
    ~Set();
    Set(const std::string& input);
    Set(const char* input);
    int power() const;
    void clear();
    std::map<char, int> getElements();
    std::map<Set*, int> getSubsets();
    Set removeDuplicateSubsets();

    bool operator ==(const Set& set) const;
    Set operator+(const Set* set) const;
    Set& operator+=(const Set* set);
    Set unionElements(const Set& other) const;
    Set unionSubsets(const Set& other) const;
    Set operator*(const Set* set) const;
    Set& operator*=(const Set* set);
    Set intersectElements(const Set& other) const;
    Set operator-(const Set* set) const;
    Set& operator-=(const Set* set);
    Set subtractElements(const Set& other) const;
    Set subtractSubsets(const Set& other) const;
    Set& operator=(const Set& other);
    
    void add(char element, int count = 1);
    void add(Set* element, int count = 1);
    void deleteElement(char element, int count = 1);
    void show(int a = 0) const;
    std::vector<Set> boolean();
private:
    std::map<char, int> setElement;
    std::map<Set*, int> setSubset;
};


bool isBracket(const std::string& str);
void showBoolean(std::vector<Set> boolean);
int  numberOfSubsets(std::string string);

#include "Set.h"

Set::Set() {}
Set::~Set() {}
Set::Set(const std::string& input) {
    size_t index = 1;
    while (index < input.size()) {
        if (input[index] == '{') {
            size_t start = index;
            int balance = 1;
            while (balance > 0 && ++index < input.size()) {
                if (input[index] == '{') {
                    balance++;
                }
                else if (input[index] == '}') {
                    balance--;
                }
            }
            if (balance == 0) {
                setSubset[new Set(input.substr(start, index - start + 1))]++;
            }
        }

        if (input[index] >= 'a' && input[index] <= 'z') {
            setElement[input[index]]++;
        }
        index++;
    }
}

Set::Set(const char* input) {
    std::string str(input);
    size_t pos = 1;
    while (pos < str.size()) {
        if (str[pos] == '{') {
            size_t start = pos;
            int balance = 1;

            while (balance > 0 && ++pos < str.size()) {
                if (str[pos] == '{') {
                    balance++;
                }
                else if (str[pos] == '}') {
                    balance--;
                }
            }

            if (balance == 0) {
                setSubset[new Set(str.substr(start, pos - start + 1))]++;
            }
        }

        if (str[pos] >= 'a' && str[pos] <= 'z') {
            setElement[str[pos]]++;
        }
        pos++;
    }
}
Set Set::removeDuplicateSubsets() {
    std::map<Set*, int> dupleSet;

    for (std::map<Set*, int>::iterator it = setSubset.begin(); it != setSubset.end(); ++it) {
        Set* subset = it->first;
        int value = it->second;

        std::map<Set*, int>::iterator dupleIt = dupleSet.find(subset);
        if (dupleIt != dupleSet.end()) {
            dupleIt->second += value;
        }
        else {
            dupleSet[subset] = value;
        }
    }
    Set result;
    for (std::map<Set*, int>::iterator dupleIt = dupleSet.begin(); dupleIt != dupleSet.end(); ++dupleIt) {
        result.setSubset.emplace(dupleIt->first, dupleIt->second);
    }
    return result; 
}
void Set::clear() {
    if (!setElement.empty() || !setSubset.empty()) {
        setElement.clear();
        setSubset.clear();
        std::cout << "Ìíîæåñòâî î÷èùåíî." << std::endl;
    }
    else {
        std::cout << "Ìíîæåñòâî óæå î÷èùåíî." << std::endl;
    }
}
bool isBracket(const std::string& str) {
    std::stack<char> stack;
    for (char ch : str) {
        if (ch == '{') {
            stack.push(ch);
        }
        else if (ch == '}') {
            if (stack.empty()) {
                std::cout << "Îøèáêà" << std::endl;
                return false;
            }
            stack.pop();
        }
        else if (ch == '[' || ch == ']') {
            std::cout << "Íå ïðàâèëüíûé ñèìâîë: " << ch << std::endl;
            return false;
        }
    }
    if (!stack.empty()) {
        std::cout << "Îñòàëîñü " << stack.size() << " íåçàêðûòûõ '{'" << std::endl;
        return false;
    }
    return true;
}
void Set::deleteElement(char element, int count) {
    auto it = setElement.find(element);

    if (it != setElement.end()) {
        it->second -= count;
        if (it->second <= 0) {
            setElement.erase(it);
            std::cout << "Ýëåìåíò '" << element << "' óñïåøíî óäàë¸í." << std::endl;
        }
        else {
            std::cout << "Ýëåìåíò '" << element << "' óìåíüøåí íà " << count << ". Òåêóùåå êîëè÷åñòâî: " << it->second << std::endl;
        }
    }
    else {
        std::cout << "Îøèáêà: ýëåìåíò '" << element << "' íå íàéäåí â ìíîæåñòâå." << std::endl;
    }
}
void Set::show(int a) const {
    if (setElement.empty() && setSubset.empty()) {
        std::cout << "{   }" << std::endl;
        return;
    }
    std::cout << std::setw(a) << " " << "{ ";
    if (!setElement.empty()) {
        for (const auto& element :setElement) {
            std::cout << std::setw(a) << "(" << element.first << " : " << element.second << ") ";
        }
    }
    if (!setSubset.empty()) {
        std::cout << std::setw(a) << std::endl;
        for (const auto& subset : setSubset) {
            std::cout << std::setw(a) << "Ïîäìíîæåñòâî :" << std::endl;
            subset.first->show(a);
        }
    }
    std::cout << " }" << std::endl;
}
bool Set::operator==(const Set& other) const {
    for (const auto& subsetEntry : this->setSubset) {
        const Set* subset = subsetEntry.first;
        int count = subsetEntry.second;
        bool found = false;

        for (const auto& otherEntry : other.setSubset) {
            const Set* otherSubset = otherEntry.first;
            if ((*otherSubset == *subset) && (otherEntry.second == count)) {
                found = true;
                break; 
            }
        }

        if (!found) {
            std::cout << "Ïîäìíîæåñòâî: " << subset << " (êîëè÷åñòâî: " << count << ") íå íàéäåíî â äðóãîì ìíîæåñòâå." << std::endl;
            return false; 
        }
    }
    std::cout << "Ìíîæåñòâà ðàâíû." << std::endl;
    return true;
}
int Set::power() const {
    int count = 0;
    std::cout << "Ýëåìåíòû ìíîæåñòâà:"<< std::endl;
    for (const auto& element : setElement) {
        count += element.second;
        std::cout << "Ýëåìåíò: " << element.first << ", Êîëè÷åñòâî: " << element.second << std::endl;
    }
    if (setSubset.empty()) {
        std::cout << "Íåò ïîäìíîæåñòâ."<< std::endl;
    }
    else {
        for (const auto& element : setSubset) {
            count ++;
            std::cout << "Ïîäìíîæåñòâî: " << element.second << std::endl;
        }
    }
    std::cout << "Ìîùíîñòü äàííîãî ìóëüòèìíîæåñòâà: " << count << std::endl;
    return count;
}
Set Set::unionElements(const Set& other) const {
    Set result = *this;

    for (const auto& elem : other.setElement) {
        result.setElement[elem.first] = std::max(result.setElement[elem.first], elem.second);
    }
    return result;
}
Set Set::unionSubsets(const Set& other) const {
    bool exists = true;
    Set result = *this; 
    for (auto it = setSubset.begin(); it != setSubset.end(); ++it) {
        result.setSubset[it->first] = it->second;
    }

    for (auto otherIt = other.setSubset.begin(); otherIt != other.setSubset.end(); ++otherIt) {
        Set* otherSubset = otherIt->first;
        int otherValue = otherIt->second;

        for (auto resultIt = result.setSubset.begin(); resultIt != result.setSubset.end(); ++resultIt) {
            if (*resultIt->first == *otherSubset) {
                result.setSubset[resultIt->first] = std::max(resultIt->second, otherValue);
                break;
            }
        }

        if (exists) {
            result.setSubset[otherSubset] = otherValue;
        }
    }

    return result;
}
Set Set::operator+(const Set* set) const {
    Set result = unionElements(*set);
    Set subsetResult = unionSubsets(*set);
    result.setSubset.insert(subsetResult.setSubset.begin(), subsetResult.setSubset.end());

    return result;
}
Set& Set::operator+=(const Set* set) {
    Set result = *this + set;
    setElement = result.setElement;
    setSubset = result.setSubset;
    return *this;
}
Set Set::intersectElements(const Set& other) const {
    Set result;

    for (const auto& elem : setElement) {
        auto it = other.setElement.find(elem.first);
        if (it != other.setElement.end()) {
            result.setElement[elem.first] = std::min(elem.second, it->second);
        }
    }
    return result;
}
Set Set::operator*(const Set* set) const {
    Set result = intersectElements(*set);
    Set subsetResult = unionSubsets(*set);

    result.setSubset.insert(subsetResult.setSubset.begin(), subsetResult.setSubset.end());
    return result;
}
std::vector<Set> Set::boolean() {
    std::vector<Set> booleanSets;
    booleanSets.reserve(1 << (setElement.size() + setSubset.size()));
    booleanSets.push_back(Set());

    for (const auto& elem : setElement) {
        size_t currentSize = booleanSets.size();
        for (size_t i = 0; i < currentSize; i++) {
            Set newSet = booleanSets[i];
            newSet.add(elem.first, elem.second);
            booleanSets.push_back(newSet);
        }
    }

    for (const auto& sub : setSubset) {
        size_t currentSize = booleanSets.size();
        for (size_t i = 0; i < currentSize; i++) {
            Set newSet = booleanSets[i];
            newSet.add(sub.first, sub.second);
            booleanSets.push_back(newSet);
        }
    }

    return booleanSets;
}
Set& Set::operator*=(const Set* set) {
    Set result = *this + set;
    setElement = result.setElement;
    setSubset = result.setSubset;
    return *this;
}
Set Set::subtractElements(const Set& other) const {
    Set result = *this;

    for (const auto& elem : other.setElement) {
        auto it = result.setElement.find(elem.first);
        if (it != result.setElement.end()) {
            it->second -= elem.second;
            if (it->second <= 0) {
                result.setElement.erase(it);
            }
        }
    }
    return result;
}
Set Set::subtractSubsets(const Set& other) const {
    Set result = *this;

    for (const auto& otherSubset : other.setSubset) {
        auto it = result.setSubset.find(otherSubset.first);
        if (it != result.setSubset.end()) {
            it->second -= otherSubset.second;
            if (it->second <= 0) {
                result.setSubset.erase(it);
            }
        }
    }
    return result;
}
Set Set::operator-(const Set* set) const {
    Set result = subtractElements(*set);
    result = result.subtractSubsets(*set);
    return result;
}
Set& Set::operator-=(const Set* set) {
    Set result = *this + set;
    setElement = result.setElement;
    setSubset = result.setSubset;
    return *this;
}
Set& Set::operator=(const Set& other) {
    if (this != &other) {
        setElement = other.setElement;
        setSubset = other.setSubset;
    }
    return *this;
}

int  numberOfSubsets(std::string string) {
    int braceCount = 1;
    size_t i;
    for (i = 0; braceCount > 0; i++) {
        if (i >= string.size()) {
            std::cout << "Îøèáêà: Íåäîñòàòî÷íî çàêðûâàþùèõ ñêîáîê â ñòðîêå." << std::endl;
            return -1;
        }
        if (string[i] == '{') {
            braceCount++;
        }
        else if (string[i] == '}') {
            braceCount--;
        }
    }
    return i;
}

void Set::add(Set* element, int count) {
    if (element == nullptr) {
        std::cout << "Îøèáêà: ïåðåäàííûé óêàçàòåëü íà ïîäìíîæåñòâî ÿâëÿåòñÿ null!" << std::endl;
        return;
    }
    if (count <= 0) {
        std::cout << "Îøèáêà: êîëè÷åñòâî äîëæíî áûòü áîëüøå íóëÿ!" << std::endl;
    }
    auto it = setSubset.find(element);
    if (it != setSubset.end()) {
        it->second += count;
        std::cout << it->second << std::endl;
    }
    else {
        setSubset[element] = count;
    }
}
void Set::add(char element, int count) {
    if (count <= 0) {
        std::cout << "Îøèáêà: êîëè÷åñòâî äîëæíî áûòü áîëüøå íóëÿ!" << std::endl;
        return;
    }
    auto it = setElement.find(element);
    if (it != setElement.end()) {
        it->second += count;
        std::cout << "Óñïåøíî îáíîâëåíî: ýëåìåíò '" << element << "' óæå ñóùåñòâóåò, íîâîå êîëè÷åñòâî: " << it->second << std::endl;
    }
    else {
        setElement[element] = count;
    }
}
void showBoolean(const std::vector<Set> boolean) {

    if (boolean.empty()) {
        std::cout << "Íåò ïîäìíîæåñòâ äëÿ îòîáðàæåíèÿ." << std::endl;
        return;
    }
    for (auto it = boolean.begin(); it != boolean.end(); ++it) {
        it->show();
    }
}

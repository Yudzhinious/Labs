#include "Set.h"

std::map<char, int> Set::getElements() {
    return setElement;
}
std::map<Set*, int> Set::getSubsets() {
    return setSubset;
}

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
        std::cout << "Множество очищено." << std::endl;
    }
    else {
        std::cout << "Множество уже очищено." << std::endl;
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
                std::cout << "Ошибка" << std::endl;
                return false;
            }
            stack.pop();
        }
        else if (ch == '[' || ch == ']') {
            std::cout << "Не правильный символ: " << ch << std::endl;
            return false;
        }
    }
    if (!stack.empty()) {
        std::cout << "Осталось " << stack.size() << " незакрытых '{'" << std::endl;
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
            std::cout << "Элемент '" << element << "' успешно удалён." << std::endl;
        }
        else {
            std::cout << "Элемент '" << element << "' уменьшен на " << count << ". Текущее количество: " << it->second << std::endl;
        }
    }
    else {
        std::cout << "Ошибка: элемент '" << element << "' не найден в множестве." << std::endl;
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
            std::cout << std::setw(a) << "Подмножество :" << std::endl;
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
            std::cout << "Подмножество: " << subset << " (количество: " << count << ") не найдено в другом множестве." << std::endl;
            return false; 
        }
    }
    std::cout << "Множества равны." << std::endl;
    return true;
}
int Set::power() const {
    int count = 0;
    std::cout << "Элементы множества:"<< std::endl;
    for (const auto& element : setElement) {
        count += element.second;
        std::cout << "Элемент: " << element.first << ", Количество: " << element.second << std::endl;
    }
    if (setSubset.empty()) {
        std::cout << "Нет подмножеств."<< std::endl;
    }
    else {
        for (const auto& element : setSubset) {
            count ++;
            std::cout << "Подмножество: " << element.second << std::endl;
        }
    }
    std::cout << "Мощность данного мультимножества: " << count << std::endl;
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
            std::cout << "Ошибка: Недостаточно закрывающих скобок в строке." << std::endl;
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
        std::cout << "Ошибка: переданный указатель на подмножество является null!" << std::endl;
        return;
    }
    if (count <= 0) {
        std::cout << "Ошибка: количество должно быть больше нуля!" << std::endl;
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
        std::cout << "Ошибка: количество должно быть больше нуля!" << std::endl;
        return;
    }
    auto it = setElement.find(element);
    if (it != setElement.end()) {
        it->second += count;
        std::cout << "Успешно обновлено: элемент '" << element << "' уже существует, новое количество: " << it->second << std::endl;
    }
    else {
        setElement[element] = count;
    }
}
void showBoolean(const std::vector<Set> boolean) {

    if (boolean.empty()) {
        std::cout << "Нет подмножеств для отображения." << std::endl;
        return;
    }
    for (auto it = boolean.begin(); it != boolean.end(); ++it) {
        it->show();
    }
}
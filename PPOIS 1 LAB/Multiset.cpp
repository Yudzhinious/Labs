#include "Multiset.h"

std::map<char, int> Set::getElements() {
    return setElement;
}

std::map<Set*, int> Set::getSubsets() {
    return setSubset;
}

int Subset(const std::string& str);
Set::Set() {}
Set::~Set() {}

int get(const std::vector<Set*>& vect, int& set1, int& set2) {
    if (vect.size() < 2) {
        std::cout << "Задано менее двух множеств" << std::endl;
        return -1;
    }

    while (true) {
        std::cout << "Введите номера двух различных множеств (от 1 до " << vect.size() << "): ";
        std::cin >> set1 >> set2;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Ошибка ввода. Пожалуйста, введите целые числа." << std::endl;
            continue; 
        }

        if (set1 > 0 && set2 > 0 && set1 != set2 && set1 <= vect.size() && set2 <= vect.size()) {
            return set1;
        }
        else {
            std::cout << "Некорректные значения. Убедитесь, что номера находятся в диапазоне и различаются." << std::endl;
        }
    }
}

int get(const std::vector<Set*>& mas, int set) {
    if (!mas.empty()) {
        std::cout << "Введите номер множества: ";
        std::cin >> set;
        if (set > 0 && set <= mas.size()) {
            return set;
        }
        else {
            std::cout << "Некорректное значение" << std::endl;
        }
    }
    else {
        std::cout << "Ни одного множества не задано" << std::endl;
    }
    return -1;
}
Set::Set(const std::string& string) {                                    
    for (int i = 1; i < string.size(); i++) {
        if (string[i] == '{') {
            int count = Subset(string.substr(i + 1));
            setSubset[new Set(string.substr(i, count))]++;
            count = 1;
            while (count > 0) {
                i++;
                if (string[i] == '}') {
                    count--;
                }
                else if (string[i] == '{') {
                    count++;
                }
            }
        }
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            setElement[(string[i])]++;
        }
    }
}
Set::Set(const char*& string) {                                                                                            
    std::string str = string;
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == '{') {
            int count = Subset(str.substr(i + 1));
            setSubset[new Set(str.substr(i, count))]++;
            count = 1;
            while (count > 0) {
                i++;
                if (str[i] == '}') count--;
                else if (str[i] == '{') count++;
            }
        }
        if (str[i] >= 'a' && str[i] <= 'z') {
            setElement[(str[i])]++;
        }
    }
}
void Set::removeDuplicateSubsets() {
    std::map<Set*, int> dupleSet;
    for (const std::pair<Set*, int>& element : setSubset) {
        auto it = dupleSet.find(element.first);

        if (it != dupleSet.end()) {
            it->second += element.second; 
        }
        else {
            dupleSet[element.first] = element.second; 
        }
    }
    setSubset.clear();
    for (const std::pair<Set*, int>& dupleElement : dupleSet) {
        setSubset.emplace(dupleElement.first, dupleElement.second);
    }
}

void Set::clear() {
    setElement.clear(); 
    setSubset.clear();
    std::cout << "Множество очищено." << std::endl;
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
        std::cout << "{  }" << std::endl;
        return;
    }
    std::cout << std::setw(a) << " " << "{ ";
    if (!setElement.empty()) {
        for (const auto& element : setElement) {
            std::cout << std::setw(a) << "(" << element.first << " : " << element.second << ") ";
        }
    }
    if (!setSubset.empty()) {
        std::cout << std::setw(a) << std::endl;
        for (const auto& subset : setSubset) {
            std::cout << std::setw(a) << "Подмножество (" << subset.second << "):" << std::endl;
            subset.first->show(a);
        }
    }
    std::cout << " }" << std::endl;
}
bool Set::operator==(const Set& set2) const {
    if (setElement != set2.setElement) {
        return false; 
    }

    if (setSubset.size() != set2.setSubset.size()) {
        return false;
    }

    for (const auto& subsetEntry : setSubset) {
        const Set* subset = subsetEntry.first;
        int count = subsetEntry.second; 

        bool found = false; 
        for (const auto& otherSubsetEntry : set2.setSubset) {
            if ((*otherSubsetEntry.first == *subset) && (otherSubsetEntry.second == count)) {
                found = true;
                break; 
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
    
    
}
void Set::power()  {
    int count = 0;
    for (auto element : setElement) {
        count += element.second;
    }
    for (auto element : setSubset) {
        count += element.second;
    }
    std::cout << "Мощность данного множества : " << count << std::endl;

}
Set& Set::operator[](const std::string& str) {
    if (str.size() == 1) {
        char ch = str[0];
        if (setElement.find(ch) != setElement.end()) {
            std::cout << "Элемент '" << ch << "' существует в мультимножестве." << std::endl;
            return *this;
        }
    }

    auto element = new Set(str);
    for (const auto& subsetElem : setSubset) {
        if (*subsetElem.first == *element) {
            std::cout << "Подмножество существует в множестве." << std::endl;
            return *this;
        }
    }

    std::cout << "Элемент отсутствует в мультимножество." << std::endl;
    return *this;
}
Set Set::unionElements(const Set& other) const {
    Set result = *this;

    for (const auto& elem : other.setElement) {
        result.setElement[elem.first] = std::max(result.setElement[elem.first], elem.second);
    }
    return result;
}

Set Set::unionSubsets(const Set& other) const {
    Set result = *this;
    result.setSubset.insert(setSubset.begin(), setSubset.end());

    for (const auto& otherSubset : other.setSubset) {
        bool exists = false;

        for (const auto& elem : result.setSubset) {
            if (*elem.first == *otherSubset.first) {
                result.setSubset[elem.first] = std::max(elem.second, otherSubset.second);
                exists = true;
                break;
            }
        }
        if (!exists) {
            result.setSubset[otherSubset.first] = otherSubset.second;
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
Set Set::intersectSubsets(const Set& other) const {
    Set result;

    for (const auto& elem : setSubset) {
        auto it = std::find_if(other.setSubset.begin(), other.setSubset.end(),
            [&elem](const auto& otherElem) { return *elem.first == *otherElem.first; });

        if (it != other.setSubset.end()) {
            result.setSubset[elem.first] = std::min(elem.second, it->second);
        }
    }
    return result; 
}
Set Set::operator*(const Set* set) const {
    Set result = intersectElements(*set);
    Set subsetResult = intersectSubsets(*set); 

    result.setSubset.insert(subsetResult.setSubset.begin(), subsetResult.setSubset.end());
    return result; 
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
Set Set::operator=(const Set* set) {
    setElement = set->setElement;
    setSubset = set->setSubset;
    return *this;
}
int Subset(const std::string& string) {
    int braceCount = 1;
    size_t i;
    for (i = 0; braceCount > 0; i++) {
        if (i >= string.size()) {
            std::cerr << "Ошибка: Недостаточно закрывающих скобок в строке." << std::endl;
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
void showBoolean(const std::vector<Set> boolean) {
    std::cout << "Булеан:" << std::endl;
    if (boolean.empty()) {
        std::cout << "Нет подмножеств для отображения." << std::endl;
        return;
    }
    for (auto it = boolean.begin(); it != boolean.end(); ++it) {
        it->show(); 
    }
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
std::vector<Set> Set::boolean() const {
    std::vector<Set> boolean;
    boolean.push_back(Set());

    size_t initialSize = boolean.size(); 
    for (const auto& elem : setElement) {
        size_t currentSize = boolean.size();
        for (size_t i = 0; i < currentSize; i++) {
            Set newSet = boolean[i];
            newSet.add(elem.first, elem.second);
            boolean.push_back(newSet);
        }
    }

    for (const auto& sub : setSubset) {
        size_t currentSize = boolean.size();
        for (size_t i = 0; i < currentSize; i++) {
            Set newSet = boolean[i];
            newSet.add(sub.first, sub.second);
            boolean.push_back(newSet);
        }
    }

    return boolean;
}
#include "Set.h"

void CreateSet(std::vector<Set*>& vect);
void SetShow(const std::vector<Set*>& vect);
void AddElement(const std::vector<Set*>& vect);
void SetPower(const std::vector<Set*>& vect);
void DeleteElement(const std::vector<Set*>& vect);
void SetUnion(std::vector<Set*>& vect);
void SetIntersection(std::vector<Set*>& vect);
void SetDifference(std::vector<Set*>& vect);
void SetCheck(const std::vector<Set*>& vect);
void DeleteSet(const std::vector<Set*>& vect);
void ShowBoolean(std::vector<Set*>& vect);
int get(const std::vector<Set*>& mas, int& first, int& second);
int get(const std::vector<Set*>& mas, int first);

int main() {
	setlocale(LC_ALL, "RU");
	std::vector <Set*> vect;
	while (1)
	{
		int choice = 0;
		std::cout << "  1 - создание/добавление нового множества " << std::endl;
		std::cout << "  2 - вывод всех множеств на экран  " << std::endl;
		std::cout << "  3 - добавление нового элемента " << std::endl;
		std::cout << "  4 - проверка множества на наличие элемента " << std::endl;
		std::cout << "  5 - нахождение булеана множества " << std::endl;
		std::cout << "  6 - нахождение объединения множеств " << std::endl;
		std::cout << "  7 - нахождение пересечения множеств " << std::endl;
		std::cout << "  8 - нахождение разности множеств " << std::endl;
		std::cout << "  9 - нахождение мощности множества " << std::endl;
		std::cout << " 10 - удаление элемента множества " << std::endl;
		std::cout << " 11 - очистка множества " << std::endl;
		std::cout << "  0 - выход из программы " << std::endl;

		std::cout << "Выберите номер необходимой команды: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
		{
			CreateSet(vect);
			break;
		}

		case 2:
		{
			SetShow(vect);
			break;
		}

		case 3:
		{
			AddElement(vect);
			break;
		}

		case 4:
		{
			SetCheck(vect);
			break;
		}

		case 5:
		{
			ShowBoolean(vect);
		}

		case 6:
		{
			SetUnion(vect);
			break;
		}

		case 7:
		{
			SetIntersection(vect);
			break;
		}

		case 8:
		{
			SetDifference(vect);
			break;
		}

		case 9:
		{
			SetPower(vect);
			break;
		}

		case 10:
		{
			DeleteElement(vect);
			break;
		}

		case 11:
		{
			DeleteSet(vect);
			break;
		}
		case 0:
		{
			vect.clear();
			return 0;
		}
		default:
			std::cout << "Некорректный ввод. Пожалуйста, выберите существующую команду." << std::endl;
			break;

		}
	}

	return 0;
}

int get(const std::vector<Set*>& vect, int& set1, int& set2) {
	if (vect.size() < 2) {
		std::cout << "Задано менее двух множеств" << std::endl;
		return -1;
	}

	while (true) {
		std::cout << "Введите номера двух различных множеств (от 1 до " << vect.size() << "): ";
		std::cin >> set1 >> set2;
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
void CreateSet(std::vector<Set*>& vect) {
	std::string input;
	do {
		std::getline(std::cin, input);
	} while (input.empty());

	if (isBracket(input)) {
		auto newSet1 = new Set(input);
		newSet1->removeDuplicateSubsets();
		vect.push_back(newSet1);
	}
	else {
		std::cout << "Проверьте правильность ввода '}'" << std::endl;
	}
}

void SetShow(const std::vector<Set*>& vect) {
	int choice = 0;
	std::cout << "Введите номер выводимого множества :" << std::endl;
	std::cin >> choice;
	if (!vect.empty()) {
		for (int i = 0; i < vect.size(); i++) {
			if (i + 1 == choice) {
				std::cout << "Множество " << i + 1 << ": ";
				vect[i]->show();
			}
		}
	}
	else {
		std::cout << "Множества не были заданы." << std::endl;
	}
}

void AddElement(const std::vector<Set*>& vect) {
	int choice = get(vect, 0);
	if (choice > 0 && choice <= vect.size()) {
		std::string inputElement;
		std::cout << "Введите элемент для добавления в множество " << choice << ": ";

		while (true) {
			std::getline(std::cin, inputElement);
			if (!inputElement.empty()) {
				break;
			}
		}
		if (inputElement.size() == 1) {
			vect[choice - 1]->add(inputElement[0]);
		}
		else {
			std::cout << "Введите только один символ." << std::endl;
		}
	}
}
void SetCheck(const std::vector<Set*>& vect) {
	int first = 0, count = 0;
	first = get(vect, first);

	if (first > 0) {
		std::string str;
		std::cout << "Наличие какого элемента вы хотите проверить?" << std::endl;
		do {
			std::getline(std::cin, str);
			if (str != " ") {
				count++;
			}
		} while (str.empty());
	}
	if (count != 0) {
		std::cout << "Элемент существует во множестве" << std::endl;
	}
}
void ShowBoolean(std::vector<Set*>& vect) {
	int choice = 0, count = 0;
	choice = get(vect, choice);
	std::cout << "Введите необходимое количество раз для проверки булеана :" << std::endl;
	std::cin >> count;
	for (int i = 0; i < count; i++) {
		if (choice != 0) {
			std::vector<Set> boolean = vect[choice - 1]->boolean();
			showBoolean(boolean);
		}
		else {
			std::cout << "Некорректный выбор множества" << std::endl;
		}
	}
}

void SetUnion(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set());
		*vect.back() = *(vect[first - 1]) + vect[sec - 1];
		vect.back()->show();
	}
	else {
		std::cout << " Ошибка ввода двух множеств" << std::endl;
	}
}

void SetIntersection(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set());
		*vect.back() = *vect[first - 1] * vect[sec - 1];
		vect.back()->show();
	}
	else {
		std::cout << " Ошибка ввода двух множеств" << std::endl;
	}
}

void SetDifference(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set(*vect[first - 1]));
		*vect.back() = *vect[first - 1] - vect[sec - 1];
		vect.back()->show();
	}
	else {
		std::cout << " Ошибка ввода двух множеств" << std::endl;
	}
}
void SetPower(const std::vector<Set*>& vect) {
	int choice = 0;
	choice = get(vect, choice);

	if (choice > 0) {
		std::cout << "Вы выбрали множество: " << std::endl;
		vect[choice - 1]->show(2);
		char confirm;
		std::cout << "Подсчитать мощность для " << choice << " множества ?" << std::endl;
		std::cin >> confirm;
		if (confirm == 'y'  || confirm == 'Y') {
			vect[choice - 1]->power();
		}
		else {
			std::cout << "Мощность множества не вычислена." << std::endl;
		}
	}
	else {
		std::cout << "Некорректный выбор множества. Выберите правильный номер." << std::endl;
	}
}
void DeleteElement(const std::vector<Set*>& vect) {
	int choice = 0;
	choice = get(vect, choice);

	if (choice > 0) {
		std::string str;
		int count = 1;
		std::cout << "Выберите элемент для удаления из множества: ";
		do {
			std::getline(std::cin, str);
		} while (str.empty() || str.size() > 1);

		std::cout << "Введите количество для удаления: ";
		std::string countI;
		std::getline(std::cin, countI);
		if (!countI.empty()) {
			count = std::stoi(countI);
		}

		vect[choice - 1]->deleteElement(str[0], count);
	}
}
void DeleteSet(const std::vector<Set*>& vect) {
	int first = 0;
	first = get(vect, first);
	if (first > 0 && first <= vect.size()) {
		vect[first - 1]->clear();

		std::cout << "Оставшиеся множества:" << std::endl;
		for (const auto& set : vect) {
			if (set) {
				set->show();
			}
		}
	}
	else {
		std::cout << "Ошибка: неверный индекс." << std::endl;
	}
}
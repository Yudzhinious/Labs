#include "Multiset.h"

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
void ShowBoolean (std::vector<Set*>& vect);

int main() {
	setlocale(LC_ALL, "RU");
	std::vector <Set*> vect;
	while (1)
	{
		int choice = 0;
		std::cout << "  1 - создание/добавление нового множества " << std::endl;
		std::cout << "  2 - вывод всех множеств на экран  " << std::endl;
		std::cout << "  3 - добавление нового элемента " << std::endl;
		std::cout << "  4 - проверка множества на наличие определенного элемента " << std::endl;
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
			std::cout << "Некорректный ввод. Пожалуйста, выберите существующую команду."<< std::endl;
			break;

		}
		}

	return 0;
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
		std::cout << "Множество содержит ошибку, проверьте правильность ввода '}'" << std::endl;
	}
}

void SetShow(const std::vector<Set*>& vect) {
	if (!vect.empty()) {
		for (int i = 0; i < vect.size(); i++) {
			std::cout << "Множество " << i + 1 << ": ";
			vect[i]->show();
		}
	}
	else {
		std::cout << "Множества не были заданы." << std::endl;
	}
}

void AddElement(const std::vector<Set*>& vect) {
	int first = 0;
	first = get(vect, first);
	if (first > 0) {
		std::string str;
		std::cout << "Введите элемент для добавления: ";
		do {
			std::getline(std::cin, str);
		} while (str.empty());

		vect[first - 1]->add(str[0]);
	}
}

void SetCheck(const std::vector<Set*>& vect) {
	int first = 0;
	first = get(vect, first);

	if (first > 0) {
		std::string str;
		std::cout << "Наличие какого элемента вы хотите проверить?" << std::endl;
		do {
			std::getline(std::cin, str);
		} while (str.empty());

		(*vect[first - 1])[str];
	}
}

void ShowBoolean(std::vector<Set*>& vect) {
	int first = 0;
	first = get(vect, first);

	if (first > 0) {
		std::vector<Set> powerSet = vect[first - 1]->boolean();
		showBoolean(powerSet);
	}
	else {
		std::cout << "Некорректный выбор множества." << std::endl;
	}
}

void SetUnion(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set());
		*vect.back() = *(vect[first - 1]) + vect[sec - 1];
		std::cout << "Результат записан в " << vect.size() << " множество." << std::endl;
	}
}

void SetIntersection(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set());
		*vect.back() = *vect[first - 1] * vect[sec - 1];
		std::cout << "Результат выполнения операции был добавлен как " << vect.size() << " множество." << std::endl;
	}
}

void SetDifference(std::vector<Set*>& vect) {
	int first = 0, sec = 0;
	first = get(vect, first, sec);
	if (first > 0) {
		vect.push_back(new Set(*vect[first - 1]));
		*vect.back() = *vect[first - 1] - vect[sec - 1];
		std::cout << "Результат выполнения операции был добавлен как " << vect.size() << " множество." << std::endl;
	}
}

void SetPower(const std::vector<Set*>& vect) {
	int first = 0;
	first = get(vect, first);

	if (first > 0) {
		std::cout << "Вы выбрали множество: " << std::endl;
		vect[first - 1]->show(2);
		char confirm;
		std::cin >> confirm;

		if (confirm == 'y' || confirm == 'Y') {
			vect[first - 1]->power();
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
	int first = 0;
	first = get(vect, first);

	if (first > 0) {
		std::string str;
		int count = 1;

		std::cout << "Выберите элемент для удаления из множества: ";
		do {
			std::getline(std::cin, str);
		} while (str.empty() || str.size() > 1);

		std::cout << "Введите количество для удаления (по умолчанию 1): ";
		std::string countInput;
		std::getline(std::cin, countInput);
		if (!countInput.empty()) {
			count = std::stoi(countInput);
		}

		vect[first - 1]->deleteElement(str[0], count);
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
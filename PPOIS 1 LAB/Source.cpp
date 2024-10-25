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
		std::cout << "  1 - ��������/���������� ������ ��������� " << std::endl;
		std::cout << "  2 - ����� ���� �������� �� �����  " << std::endl;
		std::cout << "  3 - ���������� ������ �������� " << std::endl;
		std::cout << "  4 - �������� ��������� �� ������� �������� " << std::endl;
		std::cout << "  5 - ���������� ������� ��������� " << std::endl;
		std::cout << "  6 - ���������� ����������� �������� " << std::endl;
		std::cout << "  7 - ���������� ����������� �������� " << std::endl;
		std::cout << "  8 - ���������� �������� �������� " << std::endl;
		std::cout << "  9 - ���������� �������� ��������� " << std::endl;
		std::cout << " 10 - �������� �������� ��������� " << std::endl;
		std::cout << " 11 - ������� ��������� " << std::endl;
		std::cout << "  0 - ����� �� ��������� " << std::endl;

		std::cout << "�������� ����� ����������� �������: ";
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
			std::cout << "������������ ����. ����������, �������� ������������ �������." << std::endl;
			break;

		}
	}

	return 0;
}

int get(const std::vector<Set*>& vect, int& set1, int& set2) {
	if (vect.size() < 2) {
		std::cout << "������ ����� ���� ��������" << std::endl;
		return -1;
	}

	while (true) {
		std::cout << "������� ������ ���� ��������� �������� (�� 1 �� " << vect.size() << "): ";
		std::cin >> set1 >> set2;
		if (set1 > 0 && set2 > 0 && set1 != set2 && set1 <= vect.size() && set2 <= vect.size()) {
			return set1;
		}
		else {
			std::cout << "������������ ��������. ���������, ��� ������ ��������� � ��������� � �����������." << std::endl;
		}
	}
}
int get(const std::vector<Set*>& mas, int set) {
	if (!mas.empty()) {
		std::cout << "������� ����� ���������: ";
		std::cin >> set;
		if (set > 0 && set <= mas.size()) {
			return set;
		}
		else {
			std::cout << "������������ ��������" << std::endl;
		}
	}
	else {
		std::cout << "�� ������ ��������� �� ������" << std::endl;
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
		std::cout << "��������� ������������ ����� '}'" << std::endl;
	}
}

void SetShow(const std::vector<Set*>& vect) {
	int choice = 0;
	std::cout << "������� ����� ���������� ��������� :" << std::endl;
	std::cin >> choice;
	if (!vect.empty()) {
		for (int i = 0; i < vect.size(); i++) {
			if (i + 1 == choice) {
				std::cout << "��������� " << i + 1 << ": ";
				vect[i]->show();
			}
		}
	}
	else {
		std::cout << "��������� �� ���� ������." << std::endl;
	}
}

void AddElement(const std::vector<Set*>& vect) {
	int choice = get(vect, 0);
	if (choice > 0 && choice <= vect.size()) {
		std::string inputElement;
		std::cout << "������� ������� ��� ���������� � ��������� " << choice << ": ";

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
			std::cout << "������� ������ ���� ������." << std::endl;
		}
	}
}
void SetCheck(const std::vector<Set*>& vect) {
	int first = 0, count = 0;
	first = get(vect, first);

	if (first > 0) {
		std::string str;
		std::cout << "������� ������ �������� �� ������ ���������?" << std::endl;
		do {
			std::getline(std::cin, str);
			if (str != " ") {
				count++;
			}
		} while (str.empty());
	}
	if (count != 0) {
		std::cout << "������� ���������� �� ���������" << std::endl;
	}
}
void ShowBoolean(std::vector<Set*>& vect) {
	int choice = 0, count = 0;
	choice = get(vect, choice);
	std::cout << "������� ����������� ���������� ��� ��� �������� ������� :" << std::endl;
	std::cin >> count;
	for (int i = 0; i < count; i++) {
		if (choice != 0) {
			std::vector<Set> boolean = vect[choice - 1]->boolean();
			showBoolean(boolean);
		}
		else {
			std::cout << "������������ ����� ���������" << std::endl;
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
		std::cout << " ������ ����� ���� ��������" << std::endl;
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
		std::cout << " ������ ����� ���� ��������" << std::endl;
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
		std::cout << " ������ ����� ���� ��������" << std::endl;
	}
}
void SetPower(const std::vector<Set*>& vect) {
	int choice = 0;
	choice = get(vect, choice);

	if (choice > 0) {
		std::cout << "�� ������� ���������: " << std::endl;
		vect[choice - 1]->show(2);
		char confirm;
		std::cout << "���������� �������� ��� " << choice << " ��������� ?" << std::endl;
		std::cin >> confirm;
		if (confirm == 'y'  || confirm == 'Y') {
			vect[choice - 1]->power();
		}
		else {
			std::cout << "�������� ��������� �� ���������." << std::endl;
		}
	}
	else {
		std::cout << "������������ ����� ���������. �������� ���������� �����." << std::endl;
	}
}
void DeleteElement(const std::vector<Set*>& vect) {
	int choice = 0;
	choice = get(vect, choice);

	if (choice > 0) {
		std::string str;
		int count = 1;
		std::cout << "�������� ������� ��� �������� �� ���������: ";
		do {
			std::getline(std::cin, str);
		} while (str.empty() || str.size() > 1);

		std::cout << "������� ���������� ��� ��������: ";
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

		std::cout << "���������� ���������:" << std::endl;
		for (const auto& set : vect) {
			if (set) {
				set->show();
			}
		}
	}
	else {
		std::cout << "������: �������� ������." << std::endl;
	}
}
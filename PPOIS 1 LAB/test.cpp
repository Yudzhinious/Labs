#include "pch.h"
#include "../PPOIS1lab/Set.h"
#include "../PPOIS1lab/Set.cpp"

TEST(MultisetTest, DefaultConstructor) {
    Set multiset;
    EXPECT_TRUE(multiset.getElements().empty());
}
TEST(MultisetTest, AddElement) {
    Set multiset;
    multiset.add('a', 3);
    multiset.add('z', 1);

    std::map<char, int> expected = { {'a', 3}, {'z', 1} };
    EXPECT_EQ(multiset.getElements(), expected);
}
TEST(MultisetTest, AddSubset) {
    Set multiset;
    Set* addedSubset = new Set();
    multiset.add(addedSubset, 1);

    EXPECT_EQ(multiset.getSubsets().size(), 1);
}
TEST(MultisetTest, RemoveElement) {
    Set multiset;
    multiset.add('a', 4);
    multiset.deleteElement('a', 2);

    std::map<char, int> expected = { {'a', 2} };
    EXPECT_EQ(multiset.getElements(), expected);
}
TEST(MultisetTest, RemoveElements) {
    Set multiset;
    multiset.add('a', 3);
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    multiset.deleteElement('a', 1);
    std::cout.rdbuf(oldCout);
    std::map<char, int> expected = { {'a', 2} };

    EXPECT_EQ(multiset.getElements(), expected);
    ASSERT_EQ(output.str(), "Элемент 'a' уменьшен на 1. Текущее количество: 2\n");

    output.str("");
    oldCout = std::cout.rdbuf(output.rdbuf());
    multiset.deleteElement('a', 2);
    std::cout.rdbuf(oldCout);

    EXPECT_TRUE(multiset.getElements().empty());
    ASSERT_EQ(output.str(), "Элемент 'a' успешно удалён.\n");

    output.str("");
    oldCout = std::cout.rdbuf(output.rdbuf());
    multiset.deleteElement('a', 1);
    std::cout.rdbuf(oldCout);

    ASSERT_EQ(output.str(), "Ошибка: элемент 'a' не найден в множестве.\n");
}
TEST(SubsetTest, ValidSimpleSubset) {
    std::string input = "{a,b,c}";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, -1);
}
TEST(SubsetTest, ValidNestedSubset) {
    std::string input = "{a,{b,c}}";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, -1);
}
TEST(SubsetTest, ValidMultipleSubsets) {
    std::string input = "{{a,b},{c}}";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, -1);
}
TEST(SubsetTest, EmptyString) {
    std::string input = "";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, -1);
}
TEST(SubsetTest, SingleOpeningBrace) {
    std::string input = "{";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, -1);
}
TEST(SubsetTest, CorrectBraceSequence) {
    std::string input = "{}}";
    int result = numberOfSubsets(input);
    EXPECT_EQ(result, 3);
}
TEST(MultisetTest, PowerSet) {
    Set multiset;
    multiset.add('a', 1);
    multiset.add('b', 1);

    std::vector<Set> powerSet = multiset.boolean();
    EXPECT_EQ(powerSet.size(), 4);
}
TEST(MultisetTest, EqualityTest) {
    Set multiset1;
    multiset1.add('a', 2);
    multiset1.add('b', 1);

    Set multiset2;
    multiset2.add('a', 2);
    multiset2.add('b', 1);

    EXPECT_TRUE(multiset1 == multiset2);

    Set subset1;
    subset1.add('c', 1);
    multiset1.add(&subset1, 1);

    Set subset2;
    subset2.add('c', 1);
    multiset2.add(&subset2, 1);

    EXPECT_TRUE(multiset1 == multiset2);

    multiset1.add('a', 1);
    EXPECT_TRUE(multiset1 == multiset2);

    multiset2.clear();
    EXPECT_FALSE(multiset1 == multiset2);
}
TEST(MultisetTest, ConstructorAndPrint) {
    std::string input = "{a, b, c, {o,a,s,k},d, {r, k}, {{a}, m}}";
    Set multiset(input);

    ASSERT_EQ(multiset.getElements().size(), 4);
}
TEST(MultisetTest, ConstructorCharAndPrint) {
    char* input = new char[100];
    input = "{a, b, c, {o,a,s,k},d, {r, k}, {{a}, m}}";
    Set multiset(input);

    ASSERT_EQ(multiset.getElements().size(), 4);
}
TEST(MultisetTest, removeDuplicateSubsets) {
    std::string input = "{{a}, {a}, {b}}";
    Set multiset(input);
    multiset.removeDuplicateSubsets();

    ASSERT_EQ(multiset.getElements().size(), 0);
}
TEST(MultisetTest, IsBracketValidCases) {
    std::string validSet1 = "{a, b, {c, d}}";
    std::string validSet2 = "{{ }}";
    std::string validSet3 = "{}";

    ASSERT_TRUE(isBracket(validSet1));
    ASSERT_TRUE(isBracket(validSet2));
    ASSERT_TRUE(isBracket(validSet3));
}
TEST(MultisetTest, IsBracketInvalidCases) {
    std::string invalidSet1 = "{a, b, {c, d}";
    std::string invalidSet2 = "{a, b, {c, d}}}";
    std::string invalidSet3 = "{a, b, [c, d]}";
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    ASSERT_FALSE(isBracket(invalidSet1));
    ASSERT_STREQ(output.str().c_str(), "Осталось 1 незакрытых '{'\n");
    output.str("");

    ASSERT_FALSE(isBracket(invalidSet2));
    ASSERT_STREQ(output.str().c_str(), "Ошибка\n");
    output.str("");

    ASSERT_FALSE(isBracket(invalidSet3));
    ASSERT_STREQ(output.str().c_str(), "Не правильный символ: [\n");

    std::cout.rdbuf(oldCout);
}
TEST(MultisetTest, ClearFunction) {
    Set multiset;
    multiset.add('a', 1);
    multiset.add('b', 2);

    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    multiset.clear();
    std::cout.rdbuf(oldCout);

    EXPECT_TRUE(multiset.getElements().empty());
    EXPECT_TRUE(multiset.getSubsets().empty());
    ASSERT_EQ(output.str(), "Множество очищено.\n");
}
TEST(MultisetTest, Power) {
    std::string input = "{a, b, b, n, {c, d}}";
    Set multiset(input);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    int result = multiset.power();

    std::cout.rdbuf(old);
    ASSERT_EQ(result, 5);
}
TEST(MultisetTest, BooleanTest) {
    std::string input = "{a, b}";
    Set multiset(input);

    auto powerSet = multiset.boolean();

    ASSERT_EQ(powerSet.size(), 4);
}
TEST(multiset, Plus) {
    std::string input = "{aaa}";
    std::string input2 = "{bob}";
    Set* multiset1 = new Set(input);
    Set* multiset2 = new Set(input2);

    *multiset2 += multiset1;
    EXPECT_EQ(multiset2->getElements().size(), 3);
}
TEST(MultisetTest, UnionElements) {
    Set multiset1;
    multiset1.add('a', 2);
    multiset1.add('b', 1);

    Set multiset2;
    multiset2.add('b', 3);
    multiset2.add('c', 1);

    Set result = multiset1.unionElements(multiset2);
    std::map<char, int> expected = { {'a', 2}, {'b', 3}, {'c', 1} };

    EXPECT_EQ(result.getElements(), expected);
}

TEST(MultisetTest, UnionSubsets) {
    Set multiset1;
    Set subset1;
    subset1.add('a', 1);
    multiset1.add(&subset1, 2);

    Set multiset2;
    Set subset2;
    subset2.add('a', 3);
    subset2.add('b', 1);
    multiset2.add(&subset2, 1);

    Set result = multiset1.unionSubsets(multiset2);

    std::map<Set*, int> expected = { {&subset1, 2}, {&subset2, 1} };

    EXPECT_EQ(result.getSubsets(), expected);
}
TEST(MultisetTest, Plus) {
    std::string input1 = "{akk{lgo}}";
    std::string input2 = "{aoa{sos}}";
    Set* multiset1 = new Set(input1);
    Set* multiset2 = new Set(input2);

    Set result = *multiset2 + multiset1;
    std::map<char, int> expected = { {'a', 2}, {'o', 1}, {'k', 2} };

    EXPECT_EQ(result.getElements(), expected);
    EXPECT_EQ(result.getSubsets().size(), 2);

}
TEST(MultisetTest, IntersectElements) {
    Set multiset1;
    multiset1.add('d', 1);
    multiset1.add('b', 3);
    multiset1.add('c', 1);

    Set multiset2;
    multiset2.add('b', 2);
    multiset2.add('c', 3);
    multiset2.add('d', 1);

    Set result = multiset1.intersectElements(multiset2);
    std::map<char, int> expected = { {'b', 2}, {'c', 1}, {'d', 1} };

    EXPECT_EQ(result.getElements(), expected);
}
TEST(MultisetTest, OperatorMultiply) {
    Set multiset1;
    multiset1.add('a', 2);
    multiset1.add('b', 4);

    Set multiset2;
    multiset2.add('b', 3);
    multiset2.add('c', 1);

    Set result = multiset1 * &multiset2;
    std::map<char, int> expectedElements = { {'b', 3} };

    EXPECT_EQ(result.getElements(), expectedElements);
    EXPECT_TRUE(result.getSubsets().empty());
}
TEST(MultisetTest, ShowEmptySet) {
    Set emptySet;
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    emptySet.show(2);

    std::cout.rdbuf(old);
    ASSERT_EQ(buffer.str(), "{   }\n");
}
//TEST(MultisetTest, GetTwoDifferentSetsCorrectInput) {
//    Set set1, set2;
//    std::vector<Set*> vect = { &set1, &set2 };
//
//    std::stringstream input("1 2\n");
//    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
//    int s1, s2;
//
//    int result = get(vect, s1, s2);
//
//    std::cin.rdbuf(oldCin);
//    ASSERT_EQ(result, 1);
//    ASSERT_EQ(s1, 1);
//    ASSERT_EQ(s2, 2);
//}
//TEST(MultisetTest, GetSingleSetCorrectInput) {
//    Set set1;
//    std::vector<Set*> mas = { &set1 };
//    std::stringstream input("1\n");
//    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
//    int set = 0;
//    int result = get(mas, set);
//
//    std::cin.rdbuf(oldCin);
//    ASSERT_EQ(result, 1);
//}
//TEST(MultisetTest, GetSingleSetIncorrectInput) {
//    Set set1;
//    std::vector<Set*> mas = { &set1 };
//    std::stringstream input("2\n1\n");
//    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
//    int set = 0;
//
//    int result = get(mas, set);
//
//    std::cin.rdbuf(oldCin);
//    ASSERT_EQ(result, -1);
//}
TEST(MultisetTest, BooleanFunction) {
    Set multiset;

    std::vector<Set> booleanResult = multiset.boolean();
    EXPECT_EQ(booleanResult.size(), 1);
    multiset.add('a', 2);
    multiset.add('b', 1);
    booleanResult = multiset.boolean();
    EXPECT_GE(booleanResult.size(), 4);
    EXPECT_EQ(booleanResult[0].getElements().size(), 0);
    EXPECT_EQ(booleanResult[1].getElements().size(), 1);
    Set subset;
    subset.add('c', 1);
    multiset.add(&subset, 1);

    booleanResult = multiset.boolean();
    EXPECT_GE(booleanResult.size(), 8);
}
TEST(MultisetTest, ShowBooleanFunction) {
    Set multiset;
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    std::vector<Set> emptyVector;
    showBoolean(emptyVector);
    EXPECT_EQ(output.str(), "Нет подмножеств для отображения.\n");

    std::cout.rdbuf(oldCout);
    Set nonEmptySubset;
    nonEmptySubset.add('d', 1);
    output.str("");
    std::vector<Set> nonEmptyVector = { nonEmptySubset };
    showBoolean(nonEmptyVector);
    EXPECT_FALSE(output.str().find("Элементы: d: 1") != std::string::npos);
}
TEST(MultisetTest, OperatorMultiplyAssign) {
    Set multiset1;
    multiset1.add('a', 2);
    multiset1.add('b', 4);

    Set multiset2;
    multiset2.add('b', 3);
    multiset2.add('c', 1);

    multiset1 *= &multiset2;
    std::map<char, int> expectedElements = { {'a', 2},{ 'b', 4},{'c',1} };

    EXPECT_EQ(multiset1.getElements(), expectedElements);
    EXPECT_TRUE(multiset1.getSubsets().empty());
}
TEST(MultisetTest, SubtractElements) {
    Set multiset1;
    multiset1.add('a', 5);
    multiset1.add('b', 3);
    multiset1.add('c', 2);

    Set multiset2;
    multiset2.add('b', 1);
    multiset2.add('c', 3);

    Set result = multiset1.subtractElements(multiset2);
    std::map<char, int> expected = { {'a', 5}, {'b', 2} };

    EXPECT_EQ(result.getElements(), expected);
}
TEST(MultisetTest, OperatorSubtract) {
    Set multiset1;
    multiset1.add('a', 5);
    multiset1.add('b', 3);

    Set multiset2;
    multiset2.add('b', 1);
    multiset2.add('c', 2);

    Set result = multiset1 - &multiset2;
    std::map<char, int> expectedElements = { {'a', 5}, {'b', 2} };

    EXPECT_EQ(result.getElements(), expectedElements);
    EXPECT_TRUE(result.getSubsets().empty());
}
TEST(MultisetTest, OperatorSubtractAssign) {
    Set multiset1;
    multiset1.add('a', 5);
    multiset1.add('b', 3);

    Set multiset2;
    multiset2.add('b', 1);
    multiset2.add('c', 2);

    multiset1 -= &multiset2;
    std::map<char, int> expectedElements = { {'a', 5}, {'b', 3}, {'c',2} };

    EXPECT_EQ(multiset1.getElements(), expectedElements);
    EXPECT_TRUE(multiset1.getSubsets().empty());
}

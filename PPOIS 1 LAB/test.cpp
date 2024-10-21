#include "pch.h"
#include "../проект_Разгром/Multiset.h"
#include "../проект_Разгром/Multiset.cpp"

TEST(MultisetTest, DefaultConstructor) {
    Set multiset;
    EXPECT_TRUE(multiset.getElements().empty());
}
TEST(MultisetTest, AddElement) {
    Set multiset;
    multiset.add('a', 2);
    multiset.add('b', 1);

    std::map<char, int> expected = { {'a', 2}, {'b', 1} };
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
    multiset.add('a', 3);
    multiset.deleteElement('a', 1);

    std::map<char, int> expected = { {'a', 2} };
    EXPECT_EQ(multiset.getElements(), expected);
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
TEST(MultisetTest, copyConstructor) {
    std::string input = "{a, b, c, {o,a,s,k},d, {r, k}, {{a}, m}}";
    Set multiset(input); 
    Set multiset1(multiset);

    ASSERT_EQ(multiset1.getElements().size(), 4);
}

TEST(MultisetTest, removeDuplicateSubsets) {
    std::string input = "{{a}, {a}, {b}}";
    Set multiset(input);

    multiset.removeDuplicateSubsets();

    ASSERT_EQ(multiset.getElements().size(), 0);

}

TEST(MultisetTest, isBracket) {
    std::string validSet = "{a, b, {c, d}}";
    std::string invalidSet = "{a, b, {c, d}";

    ASSERT_TRUE(isBracket(validSet));
    ASSERT_FALSE(isBracket(invalidSet));
}

TEST(MultisetTest, Power) {
    std::string input = "{a, b, {c, d}}";
    Set multiset(input);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    multiset.power();

    std::cout.rdbuf(old);
    ASSERT_EQ(buffer.str(), "Мощность данного множества : 3\n");
}

TEST(MultisetTest, BooleanTest) {
    std::string input = "{a, b}";
    Set multiset(input);

    auto powerSet = multiset.boolean();

    ASSERT_EQ(powerSet.size(), 4);
}
TEST(MultisetTest, AddMultiset) {
    Set multiset1;
    Set multiset2;
    multiset2.add(&multiset1, 1);
    std::map<Set*, int> expected = { {&multiset1, 1} };

    EXPECT_EQ(multiset2.getElements(), expected);
}
//TEST(MultisetTest, OperatorBrackets) {
//    std::string set1 = "{a, b, {c}}";
//    Set multiset(set1);
//    int result = multiset["a"]; 
//
//    ASSERT_EQ(result, 1);
//}

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
//TEST(MultisetTest, OperatorBreaketsSubsets)
//{
//    std::string set1 = "{a, b, {c}}";
//
//    Set multiset(set1);
//    int result = multiset["{c}"];
//
//    ASSERT_EQ(result, 1);
//}
//
//TEST(MultisetTest, OperatorPlus) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{b, d, {e}}";
//
//    Set multiset1(set1);
//    Set multiset2(set2);
//
//    Set result = multiset1 + std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(result.getElements().size(), 3);
//}

//TEST(MultisetTest, OperatorEqualPlus) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{b, {c}}";
//
//    Multiset multiset1(set1);
//    Multiset multiset2(set2);
//
//    multiset1 += std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(multiset1.getElements().size(), 2);
//    ASSERT_EQ(multiset1.getSubsets().size(), 1);
//}
//TEST(MultisetTest, OperatorMultiply) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{a, {c}}";
//
//    Multiset multiset1(set1);
//    Multiset multiset2(set2);
//
//    Multiset result = multiset1 * std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(result.getElements().size(), 1);
//
//}
//TEST(MultisetTest, OperatorEqualMultiply) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{b, {c}}";
//
//    Multiset multiset1(set1);
//    Multiset multiset2(set2);
//
//    multiset1 *= std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(multiset1.getSubsets().size(), 1);
//    ASSERT_EQ(multiset1.getSubsets().size(), 1);
//}
//
//TEST(MultisetTest, OperatorMinus) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{b, {c}}";
//
//    Multiset multiset1(set1);
//    Multiset multiset2(set2);
//
//    Multiset result = multiset1 - std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(result.getElements().size(), 1);
//
//}
//TEST(MultisetTest, OperatorEqualMinus) {
//    std::string set1 = "{a, b, {c}}";
//    std::string set2 = "{b, {c}}";
//
//    Multiset multiset1(set1);
//    Multiset multiset2(set2);
//
//    multiset1 -= std::make_shared<Multiset>(multiset2);
//
//    ASSERT_EQ(multiset1.getElements().size(), 1);
//    ASSERT_EQ(multiset1.getSubsets().size(), 0);
//}

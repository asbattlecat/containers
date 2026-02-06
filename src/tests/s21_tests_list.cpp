#include <list>

#include "s21_tests.h"

TEST(TestList, DefaultConstructor) {
  s21::list<int> temp;
  EXPECT_EQ(temp.size(), 0);
}

TEST(TestList, ConstructorSize) {
  s21::list<int> temp(10);
  EXPECT_EQ(temp.size(), 10);
}

TEST(TestList, InitializerList) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = temp.begin();
  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }

  s21::list<int> temp_2{1, 2, 3, 4, 5};
  temp_2.clear();
  temp_2.clear();
  EXPECT_TRUE(temp_2.empty());
}

TEST(TestList, InitializerList_Empty) {
  s21::list<int> temp{};
  EXPECT_EQ(temp.size(), 0);
  EXPECT_TRUE(temp.empty());
  EXPECT_EQ(temp.begin(), temp.end());
}

TEST(TestList, InitializerList_NotEmpty) {
  s21::list<int> temp{1, 2, 3, 4, 5};
  EXPECT_EQ(temp.size(), 5);
  auto it = temp.begin();
  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(it, temp.end());
}

TEST(TestList, InitializerList_BreakCondition) {
  s21::list<int> temp{1, 2};
  EXPECT_EQ(temp.size(), 2);
  auto it = temp.begin();
  for (int i = 1; i <= 2; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(it, temp.end());
}

TEST(TestList, CopyConstructor) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> temp_2(temp);
  auto it = temp_2.begin();
  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(temp.size(), temp_2.size());
}

TEST(TestList, CopyConstructor2) {
  s21::list<int> temp;
  s21::list<int> temp_2(temp);
  EXPECT_TRUE(temp_2.empty());
}

TEST(TestList, MoveConstructor) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> temp_2(std::move(temp));
  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(temp_2.size(), 10);
  auto it = temp_2.begin();
  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, Destructor) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  temp.~list();
  EXPECT_EQ(temp.size(), 0);
}

TEST(TestList, OperatorMove) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::list<int> temp_2;
  temp_2 = std::move(temp);
  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(temp_2.size(), 10);
  auto it = temp_2.begin();
  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, FrontMethod) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int i = temp.front();
  EXPECT_EQ(i, 1);
  temp.clear();
  EXPECT_THROW(temp.front(), std::out_of_range);
}

TEST(TestList, BackMethod) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int i = temp.back();
  EXPECT_EQ(i, 10);
  temp.clear();
  EXPECT_THROW(temp.back(), std::out_of_range);
}

TEST(TestList, BeginMethod) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = temp.begin();
  EXPECT_EQ(*it, 1);
  temp.clear();
  it = temp.begin();
  EXPECT_THROW(*it, std::out_of_range);
}

TEST(TestList, EndMethod) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = temp.end();
  EXPECT_THROW(*it, std::out_of_range);
}

TEST(TestList, EmptyMethod) {
  s21::list<int> temp;
  EXPECT_EQ(temp.empty(), true);
}

TEST(TestList, SizeMethod) {
  s21::list<int> temp;
  EXPECT_EQ(temp.size(), 0);
  s21::list<int> temp_2{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(temp_2.size(), 8);
}

TEST(TestList, MaxSize) {
  s21::list<int> my_list;
  std::list<int> std_list;

  EXPECT_GT(my_list.max_size(), 0);
}

TEST(TestList, Insert) {
  s21::list<int> list_1;
  list_1.insert(list_1.begin(), 1);
  list_1.insert(list_1.begin(), 2);
  list_1.insert(list_1.begin(), 3);
  list_1.insert(list_1.begin(), 4);
  list_1.insert(list_1.begin(), 5);
  list_1.insert(list_1.begin(), 6);
  auto it = list_1.begin();
  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(list_1.size(), 6);
  s21::list<int> list_2;
  list_2.insert(list_2.end(), 1);
  list_2.insert(list_2.end(), 2);
  list_2.insert(list_2.end(), 3);
  list_2.insert(list_2.end(), 4);
  list_2.insert(list_2.end(), 5);
  list_2.insert(list_2.end(), 6);
  auto it_2 = list_2.begin();
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(*it_2, i);
    ++it_2;
  }
  EXPECT_EQ(list_2.size(), 6);
}

TEST(TestList, Insert_2) {
  s21::list<int> list;
  list.insert(list.end(), 1);
  list.insert(list.end(), 3);
  list.insert(list.end(), 4);
  list.insert(list.end(), 5);
  list.insert(list.end(), 6);
  list.insert(list.end(), 7);
  list.insert(list.begin() + 1, 2);
  auto it = list.begin();
  for (int i = 1; i < 8; i++) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, Erase) {
  s21::list<int> list_1{1, 2, 3, 4, 5, 6};
  list_1.erase(list_1.begin() + 2);
  list_1.erase(list_1.begin());
  list_1.erase(list_1.end());
  auto it = list_1.begin();
  for (int i = 1; i < 6; i++) {
    if (i == 2 || i == 4 || i == 5) {
      EXPECT_EQ(*it, i);
      ++it;
    }
  }
}

TEST(TestList, PushBack) {
  s21::list<int> list_1;
  for (int i = 0; i < 1000; i++) {
    list_1.push_back(i);
  }
  auto it = list_1.begin();
  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, PopBack) {
  s21::list<int> list_1;
  for (int i = 0; i < 1000; i++) {
    list_1.push_back(i);
  }
  for (int i = 0; i < 500; i++) {
    list_1.pop_back();
  }
  auto it = list_1.begin();
  for (int i = 0; i < 500; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
  EXPECT_EQ(list_1.size(), 500);
}

TEST(TestList, PushFront) {
  s21::list<int> list;
  for (int i = 6; i >= 0; i--) list.push_front(i);

  auto it = list.begin();
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
  EXPECT_EQ(list.size(), 7);
}

TEST(TestList, PopFront) {
  s21::list<int> list;
  for (int i = 6; i >= 0; i--) list.push_front(i);

  auto it = list.begin();
  for (int i = 0; i < 7; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
  EXPECT_EQ(list.size(), 7);
  for (int i = 0; i < 3; i++) list.pop_front();

  it = list.begin();
  for (int i = 3; i < 7; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, Swap) {
  s21::list<int> list{1, 2, 3, 4, 5, 6};
  s21::list<int> list_2;
  list_2.swap(list);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(list_2.size(), 6);

  auto it = list_2.begin();
  for (int i = 1; i < 7; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, Merge) {
  s21::list<int> list{6, 5, 4, 3, 2, 1};
  s21::list<int> list_2{10, 9, 8, 7};
  list.merge(list_2);

  auto it = list.begin();
  for (int i = 1; i < 11; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, Merge_2) {
  s21::list<int> list{11, 12, 13, 14, 15, 16};
  s21::list<int> list_2{10, 9, 8, 7};
  list.merge(list_2);

  auto it = list.begin();
  for (int i = 7; i < 16; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, Merge_3) {
  s21::list<int> list{3, 1, 7, 5, 9, 11};
  s21::list<int> list_2{2, 6, 4, 10, 8};
  list.merge(list_2);

  auto it = list.begin();
  for (int i = 1; i < 12; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, Splice) {
  s21::list<int> list{6, 5, 4, 3, 2, 1};
  s21::list<int> list_2{10, 9, 8, 7};
  list.splice(list_2.begin() + 2, list_2);
  list.sort();
  auto it = list.begin();
  for (int i = 1; i <= 8; i++) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, Reverse) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list.reverse();
  auto it = list.begin();
  for (int i = 10; i > 0; i--) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, Unique) {
  s21::list<int> list{1, 2, 2, 2, 3, 4, 4, 5, 6, 6, 6, 7};
  list.unique();
  auto it = list.begin();
  for (int i = 1; i < 8; i++) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, Sort) {
  s21::list<int> list{1, 3, 2, 5, 4, 6, 0, 7, 9, 8};
  list.sort();
  auto it = list.begin();
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
}

TEST(TestList, IteratorConstr) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int>::iterator it = list.begin();
  EXPECT_NO_THROW(it = it);
}

TEST(TestList, IteratorPlus) {
  s21::list<int> list{1, 2, 3};
  auto it = list.begin();
  EXPECT_THROW(it + 10, std::out_of_range);
}

TEST(TestList, IteratorMinus) {
  s21::list<int> list{1, 2, 3};
  auto it = list.begin();
  EXPECT_THROW(it - 10, std::out_of_range);
}

TEST(TestList, IteratorMinus_2) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = list.begin() + 4;
  it = it - 4;
  EXPECT_EQ(*it, 1);
}

TEST(TestList, IteratorMoveBack) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7};
  auto it = list.begin() + 6;
  for (int i = 7; i > 0; i--) {
    EXPECT_EQ(*it, i);
    --it;
  }
}

TEST(TestList, IteratorMoveBackPost) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7};
  auto it = list.begin() + 6;
  for (int i = 7; i > 0; i--) {
    EXPECT_EQ(*it, i);
    it--;
  }
}

TEST(TestList, IteratorOperatorEqual) {
  s21::list<int> list{1, 2, 3, 4, 5, 6};
  auto it = list.begin() + 2;
  auto other_it = list.begin() + 2;
  EXPECT_TRUE(it == other_it);
}

TEST(TestList, IteratorOperatorNotEqual) {
  s21::list<int> list{1, 2, 3, 4, 5, 6};
  auto it = list.begin() + 2;
  auto other_it = list.begin() + 3;
  EXPECT_TRUE(it != other_it);
}

TEST(TestList, IteratorPoint) {
  s21::list<int> list{1, 2, 3, 4};
  auto it = list.begin();
  const int i = *it;
  EXPECT_EQ(i, 1);
}

TEST(TestList, IteratorPoint_2) {
  s21::list<int> list{1, 2, 3, 4};

  s21::list<int>::iterator it = list.begin();
  int i = *it;
  EXPECT_EQ(i, 1);

  const s21::list<int>& const_list = list;
  s21::list<int>::const_iterator const_it = const_list.begin();
  int ci = *const_it;
  EXPECT_EQ(ci, 1);
}

TEST(TestList, IteratorIncrement) {
  s21::list<int> list{1, 2, 3};
  auto it = list.end();
  EXPECT_THROW(++it, std::out_of_range);
}

TEST(TestList, IteratorPostcrement) {
  s21::list<int> list{1, 2, 3};
  auto it = list.end();
  EXPECT_THROW(it++, std::out_of_range);
}

TEST(TestList, IteratorDecrement) {
  s21::list<int> list{1, 2, 3};
  auto it = list.end();
  EXPECT_THROW(--it, std::out_of_range);
}

TEST(TestList, IteratorPostdecrement) {
  s21::list<int> list{1, 2, 3};
  auto it = list.end();
  EXPECT_THROW(it--, std::out_of_range);
}

TEST(TestList, ConstIteratorCopy) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator it_const = list.begin();
  EXPECT_EQ(*it_const, 1);
}

TEST(TestList, ConstIteratorConstr) {
  s21::list<int> list{1, 2, 3};
  auto it = list.begin();
  s21::list<int>::const_iterator new_it(it);
  EXPECT_EQ(*new_it, 1);
}

TEST(TestList, ConstIterOperCopy) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator it = list.begin();
  s21::list<int>::const_iterator new_it = it;
  EXPECT_EQ(*new_it, 1);
}

TEST(TestList, ConstIterOperPtr) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator new_it = list.end();
  EXPECT_THROW(*new_it, std::out_of_range);
}

TEST(TestList, ConstIteratorOperPlus) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int>::const_iterator new_it = list.begin() + 3;
  EXPECT_EQ(*new_it, 4);
  EXPECT_THROW(new_it + 3, std::out_of_range);
}

TEST(TestList, ConstIteratorOperMinus) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int>::const_iterator new_it = list.begin();
  EXPECT_THROW(new_it - 3, std::out_of_range);
  new_it = new_it + 3;
  new_it = new_it - 3;
  EXPECT_EQ(*new_it, 1);
}

TEST(TestList, OperatorPlusPlus) {
  s21::list<int> list{1, 2, 3, 4, 5};
  s21::list<int>::const_iterator new_it = list.begin();
  new_it++;
  EXPECT_EQ(*new_it, 2);
}

TEST(TestList, OperatorPlusPlus_3) {
  s21::list<int> list{1, 2, 3, 4, 5};
  s21::list<int>::const_iterator new_it = list.end();
  EXPECT_THROW(++new_it, std::out_of_range);
}

TEST(TestList, OperatorPlusPlus_2) {
  s21::list<int> list{1, 2, 3, 4, 5};
  s21::list<int>::const_iterator new_it = list.end();
  EXPECT_THROW(new_it++, std::out_of_range);
}

TEST(TestList, OperatorMinMin) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator it = list.end();
  EXPECT_THROW(--it, std::out_of_range);
}

TEST(TestList, OperatorMinMin_2) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator it = list.end();
  EXPECT_THROW(it--, std::out_of_range);
}

TEST(TestList, OperatorMinMin_3) {
  s21::list<int> list{1, 2, 3};
  s21::list<int>::const_iterator it = list.begin();
  it++;
  it++;
  it--;
  EXPECT_EQ(*it, 2);
}

TEST(TestList, OperEq) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int>::const_iterator it = list.begin();
  s21::list<int>::const_iterator other_it = list.begin();
  EXPECT_TRUE(other_it == it);
}

TEST(TestList, OperNotEq) {
  s21::list<int> list{1, 2, 3, 4};
  s21::list<int>::const_iterator it = list.begin() + 1;
  s21::list<int>::const_iterator other_it = list.begin();
  EXPECT_TRUE(other_it != it);
}

TEST(TestList, InitializerList_NotEmpty_2) {
  s21::list<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = temp.begin();
  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(TestList, EmptyListOperations) {
  s21::list<int> list;
  EXPECT_THROW(list.front(), std::out_of_range);
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(TestList, InsertMany) {
  s21::list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list.insert_many(list.end(), 11, 12, 13, 14, 15);
  int i = 1;
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(list.size(), 15);
}

TEST(TestList, InsertManyBack) {
  s21::list<int> list{4, 5, 6};
  list.insert_many_back(7, 8, 9);
  int i = 4;
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}

TEST(TestList, InsertManyFront) {
  s21::list<int> list{7, 8, 9};
  list.insert_many_front(4, 5, 6);
  int i = 4;
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}
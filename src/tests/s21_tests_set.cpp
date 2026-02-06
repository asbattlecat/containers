#include "s21_tests.h"

TEST(TestsSet, DefConstr) {
  s21::set<int> set;
  EXPECT_TRUE(set.empty());
}

TEST(TestsSet, InitList) {
  s21::set<int> set{1, 2, 3, 4, 5, 6};
  EXPECT_FALSE(set.empty());
  EXPECT_EQ(set.size(), 6);
  int i = 1;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}

TEST(TestsSet, CopyConstr) {
  s21::set<int> set{1, 2, 3, 4, 5, 6};
  s21::set<int> set_2(set);
  EXPECT_FALSE(set_2.empty());
  EXPECT_EQ(set_2.size(), 6);
  EXPECT_FALSE(set.empty());
  EXPECT_EQ(set.size(), 6);
  int i = 1;
  for (auto it = set_2.begin(); it != set_2.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
  i = 1;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}

TEST(TestsSet, MoveConstr) {
  s21::set<int> set{1, 2, 3, 4, 5, 6};
  s21::set<int> set_2(std::move(set));
  EXPECT_FALSE(set_2.empty());
  EXPECT_EQ(set_2.size(), 6);
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
  int i = 1;
  for (auto it = set_2.begin(); it != set_2.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}

TEST(TestsSet, MoveOperator) {
  s21::set<int> set{1, 2, 3, 4, 5, 6};
  s21::set<int> set_2;
  set_2 = std::move(set);
  EXPECT_FALSE(set_2.empty());
  EXPECT_EQ(set_2.size(), 6);
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0);
  int i = 1;
  for (auto it = set_2.begin(); it != set_2.end(); ++it) {
    EXPECT_EQ(i++, *it);
  }
}

TEST(TestsSet, Destr) {
  s21::set<int> set{1, 2, 3, 4, 5, 6};
  set.~set();
  EXPECT_TRUE(set.empty());
}

TEST(TestsSet, Begin) {
  s21::set<int> set{1, 2, 3};
  auto it = set.begin();
  auto val = *it;
  EXPECT_EQ(val, 1);

  s21::set<int> set_2;
  EXPECT_THROW(set_2.begin(), std::out_of_range);
}

TEST(TestsSet, End) {
  s21::set<int> set_2{2, 4};
  auto it = set_2.end();
  --it;
  auto val = *it;
  EXPECT_EQ(val, 4);
}

TEST(TestsSet, Empty) {
  s21::set<int> set;
  EXPECT_TRUE(set.empty());

  s21::set<int> set_2{2};
  EXPECT_FALSE(set_2.empty());
}

TEST(TestsSet, Size) {
  s21::set<int> set{2, 3, 4, 5};
  EXPECT_EQ(set.size(), 4);

  s21::set<int> set_2;
  EXPECT_EQ(set_2.size(), 0);
}

TEST(TestsSet, MaxSize) {
  s21::set<int> set;
  EXPECT_GT(set.max_size(), 0);
}

TEST(TestsSet, Clear) {
  s21::set<int> set;
  EXPECT_NO_THROW(set.clear());

  s21::set<int> set_2{2};
  set_2.clear();
  EXPECT_TRUE(set_2.empty());
}

TEST(TestsSet, Insert) {
  s21::set<int> set;
  for (int i = 0; i < 100000; i++) {
    set.insert(i);
  }
  int i = 0;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(set.size(), 100000);
  EXPECT_TRUE(set.is_balanced());
  for (int i = 0; i < 1000; i++) {
    auto [it, inserted] = set.insert(i);
    EXPECT_FALSE(inserted);
  }
  for (int i = 100000; i < 100010; i++) {
    auto [it, inserted] = set.insert(i);
    EXPECT_TRUE(inserted);
  }
}

TEST(TestsSet, Erase) {
  s21::set<int> set;
  for (int i = 0; i < 100000; i++) {
    set.insert(i);
  }
  for (int i = 3; i < 200; i++) {
    auto it = set.find_node_iterator(i);
    auto temp = it++;
    set.erase(temp);
  }
  EXPECT_TRUE(set.is_balanced());
  EXPECT_EQ(set.size(), 99803);

  for (auto it = set.begin(); it != set.end();) {
    set.erase(it++);
  }
  EXPECT_TRUE(set.empty());
}

TEST(TestsSet, Swap) {
  s21::set<int> set_1{2, 3, 4, 5};
  s21::set<int> set_2{6, 7};
  set_1.swap(set_2);
  EXPECT_EQ(set_1.size(), 2);
  EXPECT_EQ(set_2.size(), 4);
  EXPECT_THROW(set_1.swap(set_1), std::invalid_argument);
}

TEST(TestsSet, Merge) {
  s21::set<int> set_1{2, 3, 4, 5};
  s21::set<int> set_2{6, 7};
  s21::set<int> set_5;
  set_1.merge(set_2);
  int i = 2;
  for (auto it = set_1.begin(); it != set_1.end(); ++it) {
    auto val = *it;
    EXPECT_EQ(val, i++);
  }

  s21::set<int> set_3{2, 3, 4};
  s21::set<int> set_4{5, 6, 7};
  set_3.merge(set_4);
  i = 2;
  for (auto it = set_3.begin(); it != set_3.end(); ++it) {
    auto val = *it;
    EXPECT_EQ(val, i++);
  }

  set_1.merge(set_3);
  i = 2;
  for (auto it = set_1.begin(); it != set_1.end(); ++it) {
    auto val = *it;
    EXPECT_EQ(val, i++);
  }

  s21::set<int> haaaa;
  set_1.merge(haaaa);
}

TEST(TestsSet, Contains) {
  s21::set<int> set{2, 3, 4};
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(4));
  EXPECT_FALSE(set.contains(5));
  EXPECT_FALSE(set.contains(6));
}

TEST(TestSet, InsertMany) {
  s21::set<int> set;
  set.insert_many(1, 2, 3, 4, 5);
  int i = 1;
  for (auto it = set.begin(); it != set.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(set.size(), 5);
}
#include "s21_tests.h"

TEST(MapTests, DefConstr) {
  s21::map<int, int> map;
  EXPECT_TRUE(map.empty());
}

TEST(MapTests, InitList_01) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  EXPECT_EQ(map.size(), 5);
}

TEST(MapTests, InitList_02) {
  s21::map<int, int> map{{1, 2}, {1, 2}, {1, 2}, {1, 5}, {1, 6}};
  EXPECT_EQ(map.size(), 1);
}

TEST(MapTests, ConstCopy) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  s21::map<int, int> map_2(map);
  EXPECT_EQ(map_2.size(), 5);
}

TEST(MapTests, ConstCopy_2) {
  s21::map<int, int> map{{1, 2}, {1, 2}, {1, 2}, {1, 5}, {1, 6}};
  s21::map<int, int> map_2(map);
  EXPECT_EQ(map_2.size(), 1);
}

TEST(MapTests, ConstMove) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  s21::map<int, int> map_2(std::move(map));
  EXPECT_EQ(map_2.size(), 5);
  EXPECT_TRUE(map.empty());
}

TEST(MapTests, OperMove) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  s21::map<int, int> map_2;
  map_2 = std::move(map);
  EXPECT_EQ(map_2.size(), 5);
  EXPECT_TRUE(map.empty());
}

TEST(MapTests, At) {
  s21::map<int, int> map_1;
  EXPECT_THROW(map_1.at(3), std::out_of_range);
  s21::map<int, int> map{{1, 2}, {2, 3}};
  EXPECT_EQ(map.at(1), 2);
  EXPECT_EQ(map.at(2), 3);
  EXPECT_THROW(map.at(3), std::out_of_range);
}

TEST(MapTests, At_2) {
  s21::map<int, int> map;
  EXPECT_THROW(map.at(1), std::out_of_range);
  EXPECT_THROW(map.at(2), std::out_of_range);
  EXPECT_THROW(map.at(3), std::out_of_range);
}

TEST(MapTests, OperBraces) {
  s21::map<int, int> map{{1, 2}, {2, 3}};
  EXPECT_EQ(map[1], 2);
  EXPECT_EQ(map[2], 3);
  EXPECT_THROW(map[3], std::out_of_range);
}

TEST(MapTests, OperBraces_2) {
  s21::map<int, int> map;
  EXPECT_THROW(map[1], std::out_of_range);
}

TEST(MapTests, Destr) {
  s21::map<int, int> map{{1, 0}, {2, 0}};
  map.~map();
  EXPECT_TRUE(map.empty());
}

TEST(MapTests, Begin) {
  s21::map<int, int> map{{1, 0}, {2, 0}, {3, 0}};
  auto it = map.begin();
  auto [key, val] = *it;
  EXPECT_EQ(val, 0);
  EXPECT_EQ(key, 1);

  s21::map<int, int> map_2;
  EXPECT_THROW(map_2.begin(), std::out_of_range);
}

TEST(MapTests, End) {
  s21::map<int, int> map_2{{1, 2}, {2, 3}, {3, 4}};
  auto it = map_2.end();
  --it;
  auto [key, val] = *it;
  EXPECT_EQ(val, 4);
}

TEST(MapTests, Empty) {
  s21::map<int, int> map;
  EXPECT_TRUE(map.empty());

  s21::map<int, int> map_2{{1, 2}};
  EXPECT_FALSE(map_2.empty());
}

TEST(MapTests, Size) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  EXPECT_EQ(map.size(), 4);

  s21::map<int, int> map_2;
  EXPECT_EQ(map_2.size(), 0);
}

TEST(MapTests, MaxSize) {
  s21::map<int, int> map;
  EXPECT_GT(map.max_size(), 0);
}

TEST(MapTests, Clear) {
  s21::map<int, int> map;
  EXPECT_NO_THROW(map.clear());

  s21::map<int, int> map_2{{1, 2}};
  map_2.clear();
  EXPECT_TRUE(map_2.empty());
}

TEST(MapTests, Insert_1) {
  s21::map<int, int> map;
  for (int i = 0; i < 100000; i++) {
    map.insert({i, i + 1});
  }
  for (int i = 0; i < 100000; i++) {
    map.insert({i, i + 3});
  }
  EXPECT_TRUE(map.is_balanced());
  EXPECT_EQ(map.size(), 100000);
  int i = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
  auto [it, inserted] = map.insert({100000, 10});
  auto [key, val] = *it;
  EXPECT_TRUE(inserted);
  EXPECT_EQ(val, 10);
}

TEST(MapTests, Insert_2) {
  s21::map<int, int> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, i + 1);
  }
  for (int i = 0; i < 100000; i++) {
    map.insert(i, i + 2);
  }
  EXPECT_TRUE(map.is_balanced());
  EXPECT_EQ(map.size(), 100000);
  int i = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
  auto [it, inserted] = map.insert(100000, 10);
  auto [key, val] = *it;
  EXPECT_TRUE(inserted);
  EXPECT_EQ(val, 10);
}

TEST(MapTests, Insert_3) {
  s21::map<int, int> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, i + 1);
  }
  for (int i = 0; i < 100100; i++) {
    map.insert_or_assign(i, i + 2);
  }
  EXPECT_TRUE(map.is_balanced());
  EXPECT_EQ(map.size(), 100100);
  int i = 0;
  for (auto it = map.begin(); it != map.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i);
    i += 2;
    EXPECT_EQ(val, i);
    i--;
  }
  auto [it, inserted] = map.insert_or_assign(1, 10);
  auto [key, val] = *it;
  EXPECT_TRUE(inserted);
  EXPECT_EQ(val, 10);
}

TEST(MapTests, Erase) {
  s21::map<int, int> map;
  for (int i = 0; i < 100000; i++) {
    map.insert(i, i + 1);
  }
  for (int i = 3; i < 200; i++) {
    auto it = map.find_node_iterator(i);
    auto temp = it++;
    map.erase(temp);
  }
  EXPECT_TRUE(map.is_balanced());
  EXPECT_EQ(map.size(), 99803);

  for (auto it = map.begin(); it != map.end();) {
    map.erase(it++);
  }
  EXPECT_TRUE(map.empty());
}

TEST(MapTests, Swap) {
  s21::map<int, int> map_1{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  s21::map<int, int> map_2{{5, 6}, {6, 7}};
  map_1.swap(map_2);
  EXPECT_EQ(map_1.size(), 2);
  EXPECT_EQ(map_2.size(), 4);
  EXPECT_THROW(map_1.swap(map_1), std::invalid_argument);
}

TEST(MapTests, Merge) {
  s21::map<int, int> map_1{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  s21::map<int, int> map_2{{5, 6}, {6, 7}};
  s21::map<int, int> map_5;
  map_1.merge(map_2);
  int i = 1;
  for (auto it = map_1.begin(); it != map_1.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }

  s21::map<int, int> map_3{{1, 2}, {2, 3}, {3, 4}};
  s21::map<int, int> map_4{{1, 5}, {2, 6}, {3, 7}};
  map_3.merge(map_4);
  i = 1;
  for (auto it = map_3.begin(); it != map_3.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }

  map_1.merge(map_2);
  i = 1;
  for (auto it = map_1.begin(); it != map_1.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
}

TEST(MapTests, Contains) {
  s21::map<int, int> map{{1, 2}, {2, 3}, {3, 4}};
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_TRUE(map.contains(3));
  EXPECT_FALSE(map.contains(4));
  EXPECT_FALSE(map.contains(5));
}

TEST(MapTests, InsertMany) {
  s21::map<int, int> map;
  map.insert_many(std::make_pair(1, 2), std::make_pair(2, 3),
                  std::make_pair(3, 4), std::make_pair(4, 5),
                  std::make_pair(5, 6));
  int i = 1;
  for (auto it = map.begin(); it != map.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
  EXPECT_EQ(map.size(), 5);
}
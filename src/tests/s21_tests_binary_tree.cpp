#include "s21_tests.h"

TEST(BinaryTree, DefConstr) {
  s21::BinaryTree<int, int> tree;
  EXPECT_EQ(tree.size(), 0);
}

TEST(BinaryTree, InitList) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  EXPECT_EQ(tree.size(), 3);
  EXPECT_FALSE(tree.empty());
}

TEST(BinaryTree, CopyConstr) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  s21::BinaryTree<int, int> tree_2(tree);
  EXPECT_EQ(tree_2.size(), 3);
  EXPECT_FALSE(tree_2.empty());
}

TEST(BinaryTree, CopyConstr2) {
  s21::BinaryTree<int, int> tree;
  s21::BinaryTree<int, int> tree_2(tree);
}

TEST(BinaryTree, MoveConstr) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  s21::BinaryTree<int, int> tree_2(std::move(tree));
  EXPECT_EQ(tree_2.size(), 3);
  EXPECT_FALSE(tree_2.empty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, Destr) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  tree.~BinaryTree();
  EXPECT_EQ(tree.size(), 0);
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, OperCopy) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  s21::BinaryTree<int, int> tree_2;
  tree_2 = tree;
  EXPECT_EQ(tree_2.size(), 3);
  EXPECT_FALSE(tree_2.empty());
}

TEST(BinaryTree, OperMove) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}, {3, 4}};
  s21::BinaryTree<int, int> tree_2;
  tree_2 = std::move(tree);
  EXPECT_EQ(tree_2.size(), 3);
  EXPECT_FALSE(tree_2.empty());
  EXPECT_EQ(tree.size(), 0);
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, Insert) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  EXPECT_TRUE(tree.is_balanced());
  int i = 1;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
}

TEST(BinaryTree, Insert3) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 100; i++) {
    tree.insert({i, i + 1});
    EXPECT_TRUE(tree.is_balanced());
  }
  int i = 1;
  for (auto it = tree.begin(); it != tree.end(); ++it) {
    auto [key, val] = *it;
    EXPECT_EQ(key, i++);
    EXPECT_EQ(val, i);
  }
}

TEST(BinaryTree, Insert_2) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    if (i % 5 == 0) tree.insert({i, i + 1});
    // EXPECT_TRUE(tree.is_balanced());
  }
  for (int i = 3; i < 10000; i += 3) {
    tree.insert({i, i});
  }
  for (int i = 5; i < 10000; i += 5) {
    tree.insert({i, i});
  }
  for (int i = 7; i < 10000; i += 7) {
    tree.insert({i, i});
  }
  for (int i = 11; i < 10000; i += 7) {
    tree.insert({i, i});
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 7; i < 10000; i += 7) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
  tree.clear();
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 9900; i > 1; i -= 7) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
  for (auto it = tree.begin(); it != tree.end();) {
    tree.remove_node(it++);
  }
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, RemoveNode_2) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 4; i++) {
    tree.insert({i, i + 1});
  }
  auto it = tree.find_node_iterator(2);
  tree.remove_node(it);
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_3) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 9873; i > 1; i -= 3) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_4) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 9872; i > 1; i -= 5) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_5) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 9800; i > 1; i -= 7) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_6) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 2; i < 10000; i += 7) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_7) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 3; i < 10000; i += 7) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, RemoveNode_8) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 4; i < 10000; i += 11) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.is_balanced());
}

TEST(BinaryTree, Begin2) {
  s21::BinaryTree<int, int> tree;
  EXPECT_THROW(tree.begin(), std::out_of_range);
}

TEST(BinaryTree, RemoveNode_9) {
  s21::BinaryTree<int, int> tree;
  auto it = tree.find_node_iterator(1);
  EXPECT_THROW(tree.remove_node(it), std::out_of_range);
}

TEST(BinaryTree, Empty) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 1; i <= 10000; i++) {
    auto it = tree.find_node_iterator(i);
    tree.remove_node(it);
  }
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, Size) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  EXPECT_EQ(tree.size(), 10000);
}

TEST(BinaryTree, MaxSize) {
  s21::BinaryTree<int, int> tree;
  EXPECT_GT(tree.max_size(), 0);
}

TEST(BinaryTree, Clear) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  tree.clear();
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTree, Contains) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}};
  EXPECT_TRUE(tree.contains(2));
  EXPECT_TRUE(tree.contains(1));
  EXPECT_FALSE(tree.contains(3));
}

TEST(BinaryTree, FindNodeIterator) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 1; i <= 10000; i++) {
    auto it = tree.find_node_iterator(i);
    auto [key, val] = *it;
    EXPECT_EQ(key, i);
    EXPECT_EQ(val, i + 1);
  }
  auto it = tree.find_node_iterator(10001);
  EXPECT_THROW(*it, std::out_of_range);
}

TEST(BinaryTree, FindNodeIterator2) {
  s21::BinaryTree<int, void> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert(i);
  }
  for (int i = 1; i <= 10000; i++) {
    auto it = tree.find_node_iterator(i);
    auto key = *it;
    EXPECT_EQ(key, i);
  }
  auto it = tree.find_node_iterator(10001);
  EXPECT_THROW(*it, std::out_of_range);
}

TEST(BinaryTree, FindNodeNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 1; i <= 10000; i++) {
    auto ptr = tree.find_node_node_(i);
    EXPECT_FALSE(ptr == nullptr);
  }
  auto ptr = tree.find_node_node_(10001);
  EXPECT_TRUE(ptr == nullptr);
}

TEST(BinaryTree, FindNodeNode2) {
  s21::BinaryTree<int, void> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert(i);
  }
  for (int i = 1; i <= 10000; i++) {
    auto ptr = tree.find_node_node_(i);
    EXPECT_FALSE(ptr == nullptr);
  }
  auto ptr = tree.find_node_node_(10001);
  EXPECT_TRUE(ptr == nullptr);
}

TEST(BinaryTree, GetNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  for (int i = 1; i <= 10000; i++) {
    auto it = tree.find_node_iterator(i);
    auto ptr = tree.get_node(it);
    EXPECT_FALSE(ptr == nullptr);
  }
  auto it = tree.find_node_iterator(10001);
  EXPECT_THROW(tree.get_node(it), std::out_of_range);
}

TEST(BinaryTree, FindMaxNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  auto ptr = tree.find_max_node();
  auto other_ptr = tree.find_node_node_(10000);
  EXPECT_TRUE(ptr == other_ptr);
}

TEST(BinaryTree, FindMaxNode2) {
  s21::BinaryTree<int, int> tree;
  auto ptr = tree.find_max_node();
  EXPECT_TRUE(ptr == nullptr);
}

TEST(BinaryTree, FindMinNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  auto ptr = tree.find_min_node();
  auto other_ptr = tree.find_node_node_(1);
  EXPECT_TRUE(ptr == other_ptr);
}

TEST(BinaryTree, FindMinNode2) {
  s21::BinaryTree<int, int> tree;
  auto ptr = tree.find_min_node();
  EXPECT_TRUE(ptr == nullptr);
}

TEST(BinaryTree, IsThereSuchNode) {
  s21::BinaryTree<int, int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.insert({i, i + 1});
  }
  EXPECT_TRUE(tree.is_there_such_node(10000));
  EXPECT_FALSE(tree.is_there_such_node(10001));
}

TEST(BinaryTree, IterPtr) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}};
  auto it = tree.begin();
  it->second = 3;
  auto [key, val] = *it;
  EXPECT_EQ(val, 3);
}

TEST(BinaryTree, IterMove) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  ++it;
  EXPECT_THROW(++it, std::out_of_range);
}

TEST(BinaryTree, IterMove2) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  ++it;
  EXPECT_THROW(it++, std::out_of_range);
}

TEST(BinaryTree, IterMoveBack) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  EXPECT_THROW(--it, std::out_of_range);
}

TEST(BinaryTree, IterMoveBack2) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  EXPECT_THROW(it--, std::out_of_range);
}

TEST(BinaryTree, IterEq) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  auto oth_it = tree.begin();
  EXPECT_TRUE(it == oth_it);
}

TEST(BinaryTree, IterNotEq) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.begin();
  auto oth_it = tree.begin();
  EXPECT_FALSE(it != oth_it);
}

TEST(BinaryTree, IterPtr2) {
  s21::BinaryTree<int, int> tree{{1, 2}};
  auto it = tree.find_node_iterator(2);
  EXPECT_THROW(it->second, std::out_of_range);
}

TEST(BinaryTree, IterMoveBack3) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}};
  auto it = tree.find_node_iterator(3);
  --it;
  auto [key, val] = *it;
  EXPECT_EQ(val, 3);
  --it;
}

TEST(BinaryTree, IterMoveBack4) {
  s21::BinaryTree<int, int> tree{{1, 2}, {2, 3}};
  auto it = tree.find_node_iterator(3);
  it--;
  auto [key, val] = *it;
  EXPECT_EQ(val, 3);
  it--;
}
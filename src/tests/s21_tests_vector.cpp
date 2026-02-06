#include "s21_tests.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> temp;
  ASSERT_EQ(temp.size(), 0);
}

TEST(VectorTest, ConstructorSize) {
  s21::vector<int> temp(4);
  ASSERT_EQ(temp.size(), 4);
  ASSERT_EQ(temp.capacity(), 4);
}

TEST(VectorTest, ConstructorList) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ(temp.size(), 9);
  ASSERT_EQ(temp.capacity(), 9);
}

TEST(VectorTest, ConstructorList_2) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp[pos++], i);
  }
}

TEST(VectorTest, ConstructorCopy) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> temp_2(temp);
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp_2[pos++], i);
  }
  ASSERT_EQ(temp_2.size(), 9);
  ASSERT_EQ(temp_2.capacity(), 9);
  ASSERT_EQ(temp.size(), 9);
  ASSERT_EQ(temp.capacity(), 9);
}

TEST(VectorTest, ConstructorMove) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> temp_2(std::move(temp));
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp_2[pos++], i);
  }
  ASSERT_EQ(temp_2.size(), 9);
  ASSERT_EQ(temp_2.capacity(), 9);
  ASSERT_EQ(temp.size(), 0);
  ASSERT_EQ(temp.capacity(), 0);
}

TEST(VectorTest, Destrucor) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  temp.~vector();
  ASSERT_EQ(temp.size(), 0);
  ASSERT_EQ(temp.capacity(), 0);
}

TEST(VectorTest, OperatorMove) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> temp_2;
  temp_2 = std::move(temp);
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp_2[pos++], i);
  }
  ASSERT_EQ(temp_2.size(), 9);
  ASSERT_EQ(temp_2.capacity(), 9);
  ASSERT_EQ(temp.size(), 0);
  ASSERT_EQ(temp.capacity(), 0);
}

TEST(VectorTest, OperatorCopy) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> temp_2;
  temp_2 = temp;
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp_2[pos++], i);
  }
  ASSERT_EQ(temp_2.size(), 9);
  ASSERT_EQ(temp_2.capacity(), 9);
  ASSERT_EQ(temp.size(), 9);
  ASSERT_EQ(temp.capacity(), 9);
}

TEST(VectorTest, AtMethod) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp.at(pos++), i);
  }
}

TEST(VectorTest, AtMethos_2) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_THROW(temp.at(9), std::out_of_range);
}

TEST(VectorTest, AtMethos_3) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_THROW(temp.at(10), std::out_of_range);
}

TEST(VectorTest, OperatorBraces) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int>::size_type pos = 0;
  for (int i = 1; i < 10; i++) {
    ASSERT_EQ(temp[pos++], i);
  }
}

TEST(VectorTest, OperatorBraces_2) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_THROW(temp[9], std::out_of_range);
}

TEST(VectorTest, FrontMethod) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(temp.front(), 1);
}

TEST(VectorTest, FrontMethod_2) {
  s21::vector<int> temp;
  EXPECT_THROW(temp.front(), std::out_of_range);
}

TEST(VectorTest, BackMethod) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_EQ(temp.back(), 9);
}

TEST(VectorTest, BackMethod_2) {
  s21::vector<int> temp;
  EXPECT_THROW(temp.back(), std::out_of_range);
}

TEST(VectorTest, DataMethod) {
  s21::vector<int> temp{1, 2, 3};
  auto it = temp.data();
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, DataMethod_2) {
  s21::vector<int> temp;
  EXPECT_THROW(temp.data(), std::out_of_range);
}

TEST(VectorTest, BeginMethod) {
  s21::vector<int> temp{1, 2, 3};
  auto it = temp.begin();
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, EndMethod) {
  s21::vector<int> temp;
  EXPECT_EQ(temp.end(), temp.begin());
  temp.push_back(1);
  EXPECT_EQ(temp.end(), temp.begin() + 1);
  temp.push_back(2);
  temp.push_back(3);
  EXPECT_EQ(temp.end(), temp.begin() + 3);
  temp.pop_back();
  EXPECT_EQ(temp.end(), temp.begin() + 2);
}

TEST(VectorTest, EmptyMethod) {
  s21::vector<int> temp;
  EXPECT_EQ(temp.empty(), true);
  s21::vector<int> temp_2{1, 2, 3, 4, 5};
  EXPECT_EQ(temp_2.empty(), false);
}

TEST(VectorTest, MaxSizeMethod) {
  s21::vector<int> vector_int;
  size_t expected_max_size_int =
      std::numeric_limits<size_t>::max() / sizeof(int);
  EXPECT_EQ(vector_int.max_size(), expected_max_size_int);

  s21::vector<double> vector_double;
  size_t expected_max_size_double =
      std::numeric_limits<size_t>::max() / sizeof(double);
  EXPECT_EQ(vector_double.max_size(), expected_max_size_double);

  s21::vector<char> vector_char;
  size_t expected_max_size_char =
      std::numeric_limits<size_t>::max() / sizeof(char);
  EXPECT_EQ(vector_char.max_size(), expected_max_size_char);
}

TEST(VectorTest, ReserveMethod) {
  s21::vector<int> temp{1, 2};
  temp.reserve(4);
  EXPECT_EQ(temp.capacity(), 4);
  EXPECT_EQ(temp.size(), 2);
}

TEST(VectorTest, ShrinkMethod) {
  s21::vector<int> temp{1, 2};
  temp.reserve(10);
  temp.shrink_to_fit();
  EXPECT_EQ(temp.capacity(), 2);
  EXPECT_EQ(temp.size(), 2);
}

TEST(VectorTest, ClearMethod) {
  s21::vector<int> temp{1, 2, 3, 4};
  temp.clear();
  EXPECT_EQ(temp.size(), 0);
}

TEST(VectorTest, InsertMethod) {
  s21::vector<int> temp;
  temp.insert(temp.end(), 2);
  temp.insert(temp.end(), 3);
  temp.insert(temp.end(), 4);
  EXPECT_EQ(temp[2], 4);
}

TEST(VectorTest_2, InsertMethod) {
  s21::vector<int> temp;
  temp.insert(temp.end(), 2);
  temp.insert(temp.end(), 3);
  temp.insert(temp.end(), 4);
  temp.insert(temp.begin() + 2, 5);
  EXPECT_EQ(temp[2], 5);
}

TEST(VectorTest, EraseMethod) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6, 7};
  temp.erase(temp.begin() + 2);
  EXPECT_EQ(temp[2], 4);
}

TEST(VectorTest, EraseMethod_2) {
  s21::vector<s21::vector<int>> temp;
  s21::vector<int> inserted_1{1, 2};
  s21::vector<int> inserted_2{3, 4};

  temp.insert(temp.end(), inserted_1);
  temp.insert(temp.end(), inserted_2);

  temp.erase(temp.begin());

  auto resulted = temp[0];
  EXPECT_EQ(resulted[0], 3);
  EXPECT_EQ(resulted[1], 4);
}

TEST(VectorTest, PushBackMethod) {
  s21::vector<int> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  int j = 1;
  for (s21::vector<int>::size_type i = 0; i < 4; i++) {
    EXPECT_EQ(temp[i], j++);
  }
  EXPECT_EQ(temp.size(), 4);
}

TEST(VectorTest, PopBackMethod) {
  s21::vector<int> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.pop_back();
  int j = 1;
  for (s21::vector<int>::size_type i = 0; i < 3; i++) {
    EXPECT_EQ(temp[i], j++);
  }
  EXPECT_EQ(temp.size(), 3);
}

TEST(VectorTest, SwapMethod) {
  s21::vector<int> temp{1, 2, 3, 4, 5};
  s21::vector<int> temp_2{6, 7, 8, 9, 10};
  temp.swap(temp_2);
  int j = 6;
  for (s21::vector<int>::size_type i = 0; i < temp.size(); i++) {
    EXPECT_EQ(temp[i], j++);
  }
  j = 1;
  for (s21::vector<int>::size_type i = 0; i < temp_2.size(); i++) {
    EXPECT_EQ(temp_2[i], j++);
  }
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> temp{7, 8, 9, 10, 11};
  temp.insert_many(temp.begin(), 1, 2, 3, 4, 5, 6);
  int i = 1;
  for (auto it = temp.begin(); it != temp.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(temp.size(), 11);

  s21::vector<int> temp_2{1, 4, 5, 6};
  temp_2.insert_many(temp_2.begin() + 1, 2, 3);
  i = 1;
  for (auto it = temp_2.begin(); it != temp_2.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(temp_2.size(), 6);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> temp{1, 2, 3, 4, 5, 6};
  temp.insert_many_back(7, 8, 9, 10, 11);
  int i = 1;
  for (auto it = temp.begin(); it != temp.end(); ++it) {
    EXPECT_EQ(*it, i++);
  }
  EXPECT_EQ(temp.size(), 11);
}
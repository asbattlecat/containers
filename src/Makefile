CC = g++
CC_FLAGS = -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-value -std=c++17
GCOVR_FLAGS = -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest_main -lgtest -pthread
GTEST_FLAGS_WITH_MAIN = -lgtest -pthread -lgmock

# прикольно описанные пути
SRC_DIR = .
VECTOR_DIR = vector
LIST_DIR = list
MAP_DIR = map
SET_DIR = set
BIN_TREE_DIR = common/binary_tree
COMMON_MSET_TREE = common/for_mset_tree
COMMOT_VECTOR = common/common_vector
ARRAY_DIR = array
MSET_DIR = multiset
STACK_DIR = stack
QUEUE_DIR = queue
TESTS_DIR = tests

# тестовые файлы
TEST_VECTOR = $(TESTS_DIR)/s21_tests_vector.cpp
TEST_LIST = $(TESTS_DIR)/s21_tests_list.cpp
TEST_MAP = $(TESTS_DIR)/s21_tests_map.cpp
TEST_SET = $(TESTS_DIR)/s21_tests_set.cpp
TEST_BIN_TREE = $(TESTS_DIR)/s21_tests_binary_tree.cpp
TEST_STACK = $(TESTS_DIR)/stack.cpp
TEST_QUEUE = $(TESTS_DIR)/queue.cpp
TEST_ARRAY = $(TESTS_DIR)/array.cpp
TEST_MULTISET = $(TESTS_DIR)/multiset.cpp
TEST_TESTS = $(TESTS_DIR)/tests.cpp

all: test

test: vector_build_test list_build_test map_build_test set_build_test \
			bin_tree_build_test stack_build_test queue_build_test array_build_test \
			multiset_build_test
	./vector_res.out
	./list_res.out
	./map_res.out
	./set_res.out
	./bin_tree_res.out
	./stack_res.out
	./queue_res.out
	./array_res.out
	./multiset_res.out

valgrind: vector_valgrind list_valgrind map_valgrind set_valgrind bin_tree_valgrind \
					stack_valgrind queue_valgrind array_valgrind multiset_valgrind

# ------------------------Вспомогательные цели---------------------------

# vector

vector: vector_build_test
	./vector_res.out

vector_build_test:
	$(CC) $(CC_FLAGS) $(TEST_VECTOR) $(GTEST_FLAGS) -o vector_res.out

vector_valgrind: vector_build_test
	valgrind --tool=memcheck --leak-check=yes ./vector_res.out

# list 
list: list_build_test
	./list_res.out

list_build_test:
	$(CC) $(CC_FLAGS) $(TEST_LIST) $(GTEST_FLAGS) -o list_res.out

list_valgrind: list_build_test
	valgrind --tool=memcheck --leak-check=yes ./list_res.out

# map
map: map_build_test
	./map_res.out

map_build_test:
	$(CC) $(CC_FLAGS) $(TEST_MAP) $(GTEST_FLAGS) -o map_res.out

map_valgrind: map_build_test
	valgrind --tool=memcheck --leak-check=yes -s ./map_res.out

# set
set: set_build_test
	./set_res.out

set_build_test:
	$(CC) $(CC_FLAGS) $(TEST_SET) $(GTEST_FLAGS) -o set_res.out

set_valgrind: set_build_test
	valgrind --tool=memcheck --leak-check=yes ./set_res.out


# BinaryTree
bin_tree: bin_tree_build_test
	./bin_tree_res.out

bin_tree_build_test:
	$(CC) $(CC_FLAGS) $(TEST_BIN_TREE) $(GTEST_FLAGS) -o bin_tree_res.out

bin_tree_valgrind: bin_tree_build_test
	valgrind --tool=memcheck --leak-check=yes ./bin_tree_res.out

# stack
stack: stack_build_test
	./stack_res.out

stack_build_test:
	$(CC) $(CC_FLAGS) $(TEST_STACK) $(GTEST_FLAGS) -o stack_res.out

stack_valgrind: stack_build_test
	valgrind --tool=memcheck --leak-check=yes ./stack_res.out

# queue
queue: queue_build_test
	./queue_res.out

queue_build_test:
	$(CC) $(CC_FLAGS) $(TEST_QUEUE) $(GTEST_FLAGS) -o queue_res.out

queue_valgrind: queue_build_test
	valgrind --tool=memcheck --leak-check=yes ./queue_res.out

# array
array: array_build_test
	./array_res.out

array_build_test:
	$(CC) $(CC_FLAGS) $(TEST_ARRAY) $(GTEST_FLAGS) -o array_res.out

array_valgrind: array_build_test
	valgrind --tool=memcheck --leak-check=yes ./array_res.out

# multiset
multiset: multiset_build_test
	./multiset_res.out

multiset_build_test:
	$(CC) $(CC_FLAGS) $(TEST_MULTISET) $(TEST_TESTS) $(GTEST_FLAGS_WITH_MAIN) -o multiset_res.out

multiset_valgrind: multiset_build_test
	valgrind --tool=memcheck --leak-check=yes ./multiset_res.out

clean:
	@rm -f *.info *.gcda *.gcno *.out
	@rm -rf $(TESTS_DIR)/report

clang_fix:
	@clang-format -i $(TESTS_DIR)/*.h $(TESTS_DIR)/*.cpp
	@clang-format -i $(VECTOR_DIR)/*.h $(VECTOR_DIR)/*.tpp
	@clang-format -i $(LIST_DIR)/*.h $(LIST_DIR)/*.tpp
	@clang-format -i $(MAP_DIR)/*.h $(MAP_DIR)/*.tpp
	@clang-format -i $(SET_DIR)/*.h $(SET_DIR)/*.tpp
	@clang-format -i $(BIN_TREE_DIR)/*.h $(BIN_TREE_DIR)/*.tpp
	@clang-format -i $(COMMON_MSET_TREE)/*.h $(COMMON_MSET_TREE)/*.tpp
	@clang-format -i $(COMMOT_VECTOR)/*.h $(COMMOT_VECTOR)/*.tpp
	@clang-format -i $(ARRAY_DIR)/*.h $(ARRAY_DIR)/*.tpp
	@clang-format -i $(MSET_DIR)/*.h $(MSET_DIR)/*.tpp
	@clang-format -i $(STACK_DIR)/*.h $(STACK_DIR)/*.tpp
	@clang-format -i $(QUEUE_DIR)/*.h $(QUEUE_DIR)/*.tpp

clang_check:
	@clang-format -n $(TESTS_DIR)/*.h $(TESTS_DIR)/*.cpp
	@clang-format -n $(VECTOR_DIR)/*.h $(VECTOR_DIR)/*.tpp
	@clang-format -n $(LIST_DIR)/*.h $(LIST_DIR)/*.tpp
	@clang-format -n $(MAP_DIR)/*.h $(MAP_DIR)/*.tpp
	@clang-format -n $(SET_DIR)/*.h $(SET_DIR)/*.tpp
	@clang-format -n $(BIN_TREE_DIR)/*.h $(BIN_TREE_DIR)/*.tpp
	@clang-format -n $(COMMON_MSET_TREE)/*.h $(COMMON_MSET_TREE)/*.tpp
	@clang-format -n $(COMMOT_VECTOR)/*.h $(COMMOT_VECTOR)/*.tpp
	@clang-format -n $(ARRAY_DIR)/*.h $(ARRAY_DIR)/*.tpp
	@clang-format -n $(MSET_DIR)/*.h $(MSET_DIR)/*.tpp
	@clang-format -n $(STACK_DIR)/*.h $(STACK_DIR)/*.tpp
	@clang-format -n $(QUEUE_DIR)/*.h $(QUEUE_DIR)/*.tpp
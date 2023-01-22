CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS = -lgtest -lgmock -pthread 
ALL_FLAGS = $(CFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)

SOURCE_LIB = $(wildcard source/*.cpp)
SOURCE = $(wildcard source/*.cpp tests/*.cpp)
D_FILES = $(patsubst %.cpp, %.d, $(SOURCE))

SOURCE_OBJ = $(SOURCE:%.cpp=objs/%.o)
SOURCE_OBJ_LIB = $(SOURCE_LIB:%.cpp=objs_lib/%.o)

all: s21_matrix_oop.a gcov_report

objs_lib/%.o: %.cpp
	@mkdir -p objs_lib/source
	$(CC) -c $< -o $@ -MMD $(CFLAGS)


objs/%.o: %.cpp
	@mkdir -p objs/tests objs/source
	$(CC) $(CHECK_FLAGS) $(GCOV_FLAGS) -c $< -o $@ -MMD

include $(wildcard objs_lib/*.d)


clean:
	rm -rf objs objs_lib finish
	rm -f test check_res
	rm -f s21_matrix_oop.a
	

test: $(SOURCE_OBJ)
	$(CC) $(ALL_FLAGS) $(SOURCE_OBJ) -o test 
	./test

s21_matrix_oop.a: $(SOURCE_OBJ_LIB)
	ar rcs s21_matrix_oop.a $?

gcov_report: test 
	geninfo */*/*.gcda */*/*.gcno -b . -o check_res
	genhtml check_res -o finish
	open finish/index.html

clang:
	clang-format -n source/*.cpp 
	clang-format -n source/*.h 
	clang-format -n tests/*.cpp 


.PHONY: all clean gcov_report test s21_matrix_oop.a clang
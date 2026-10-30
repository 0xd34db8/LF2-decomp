CXX ?= C:/msys64/ucrt64/bin/g++.exe
CXXFLAGS ?= -std=c++20 -Wall -Wextra -O2 -I.
AR ?= C:/msys64/ucrt64/bin/ar.exe

LIB_SRCS = teleport.cpp attack.cpp random.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
TARGET_LIB = liblf2.a

TEST_SRCS = verify_memory_maps.cpp
TEST_EXE = verify_memory_maps.exe

.PHONY: all test clean

all: $(TARGET_LIB) $(TEST_EXE)

$(TARGET_LIB): $(LIB_OBJS)
	$(AR) rcs $@ $^

$(TEST_EXE): $(TEST_SRCS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -L. -llf2 -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXE)
	./$(TEST_EXE)

clean:
	rm -f $(LIB_OBJS) $(TARGET_LIB) $(TEST_EXE)


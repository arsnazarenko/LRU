CXX = clang++
SOURCE_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
DEBUG_DIR = $(BUILD_DIR)/debug
SANITIZED_DIR = $(BUILD_DIR)/sanitized
RELEASE_DIR = $(BUILD_DIR)/release
OBJS = $(patsubst $(SOURCE_DIR)/%.cpp, %.o, $(wildcard $(SOURCE_DIR)/*.cpp))


CXXFLAGS += -std=c++17 -Wall -Werror -g -I $(INCLUDE_DIR)
DEBUG_FLAGS = $(CXXFLAGS)
SANITIZED_FLAGS = $(DEBUG_FLAGS) -fsanitize=address,undefined,leak
RELEASE_FLAGS = $(DEBUG_FLAGS) -O3


all: release
debug: $(DEBUG_DIR)/main
	./$(DEBUG_DIR)/main
sanitized: $(SANITIZED_DIR)/main
	./$(SANITIZED_DIR)/main
release: $(RELEASE_DIR)/main
	./$(RELEASE_DIR)/main

#dirs
debug_dir:
	mkdir -p $(DEBUG_DIR)/obj

sanitized_dir:
	mkdir -p $(SANITIZED_DIR)/obj

release_dir:
	mkdir -p $(RELEASE_DIR)/obj



# object files
$(DEBUG_DIR)/obj/%.o: $(SOURCE_DIR)/%.cpp debug_dir
	$(CXX) -c $(DEBUG_FLAGS) $< -o $@

$(SANITIZED_DIR)/obj/%.o: $(SOURCE_DIR)/%.cpp sanitized_dir
	$(CXX) -c $(SANITIZED_FLAGS) $< -o $@

$(RELEASE_DIR)/obj/%.o: $(SOURCE_DIR)/%.cpp release_dir
	$(CXX) -c $(RELEASE_FLAGS) $< -o $@


# executable files
$(DEBUG_DIR)/main: $(patsubst %.o, $(DEBUG_DIR)/obj/%.o, $(OBJS))
	$(CXX) $(DEBUG_FLAGS) $^ -o $@

$(SANITIZED_DIR)/main: $(patsubst %.o, $(SANITIZED_DIR)/obj/%.o, $(OBJS)) 
	$(CXX) $(SANITIZED_FLAGS) $^ -o $@

$(RELEASE_DIR)/main: $(patsubst %.o, $(RELEASE_DIR)/obj/%.o, $(OBJS))
	$(CXX) $(RELEASE_FLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean debug sanitized release



# C++ compiler
CXX	=	g++

# C++ compiler options
DEBUG	= true
ifeq ($(DEBUG), true)
	CXXFLAGSDEBUG	= -g3 -fsanitize=address
else
	CXXFLAGSDEBUG	= -O3
endif
CXXFLAGS	=	-std=c++17 -pedantic -Wall -Wextra $(CXXFLAGSDEBUG)

# External libraries used
LIBS	=	-lncurses

# Linker options
ifeq ($(DEBUG), true)
	LFLAGSDEBUG	= -fsanitize=address
endif
LFLAGS = -lstdc++fs $(LFLAGSDEBUG)

# all the source and generated files
#
# Creates a recursive make function
# Searches for files in a specific dir
# @param 1 - folder to search in
# @param 2 - pattern to search for
# source: https://stackoverflow.com/a/12959764
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

OUT_FILE = vimxel
SOURCES := $(call rwildcard,src/,*.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
HEADERS := $(call rwildcard,src/,*.hpp) $(call rwildcard,src/,*.h)

TEST_FILE = test_vimxel
TEST_SOURCES := $(call rwildcard,tests/,*.cpp) $(filter-out $(call rwildcard,src/,main.cpp), $(SOURCES))
TEST_OBJECTS := $(patsubst %.cpp,%.o,$(TEST_SOURCES))
TEST_DEPENDS := $(patsubst %.cpp,%.d,$(TEST_SOURCES))
TEST_HEADERS := $(call rwildcard,tests/,*.hpp) $(call rwildcard,tests/,*.h) $(filter-out $(call rwildcard,src/,main.hpp) $(call rwildcard,src/,main.h), $(HEADERS))

EXAMPLES := $(wildcard examples/**)

# These task will be run also if files of their name exists
.PHONY: default all compile run compile_test run_test doc clean lines




# --- DEFAULT, CORE ------------------------------------------------------------
# build all
default:	all
all:	compile doc

# Build executable file
compile:	$(OUT_FILE)

# Runs compiled binary
run:
	@./$(OUT_FILE) 2> err.txt

# Tests
compile_test:	$(TEST_FILE)
run_test:
	@./$(TEST_FILE) 2> err.txt




# --- COMPILATION --------------------------------------------------------------
# link the final program
$(OUT_FILE) : $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) -o $@ $(LFLAGS) $(LIBS)
	@echo compiled!

# link tests
$(TEST_FILE) : $(TEST_OBJECTS) Makefile
	$(CXX) $(TEST_OBJECTS) -o $@ $(LFLAGS) $(LIBS)
	@echo compiled!

# includes .d files as dependencies
-include	$(DEPENDS) $(TEST_DEPENDS)

# compile a C++ module and create .d files
%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@




# --- DOCS ---------------------------------------------------------------------
# Create documentation in the doc/ folder
doc: doc/index.html

doc/index.html: $(SOURCES) $(HEADERS) Doxyfile Makefile README.md
	@doxygen



# --- CLEAN UP -----------------------------------------------------------------
# clean up
# delete .o files, .d files, final executable, doc and memory dumps
clean:
	rm -f $(OUT_FILE) $(TEST_FILE)
	rm -f $(OBJECTS) $(DEPENDS)
	rm -f $(TEST_OBJECTS) $(TEST_DEPENDS)
	rm -f core
	rm -fr doc
	rm -f logs.txt err.txt



# --- LINE COUNT ---------------------------------------------------------------
lines:
	@echo Lines in project:
	@cat $(SOURCES) $(HEADERS) | grep . | wc -l




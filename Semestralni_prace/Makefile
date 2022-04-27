# C++ compiler
CXX	=	g++

# C++ compiler options
DEBUG	= true
ifeq ($(DEBUG), true)
	CXXFLAGSDEBUG	= -g3 -fsanitize=address
endif
CXXFLAGS	=	-std=c++17 -pedantic -Wall -Wextra -O3 $(CXXFLAGSDEBUG)

# External libraries used
LIBS	=	-lncurses
# Linker options
ifeq ($(DEBUG), true)
	LFLAGSDEBUG	= -fsanitize=address
endif
LFLAGS = $(LFLAGSDEBUG)
# My username, used as output filename
USERNAME =	lastope2

# all the source and generated files
#
# Creates a recursive make function
# Searches for files in a specific dir
# @param 1 - folder to search in
# @param 2 - pattern to search for
# source: https://stackoverflow.com/a/12959764
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SOURCES := $(call rwildcard,src/,*.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
HEADERS := $(call rwildcard,src/,*.hpp) $(call rwildcard,src/,*.h)

TEST_FILE = test
TEST_SOURCES := $(call rwildcard,tests/,*.cpp) $(filter-out $(call rwildcard,src/,main.cpp), $(SOURCES))
TEST_OBJECTS := $(patsubst %.cpp,%.o,$(TEST_SOURCES))
TEST_DEPENDS := $(patsubst %.cpp,%.d,$(TEST_SOURCES))
TEST_HEADERS := $(call rwildcard,tests/,*.hpp) $(call rwildcard,tests/,*.h) $(filter-out $(call rwildcard,src/,main.hpp) $(call rwildcard,src/,main.h), $(HEADERS))

EXAMPLES := $(wildcard examples/**)
ZIP := $(SOURCES) $(HEADERS) $(EXAMPLES) Doxyfile Makefile zadani.txt prohlaseni.txt

# These task will be run also if files of their name exists
.PHONY: default all compile run compile_test run_test doc zip clean




# --- DEFAULT, CORE ------------------------------------------------------------
# build all
default:	all
all:	compile doc

# Build executable file
compile:	$(USERNAME)

# Runs compiled binary
run:
	@./$(USERNAME)

# Tests
compile_test:	$(TEST_FILE)
run_test:
	@./$(TEST_FILE)




# --- COMPILATION --------------------------------------------------------------
# link the final program
$(USERNAME) : $(OBJECTS) Makefile
	$(CXX) $(LFLAGS) $(LIBS) $(OBJECTS) -o $@
	@echo compiled!

# link tests
$(TEST_FILE) : $(TEST_OBJECTS) Makefile
	$(CXX) $(LFLAGS) $(LIBS) $(TEST_OBJECTS) -o $@
	@echo compiled!

# includes .d files as dependencies
-include	$(DEPENDS) $(TEST_DEPENDS)

# compile a C++ module and create .d files
%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@




# --- DOCS ---------------------------------------------------------------------
# Create documentation in the doc/ folder
doc: doc/html/index.html

doc/html/index.html: $(SOURCES) $(HEADERS) Doxyfile Makefile zadani.txt
	@cp zadani.txt zadani.md
	@doxygen
	@rm zadani.md



# --- ZIP ----------------------------------------------------------------------
zip: $(USERNAME).zip

$(USERNAME).zip: $(ZIP)
	@mkdir -p zip_tmp/$(USERNAME)
	@cp --parents -r $(ZIP) zip_tmp/$(USERNAME)
	cd zip_tmp/ && zip -r ../$@ $(USERNAME)/
	@rm -fr zip_tmp




# --- CLEAN UP -----------------------------------------------------------------
# clean up
# delete .o files, .d files, final executable, doc and memory dumps
clean:
	rm -f $(USERNAME) $(USERNAME).zip
	rm -f $(OBJECTS) $(DEPENDS)
	rm -f $(TEST_OBJECTS) $(TEST_DEPENDS) $(TEST_FILE)
	rm -f core
	rm -fr doc


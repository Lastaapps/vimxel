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
ASSETS  := $(call rwildcard,assets/,*)

TEST_FILE = test
TEST_SOURCES := $(call rwildcard,tests/,*.cpp) $(filter-out $(call rwildcard,src/,main.cpp), $(SOURCES))
TEST_OBJECTS := $(patsubst %.cpp,%.o,$(TEST_SOURCES))
TEST_DEPENDS := $(patsubst %.cpp,%.d,$(TEST_SOURCES))
TEST_HEADERS := $(call rwildcard,tests/,*.hpp) $(call rwildcard,tests/,*.h) $(filter-out $(call rwildcard,src/,main.hpp) $(call rwildcard,src/,main.h), $(HEADERS))

EXAMPLES := $(wildcard examples/**)

# These task will be run also if files of their name exists
.PHONY: default all compile run compile_test run_test doc clean




# --- DEFAULT, CORE ------------------------------------------------------------
# build all
default:	all
all:	compile doc

# Build executable file
compile:	$(USERNAME)

# Runs compiled binary
run:
	@./$(USERNAME) 2> err.txt

# Tests
compile_test:	$(TEST_FILE)
run_test:
	@./$(TEST_FILE) 2> err.txt




# --- COMPILATION --------------------------------------------------------------
# link the final program
$(USERNAME) : $(OBJECTS) Makefile
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

doc/index.html: $(SOURCES) $(HEADERS) Doxyfile Makefile assets/README.md
	@doxygen



# --- CLEAN UP -----------------------------------------------------------------
# clean up
# delete .o files, .d files, final executable, doc and memory dumps
clean:
	rm -f $(USERNAME) $(USERNAME).zip
	rm -f $(OBJECTS) $(DEPENDS)
	rm -f $(TEST_OBJECTS) $(TEST_DEPENDS) $(TEST_FILE)
	rm -f core
	rm -fr doc
	rm -f logs.txt err.txt



# PRIVATE
# this part get's removed, because some weido said we can use make commands only
# so this part is in fact illegal, do it gets removed from zip
.PHONY: zip lines

# --- ZIP ----------------------------------------------------------------------
ZIP := $(SOURCES) $(HEADERS) $(TEST_SOURCES) $(TEST_HEADERS) $(EXAMPLES) $(ASSETS) Doxyfile zadani.txt prohlaseni.txt

zip: $(USERNAME).zip

$(USERNAME).zip: $(ZIP) Makefile
	@rm -fr zip_tmp
	@rm -f $(USERNAME).zip
	@mkdir -p zip_tmp/$(USERNAME)
	@cp --parents -r $(ZIP) zip_tmp/$(USERNAME)
	@cat Makefile | awk -f Makefile_filter.awk > zip_tmp/$(USERNAME)/Makefile
	@cd zip_tmp/ && zip -r ../$@ $(USERNAME)/
	@rm -fr zip_tmp
	@echo $(USERNAME).zip created


# --- LINE COUNT ---------------------------------------------------------------
lines:
	@echo Lines in project:
	@cat $(SOURCES) $(HEADERS) | grep . | wc -l




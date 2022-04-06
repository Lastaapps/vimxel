# C++ compiler
CXX	=	g++

# C++ compiler options
DEBUG	= true
ifeq ($(DEBUG),true)
	CXXFLAGSDEBUG	=
else
	CXXFLAGSDEBUG	= -g3 -fsanitize=address
endif
CXXFLAGS	=	-std=c++17 -pedantic -Wall $(CXXFLAGSDEBUG)

# External libraries used
LIBS	=	-lncourser
# Linker options
LFLAGS =
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
#SOURCES := $(shell find . -name '*.cpp' | sed 's/\.\///' )
#HEADERS := $(shell find . -name '*.hpp' -or -name '*.h' | sed 's/\.\///' )

# These task will be run also if files of their name exists
.PHONY: all clean doc run compile




# --- DEFAULT, CORE ------------------------------------------------------------
# build all
default:	all
all:	compile doc

# Build executable file
compile:	$(USERNAME)

# Runs compiled binary
run:
	@./$(USERNAME)




# --- DOCS ---------------------------------------------------------------------
# Create documentation in the doc/ folder
doc: doc/html/index.html

doc/html/index.html: $(SOURCES) $(HEADERS) Doxyfile Makefile
	@doxygen




# --- CLEAN UP -----------------------------------------------------------------
# clean up
# delete .o files, .d files, final executable, doc and memory dumps
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(USERNAME) core
	rm -fr doc




# --- COMPILATION --------------------------------------------------------------
# link the final program
$(USERNAME) : $(OBJECTS) Makefile
	$(CXX) $(LFLAGS) $(OBJECTS) -o $@

# includes .d files as dependencies
-include	$(DEPENDS)

# compile a C++ module and create .d files
%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@


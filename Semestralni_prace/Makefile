# Base structure provided by Jiří Kašpar, thanks a lot

# C++ compiler
CXX	=	g++

# C++ compiler options
DEBUG	= true
ifeq ($(DEBUG),true)
	CXXFLAGSDEBUG	=
else
	CXXFLAGSDEBUG	= -g3 -fsanitize=address
endif
CXXFLAGSRELEASE	=	-std=c++17 -pedantic -Wall
CXXFLAGS	=	$(CXXFLAGSRELEASE) $(CXXFLAGSDEBUG)

# External libraries used
LIBS	=	-lncourser
# Linker options
LFLAGS =
# My username, used as output filename
USERNAME =	lastope2

# all .o modules to make
# find . -name '*.cpp' | sed 's/.cpp/.o/g' | sed 's/\.\///' | tr '\n' ' '
MODULES	= src/main.o src/table/table.o

# all programs to build
# find . -name '*.cpp' | sed 's/.cpp//g' | sed 's/\.\///' | tr '\n' ' '
ALL	= src/main

# build all
default:	all
all:	compile doc

# Build executable file
compile:	$(USERNAME)

# Runs compiled code
run:
	@./$(USERNAME)

# Create documentation in the doc/ folder
doc:


# make dependencies
depend:
	cp Makefile Makefile_tmp
	awk -f Makefile_depend_reset.awk Makefile_tmp > Makefile
	rm Makefile_tmp
	find . -name "*.cpp" -exec $(CXX) -MM {} + >> Makefile

# clean up
# delete .o files, executables, final executable and code dumps
clean:
	rm -f $(MODULES) $(ALL) $(USERNAME) core

# link the final program
$(USERNAME) : $(MODULES) Makefile
	$(CXX) $(LFLAGS) $(MODULES) -o $@

# compile a C++ module
%.o : %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Task dependency graph
# output of g++ -MM *.cpp
# The line below is used as a marker for awk script
# DELETE_THESE_UNDER_ME_ON_DEPEND
main.o: src/main.cpp src/table/table.hpp
table.o: src/table/table.cpp src/table/table.hpp

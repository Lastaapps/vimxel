# Provided by Jiří Kašpar, thanks a lot
# PA2 Makefile template
CC	=	gcc
CXX	=	g++
CXXFLAGS	=       -std=c++17 -pedantic -Wall
CFLAGS	= 	-Wall -pedantic -g3 -fsanitize=address
LIBS	=	-lncourser
LFLAGS =

# all .o modules to make
#         ls *.cpp | sed 's/.cpp/.o/g' | tr '\n' ' '
MODULES	=

# all programs to build
#         ls *.cpp | sed 's/.cpp//g' | tr '\n' ' '
ALL	= main

# build all
default:	$(ALL) $(MODULES)

# make dependencies
depend:
	cp Makefile Makefile_tmp
	cat Makefile_tmp | awk -f Makefile_depend_reset.awk > Makefile
	rm Makefile_tmp
	g++ -MM *.cpp >> Makefile

# clean up
clean:
	rm -f $(MODULES) $(ALL) core

# link a program from several modules
#prog : $(MODULES) Makefile
#	$(CXX) $(LFLAGS) $(MODULES) -o $@

# compile & link a C++ program
% : %.cpp Makefile
	$(CXX) $(CXXFLAGS) $< $(LFLAGS) $(MODULES) -o $@

# compile a C++ module
%.o : %.cpp Makefile
	$(CXX)  $(CXXFLAGS) -c $< -o $@

# here add output of "g++ -MM *.cpp >>Makefile"
# DELETE_ME
main.o: main.cpp

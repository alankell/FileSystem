# Makefile
# Project: OS-Final Project-File System
# Date: 2017/12/11

CXX := g++
INCLUDE  = . 
CXXFLAGS = -std=c++11 -g -w
OBJDIR	:= obj
BINDIR	:= bin
SRCDIR	:= src
SRC		:= $(wildcard $(SRCDIR)/*.cpp)
INC		:= $(wildcard $(SRCDIR/*.cpp))
OBJ		:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
#CXXFLAGS += -Wall -g 


EXE  := fs
SRCS := main.cpp

#---------------- COMPILE -----------------------------------
all: $(EXE)
	@printf "\033[32m[Info]:\033[0m Complete! Execution file:"
	@printf "\033[92;1m %s\033[0m\n" "$(EXE)"
$(EXE): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(EXE) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

#----------------- CLEAN --------------------------------------	

clean:
	@printf "\033[32m[Info]:\033[0m Clean all obj files.\n"
	@rm -rf $(OBJDIR)/*.o

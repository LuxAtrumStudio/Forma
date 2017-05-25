CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	@printf "Compiling $*.cpp...\n"
	@$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore magenta; printf "$(shell pwd)/input:\n"; setterm -fore white
	cd input && $(MAKE)
	@setterm -fore magenta; printf "$(shell pwd)/object:\n"; setterm -fore white
	cd object && $(MAKE)
	@setterm -fore magenta; printf "$(shell pwd)/shader:\n"; setterm -fore white
	cd shader && $(MAKE)
	@setterm -fore magenta; printf "$(shell pwd)/window:\n"; setterm -fore white
	cd window && $(MAKE)

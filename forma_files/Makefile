CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(notdir $(CPP_FILES:.cpp=.o))

all: $(OBJ_FILES) subsystem

%.o: %.cpp %.hpp
	$(COMPILER) $(FLAGS) -o $(notdir $*).o $*.cpp

.PHONY : subsystem
subsystem:
	@setterm -fore blue
	@printf "FRAMEWORK/\n";
	@setterm -fore white
	@cd framework && $(MAKE)
	@setterm -fore green
	@printf "WINDOW/\n";
	@setterm -fore white
	@cd window && $(MAKE)
	@setterm -fore cyan
	@printf "OBJECT/\n";
	@setterm -fore white
	@cd object && $(MAKE)

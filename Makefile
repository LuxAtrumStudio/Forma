
SHELL=/bin/bash
ifndef .VERBOSE
    .SILENT:
endif
ROOT=$(shell pwd)
CXX=clang++
CC=clang
CCIGNORE=
CXXIGNORE=
CCFLAGS=-fPIC -Wall -Wpedantic --static
CXXFLAGS=-std=c++17 -fPIC -Wall -Wpedantic --static -DDEV
LINK=
SOURCE=src
INCLUDE_DIR=include
INCLUDE=
BUILD=build
COMMON_INCLUDE=-I$(ROOT)/$(INCLUDE_DIR) $(INCLUDE)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[1;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C++ object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef

all: build-forma.exe
clean: clean-forma.exe
install: install-forma.exe
uninstall: uninstall-forma.exe

# FORMA.EXE {{{

FORMA.EXE=forma.exe
FORMA.EXE_FILES=$(SOURCE)/main.cpp
FORMA.EXE_OBJS=$(FORMA.EXE_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(FORMA.EXE_OBJS:.o=.d)

build-forma.exe: build-libforma.a pre-forma.exe $(FORMA.EXE)
	$(call complete_target,$(shell basename $(FORMA.EXE)))

clean-forma.exe:
	$(call clean_target,$(shell basename $(FORMA.EXE)))
	if [ -e "$(FORMA.EXE)" ]; then rm $(FORMA.EXE); fi

pre-forma.exe:
	$(call scan_target,$(shell basename $(FORMA.EXE)))

$(FORMA.EXE): $(FORMA.EXE_OBJS) FORCE
	$(call print_link_exe,$(shell basename $(FORMA.EXE)))
	$(CXX) $(FORMA.EXE_OBJS) $(LIBFORMA.A) $(LINK) $(COMMON_INCLUDE) -o $(FORMA.EXE)

install-forma.exe: build-forma.exe
	$(call install_target,$(shell basename $(FORMA.EXE)))
	mkdir -p $(INSTALL_PATH)/bin/
	cp $(FORMA.EXE) $(INSTALL_PATH)/bin

uninstall-forma.exe:
	$(call uninstall_target,$(shell basename $(FORMA.EXE)))
	if [ -e "$(INSTALL_PATH)/bin/$(shell basename $(FORMA.EXE))" ]; then rm $(INSTALL_PATH)/bin/$(shell basename $(FORMA.EXE)); fi

# }}}
# LIBFORMA.A {{{

LIBFORMA.A=$(BUILD)/libforma.a
LIBFORMA.A_FILES=$(filter-out $(SOURCE)/main.cpp, $(shell find "$(SOURCE)/" -name "*.cpp"))
LIBFORMA.A_OBJS=$(LIBFORMA.A_FILES:%=$(ROOT)/$(BUILD)/%.o)
-include $(LIBFORMA.A_OBJS:.o=.d)

build-libforma.a:  pre-libforma.a $(LIBFORMA.A)
	$(call complete_target,$(shell basename $(LIBFORMA.A)))

clean-libforma.a: 
	$(call clean_target,$(shell basename $(LIBFORMA.A)))
	if [ -e "$(LIBFORMA.A)" ]; then rm $(LIBFORMA.A); fi

pre-libforma.a:
	$(call scan_target,$(shell basename $(LIBFORMA.A)))

$(LIBFORMA.A): $(LIBFORMA.A_OBJS) FORCE
	$(call print_link_lib,$(shell basename $(LIBFORMA.A)))
	ar rcs $@ $(LIBFORMA.A_OBJS)
	

install-libforma.a: build-libforma.a
	$(call install_target,$(shell basename $(LIBFORMA.A)))
	mkdir -p $(INSTALL_PATH)/lib/
	mkdir -p $(INSTALL_PATH)/include/$(NAME)/
	cp $(LIBFORMA.A) $(INSTALL_PATH)/lib
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.h") $(INSTALL_PATH)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(sehll cd $(SOURCE_DIR) && find . -name "*.hpp") $(INSTALL_PATH)/include/$(NAME); fi

uninstall-libforma.a:
	$(call uninstall_target,$(shell basename $(LIBFORMA.A)))
	if [ ! -e "$(INSTALL_PATH)/lib/$(shell basename $(LIBFORMA.A))" ]; then rm $(INSTALL_PATH)/lib/$(shell basename $(LIBFORMA.A)); fi
	if [ ! -e "$(INSTALL_PATH)/include/$(NAME)" ]; then rm $(INSTALL_PATH)/include/$(NAME) -r; fi

# }}}

$(ROOT)/$(BUILD)/%.cpp.o: %.cpp
	mkdir -p $(@D)
	$(call print_build_cpp,$@)
	$(CXX) $(CXXFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

$(ROOT)/$(BUILD)/%.c.o: %.c
	mkdir -p $(@D)
	$(call print_build_c,$@)
	$(CC) $(CCFLAGS) -MMD -c $(COMMON_INCLUDE) $< -o $@

FORCE:

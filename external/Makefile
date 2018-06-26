SHELL = /bin/bash

DIR = $(EXTERNAL_DIR)
SUB_NAME = "External"

define print
printf "%b%s%b\n" "$(2)" "$(1)" "$(NO_COLOR)"
endef

all: gtest glfw

.PHONY : clean
clean: gtest_clean glfw_clean


GTEST_ALL = $(BASE_PATH)/$(BUILD_DIR)/gtest/gtest-all.o
GTEST_MAIN = $(BASE_PATH)/$(BUILD_DIR)/gtest/gtests_main.o
GTEST_DIR = $(BASE_PATH)/$(EXTERNAL_DIR)/googletest/googletest

.PHONY : gtest
gtest: gtest_start $(GTEST_ALL) $(GTEST_MAIN)
	$(call print,Linking libgtest.a,$(LINK_COLOR))
	ar -rc $(BASE_PATH)/$(BUILD_DIR)/libgtest.a $(GTEST_ALL)
	$(call print,Linking libgtest_main.a,$(LINK_COLOR))
	ar -rc $(BASE_PATH)/$(BUILD_DIR)/libgtest_main.a $(GTEST_MAIN)

.PHONY : gtest_start
gtest_start:
	$(call print,GoogleTest Library,$(TARGET_COLOR))

.PHONY : gtest_clean
gtest_clean: gtest_start
	$(call print,Removing gtest,$(CLEAN_COLOR))
	if [ -d "$(BASE_PATH)/$(BUILD_DIR)/gtest" ]; then\
	  rm $(BASE_PATH)/$(BUILD_DIR)/gtest -r; fi
	$(call print,Removing libgtest.a,$(CLEAN_COLOR))
	if [ -e "$(BASE_PATH)/$(BUILD_DIR)/libgtest.a" ]; then\
	  rm $(BASE_PATH)/$(BUILD_DIR)/libgtest.a; fi
	$(call print,Removing libgtest_main.a,$(CLEAN_COLOR))
	if [ -e "$(BASE_PATH)/$(BUILD_DIR)/libgtest_main.a" ]; then\
	  rm $(BASE_PATH)/$(BUILD_DIR)/libgtest_main.a; fi

$(GTEST_ALL):
	mkdir -p $(@D)
	$(call print,Building $@,$(COMPILE_COLOR))
	$(COMPILER) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(GTEST_MAIN):
	mkdir -p $(@D)
	$(call print,Building $@,$(COMPILE_COLOR))
	$(COMPILER) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc -o $@

.PHONY : glfw
glfw: glfw_start
	if [ ! -f "./glfw/Makefile" ]; then\
	  $(call print,Running CMake,$(COMPILE_COLOR));\
	  cd glfw && cmake -DCMAKE_INSTALL_PREFIX:PATH=$(BASE_PATH)/$(BUILD_DIR)/glfw .;\
	  fi
	if [ ! -d "$(BASE_PATH)/$(BUILD_DIR)/glfw" ]; then\
	  $(call print,Compiling and installing GLFW,$(COMPILE_COLOR)); \
	  cd glfw && make all install ;\
	  fi

.PHONY : glfw_start
glfw_start:
	$(call print,GLFW Library,$(TARGET_COLOR))

.PHONY : glfw_clean
glfw_clean: glfw_start
	$(call print,Removing GLFW Library,$(CLEAN_COLOR))
	if [ -d "$(BASE_PATH)/$(BUILD_DIR)/glfw" ]; then \
	  $(call print,Removing Installed Files,$(CLEAN_COLOR)); \
	  rm -r $(BASE_PATH)/$(BUILD_DIR)/glfw; \
	fi

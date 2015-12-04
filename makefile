#===============================================================================
# This makefile is meant to be used while learning to program in C (or with
# minor modifications C++). For this reason, the programs built by this makefile
# are optimized for debugability not for performance. This makefile has been
# tested with clang version 3.7 on OS X and Linux.
#
# Please enter your name below:
#
lastname = LASTNAME
firstname = FIRSTNAME
#
# Make sure the project name below is correct:
#
project_name = Assignment12
#
# If you are working from home, enter the location of your copy of clang below:
#
CC =
#
# You will use the following commands provides by this makefile:
#
# make                    -  builds the project
# make run                -  runs the built project
# make memcheck           -  run program with memory checker
# make package            -  creates deliverable package on the Desktop
# make package-nocompile  -  creates deliverable package without compiling
# make clean              -  remove binary files
#
# Author: Michael J Bannister (7/2015)
# version: 0.3
#===============================================================================


#################################################
#### DO NOT CHANGE ANYTHING BELOW THIS LINE! ####
#################################################


#### Start: Variables ####

# Variables for C compiler (CC), warning flags (WFLAGS), debug flags (DFLAGS)
# and sanitizer flags (SFLAGS).
ifneq ($(ALTCC),)
	CC = $(ALTCC)
endif
ifeq ($(wildcard $(CC)),)
	# The location of clang on lab computers.
	CC = /common/cs/cs062/clang/bin/clang
endif
WFLAGS = -Wall -Wextra -pedantic
DFLAGS = -g -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls
SFLAGS = -fsanitize=address,undefined
CSTD   = -std=c11
CFLAGS += $(CSTD) $(WFLAGS) $(DFLAGS)

# Variables for locations of source (SRC), header (HDR) files.
location = $(shell pwd)
SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)

#### End: Variables ####


#### Start: Compiling rules ####

.PHONY: all
all: bin/$(project_name).san.out

# Compile for use with sanitizer
bin/$(project_name).san.out: $(SRC) $(HDR) bin/
	$(CC) $(CFLAGS) $(SFLAGS) $(SRC) -o ./bin/$(project_name).san.out

# Compile for use with valgrind or other debuggers
bin/$(project_name).out: $(SRC) $(HDR) bin/
	$(CC) $(CFLAGS) $(SRC) -o ./bin/$(project_name).out

# Create bin directory if missing
bin/:
	mkdir bin

#### End: Compiling rules ####


#### Start: Running rules ####

.PHONY: run
run: bin/$(project_name).san.out
	@./bin/$(project_name).san.out \
		|| echo "\n\033[1;31m*** Program failed to successfully exit. ***\033[0m"

VFLAGS = --tool=memcheck --leak-check=yes --track-origins=yes --show-reachable=yes
.PHONY: memcheck
memcheck: bin/$(project_name).out
	@valgrind $(VFLAGS) ./bin/$(project_name).out \
		|| echo "\n\033[1;31m*** Program failed to successfully exit. ***\033[0m"

#### End: Running rules


#### Start: Packaging rules ####

space_char = $(subst ,, )
package_name = $(subst $(space_char),_,$(project_name) $(lastname) $(firstname))
package_dir = ~/Desktop/

.PHONY: package
package: bin/$(project_name).san.out | package-nocompile

.PHONY: package-nocompile
package-nocompile:
	@mkdir $(package_dir)$(package_name) 2> /dev/null \
		&& cp -r . $(package_dir)$(package_name) \
		&& echo "\n\033[1;32m*** Folder $(package_name) ready to turn in. ***\033[0m" \
		|| echo "\n\033[1;31m*** Folder $(package_name) already exists. Please rename or move this folder. ***\033[0m"


#### End: Packaging rules ####


#### Start: Cleaning rules ####

.PHONY: clean
clean:
	rm -r bin/* ||:

#### End: Cleaning rules ####

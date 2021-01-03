MAKEFLAGS=--warn-undefined-variables

TARGET ?= poke_cereal

BUILD ?= build/
SRC_DIR ?= src/
BIN_DIR ?= bin/
INC_DIR ?= include/
ASSETS_DIR ?= assets/

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%.cpp=$(BUILD)%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := $(addprefix -I,$(INC_DIR))

CFLAGS  := -march=native -std=c++17 -Og -ggdb -Wall -Werror -Wextra -Wunused -Wconversion -Wunused-macros -fno-strict-aliasing $(INC_FLAGS) -MMD -MP
LD_FLAGS := -march=native -std=c++17 -fwhole-program -Xlinker -Map=$(BIN_DIR)x86.map
#-flto in CFLAGS can reduce size, but greatly increases compile time. -O2 for speed.

all: $(BIN_DIR)$(TARGET).exe $(ASSETS_DIR)PBS/PBS/pokemon.txt
	$(BIN_DIR)$(TARGET).exe -p $(ASSETS_DIR)PBS/PBS/pokemon.txt -m $(ASSETS_DIR)PBS/PBS/moves.txt

$(BIN_DIR)$(TARGET).exe: $(OBJS)
	$(MKDIR_P) $(dir $@)
	g++ $^ $(LD_FLAGS) -o $@
	
# c source
$(BUILD)%.o: %.cpp
	$(MKDIR_P) $(dir $@)
	g++ $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf bin
	$(RM) -rf build

.PHONY: all clean

-include $(DEPS)

MKDIR_P ?= mkdir -p

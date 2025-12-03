CC          := gcc
EXE_DIR     := exe
EXE_FILE    := $(EXE_DIR)/main.exe

SRC_DIR  := c
OBJ_DIR  := o
SRCS     := $(shell find $(SRC_DIR) -name *.c )
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
ccInc    := $(addprefix -I,./$(shell find $(SRC_DIR) -type d))

cl_DIR   := cl
cl_h_DIR := cl_h
cl_s     := $(shell find $(cl_DIR) -name *.cl )
cl_h_s   := $(patsubst $(cl_DIR)/%.cl,$(cl_h_DIR)/%_cl.h,$(cl_s))
clInc    := -I./$(cl_h_DIR)

CCFLAGS := $(ccInc) $(clInc)
LDFLAGS := -lOpenCL -lm
################################################################################

# Target rules
all: build

build:$(cl_h_s) $(EXE_FILE)

$(OBJS): $(cl_h_s)

# Link executable
$(EXE_FILE):$(OBJS) | $(EXE_DIR)
	$(CC) -o $@ $(OBJS) $(CCFLAGS) $(LDFLAGS)

# Compile C source .c -> obj/*.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c |$(OBJ_DIR)
	$(CC) -c $< -o $@ $(CCFLAGS)

# Embed kernels: .cl -> _cl.h
$(cl_h_DIR)/%_cl.h: $(cl_DIR)/%.cl | $(cl_h_DIR)
	xxd -i -n $* $< > $@

$(OBJ_DIR):
	mkdir -p $@

$(cl_h_DIR):
	mkdir -p $@

$(EXE_DIR):
	mkdir -p $@

.PHONY:run
run: build
	./$(EXE_FILE)

.PHONY:clean
clean:
	rm -rf $(OBJ_DIR) $(cl_h_DIR) $(EXE_DIR)

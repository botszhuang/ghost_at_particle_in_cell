CC          := gcc
EXE_DIR     := exe
EXE_FILE    := $(EXE_DIR)/main.exe

SRC_DIR  := src/
OBJ_DIR  := obj/
SRCS     := $(shell find $(SRC_DIR) -name *.c )
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
ccInc    := $(addprefix -I,$(shell find $(SRC_DIR) -type d))

cl_DIR   := cl/
cl_h_DIR := cl_h/
cl_s     := $(shell find $(cl_DIR) -name *.cl )
cl_h_s   := $(patsubst $(cl_DIR)/%.cl,$(cl_h_DIR)/%_cl.h,$(cl_s))
clInc    := $(addprefix -I,$(shell find $(cl_h_DIR) -type d))

CCFLAGS := -std=c++17 $(ccInc) $(clInc)
LDFLAGS := -lOpenCL -lm 
################################################################################

# Target rules
all: build

build:$(EXE_FILE) 

# Embed kernels: .cl -> _cl.h
$(cl_h_DIR)/%_cl.h: $(cl_DIR)/%.cl
	mkdir -p $(cl_h_DIR)
	xxd -i $< > $@

# Compile C source .c -> obj/*.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(cl_h_s)
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CCFLAGS) 

# Link executable
$(EXE_FILE):$(OBJS)
	mkdir -p  $(EXE_DIR)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)


.PHONY:run 
	run: build 
	./$(EXE_FILE)
	
.PHONY:clean
clean:
	rm -rf $(OBJ_DIR) $(cl_h_DIR) $(EXE_DIR)


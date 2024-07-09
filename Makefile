#( MAKEFILE FOR C/C++ PROJECTS )
# >>> common
CC					:= clang++
CFLAGS				:= -std=c++23 -Wall -Wextra -g #-Qunused-arguments #-std=c23
LDFLAGS   			:= -lglfw -lGL -lGLEW -lGLU -lOpenGL -lassimp -lX11 -lpthread -lm
SHOW_CMD  			?=#@

# >>> directory structure
BIN_DIR   			:= build
OBJ_DIR   			:= $(BIN_DIR)/obj
SRC_DIR				:= src
VENDOR_DIR 			:= $(SRC_DIR)/vendor
PACKAGE_DIR 		:= $(SRC_DIR)/package
TEST_DIR 			:= #$(SRC_DIR)/test

# >>> gathering source files
SRCS 				:= $(shell find $(SRC_DIR) -type f -name '*.cpp' -o -name '*.c')
OBJS 				:= $(strip $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))))
TARGET     			:= $(BIN_DIR)/program

# >>> patterns for compilation
SOURCE_DIRS 		:= $(SRC_DIR) $(VENDOR_DIR) $(PACKAGE_DIR) $(TEST_DIR)
SOURCE_PATTERNS 	:= $(strip $(foreach dir, $(SOURCE_DIRS), $(dir)/*/%.cpp $(dir)/*/%.c $(dir)/%.cpp $(dir)/%.c))

# >>> rules
.PHONY: all clean dirs check build run vari
all: build

# >>> print variables
vari:
	$(info ----- [State of the variables] ------------------)
	$(info SRC_DIR:             $(SRC_DIR))
	$(info PACKAGE_DIR:    	    $(PACKAGE_DIR))
	$(info VENDOR_DIR:          $(VENDOR_DIR))
	$(info TEST_DIR:            $(TEST_DIR))
	$(info SRCS:                $(SRCS))
	$(info OBJS:                $(OBJS))
	$(info SOURCE_PATTERNS:     $(SOURCE_PATTERNS))
	$(info -------------------------------------------------)
	@echo
# <<< print variables

define compile_source_file
$(OBJ_DIR)/%.o: $(1)
	@@echo "$$(BLUE)$$(BD_SYS) Compiling: '$$<' to an object files. $$(RESET)"
	$$(SHOW_CMD)$$(CC) $$(CFLAGS) -c $$< -o $$@
endef

build: dirs check $(TARGET)
$(foreach pattern, $(SOURCE_PATTERNS), $(eval $(call compile_source_file, $(pattern))))
$(TARGET): $(OBJS)
	@echo "$(BLUE)$(BD_SYS) Linking with '$(<U>)$(CC)$(</U>)' into an executable ./$(<U>)$(TARGET)$(</U>) $(RESET)"
	$(SHOW_CMD)$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
# <<<
run: build
	@echo "$(GREEN)$(BD_SYS) Running the executable. $(RESET)"
	$(SHOW_CMD)./$(TARGET)
# <<<
val: 
	@echo "$(GREEN)$(BD_SYS) Running the executable with $(RED)$(<U>)Valgrind$(</U>). $(RESET)"
	$(SHOW_CMD)valgrind -q --tool=memcheck --track-origins=no --error-exitcode=1 --track-origins=yes ./$(TARGET) 
# <<<
clean: 
	@if [ -d "$(BIN_DIR)" ]; then \
		echo -e "$(GREEN)$(BD_SYS) Removing the '$(<U>)$(BIN_DIR)$(</U>)' directory. $(RESET)"; \
		rm -rf $(OBJ_DIR); \
	else \
  		echo "$(RED)$(BD_SYS) Error: Directory '$(<U>)$(BIN_DIR)$(</U>)' does not exist."; \
	fi
# <<<
dirs:
ifeq (,$(wildcard $(OBJ_DIR)))
	@echo "$(GREEN)$(BD_SYS) Creating the directory system. $(RESET)"
	$(SHOW_CMD)mkdir -p $(OBJ_DIR) $(BIN_DIR) $(SRC_DIR) $(PACKAGE_DIR) $(VENDOR_DIR) $(TEST_DIR)
endif
# <<<
check:
	@echo "$(GREEN)$(BD_SYS) Checking for modifications in '$(<U>)$(SRC_DIR)$(</U>)' directory:$(RESET)"
	@modified=false; \
	for src in $(SRCS); do \
		if [ "$${src##*.}" = "c" ]; then \
			obj=$(OBJ_DIR)/$$(basename $$src .c).o; \
		else \
			obj=$(OBJ_DIR)/$$(basename $$src .cpp).o; \
		fi; \
		if [ ! -f $$obj ] || [ $$src -nt $$obj ]; then \
			modified=true; \
			echo "$(BOLD)  Source file '$(<U>)$$src$(</U>)' has been modified or the object file does not exist.$(RESET)"; \
		fi; \
	done; \
	if [ "$$modified" = false ]; then \
		echo "$(BOLD)  $(<U>)No changes$(</U>) in source files.$(RESET)"; \
	fi
# <<<
%:
	@echo "$(RED)$(BD_SYS) Error: Non-valid rule ('$(MAKECMDGOALS)') provided.$(RESET)"
# <<<

# >>> colors and shit
BOLD    	:= $(shell tput bold)
<U>     	:= $(shell tput smul)
</U>    	:= $(shell tput rmul)
RESET   	:= $(shell tput sgr0)
BLACK   	:= $(shell tput setaf 0)
RED     	:= $(shell tput setaf 1)
GREEN   	:= $(shell tput setaf 2)
YELLOW  	:= $(shell tput setaf 3)
BLUE    	:= $(shell tput setaf 4)
MAGENTA 	:= $(shell tput setaf 5)
CYAN    	:= $(shell tput setaf 6)
WHITE   	:= $(shell tput setaf 7)
TAB     	:= $(shell echo -e "\t")
BD_SYS  	:= $(BOLD)"[$(<U>)BUILD$(</U>)]"
# <<< colors and shit

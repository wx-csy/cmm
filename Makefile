TARGET_NAME = parser

CC      = gcc
LD      = gcc
FLEX	= flex
BISON	= bison

CLFAGS  += -std=gnu99 -Wall 
CFLAGS  += -ggdb -fsanitize=undefined -fsanitize=address

BUILD_DIR     = build
SRC_DIR       = src
INCLUDE_DIR   = include

SRCS = $(shell find $(SRC_DIR)/ -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS += -I./$(INCLUDE_DIR)

.PHONY : lex syntax parser run clean

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo + [CC] $@
	@$(CC) $(CFLAGS) -c -o $@ $<

$(SRC_DIR)/lexical/lex.yy.c : $(SRC_DIR)/lexical/lexical.l
	@mkdir -p $(dir $@)
	@echo + [FLEX] $@
	@$(FLEX) -o $@ $<

$(SRC_DIR)/syntax/syntax.tab.c : $(SRC_DIR)/syntax/syntax.y
	@mkdir -p $(dir $@)
	@echo + [BISON] $@
	@$(BISON) -o $@ $<

$(INCLUDE_DIR)/syntax/syntax.tab.h : $(SRC_DIR)/syntax/syntax.y
	@mkdir -p $(dir $@)
	@echo + [BISON] $@
	@$(BISON) --defines=$@ -o /dev/null $<

lexical : $(SRC_DIR)/lexical/lex.yy.c

syntax : $(INCLUDE_DIR)/syntax/syntax.tab.h $(SRC_DIR)/syntax/syntax.tab.c

$(BUILD_DIR)/$(TARGET_NAME) : $(OBJS)
	@mkdir -p $(dir $@)
	@echo + [LD] $@
	@$(CC) $(CFLAGS) -o $@ $^

$(TARGET_NAME): $(BUILD_DIR)/$(TARGET_NAME)

run: lexical syntax $(TARGET_NAME)
	./$(BUILD_DIR)/$(TARGET_NAME)

clean :
	@echo - [RM] $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)

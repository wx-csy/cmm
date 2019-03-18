TARGET_NAME = parser

CC      = gcc
LD      = gcc
FLEX	= flex
BISON	= bison

CFLAGS  += -std=gnu99 -Wall
CFLAGS  += -ggdb -fsanitize=undefined -fsanitize=address

BUILD_DIR     = build
SRC_DIR       = src
INCLUDE_DIR   = include

SRCS = $(SRC_DIR)/cmm/error.c $(SRC_DIR)/lexical/lex.yy.c $(SRC_DIR)/syntax/syntax.tab.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS += -I./$(INCLUDE_DIR)

.DEFAULT_GOAL = run
.PHONY : $(TARGET_NAME) run clean

# generate dependency files
$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo + [DEP] $@
	@$(CC) $(CFLAGS) -M -MMD -o $@ $<

-include $(OBJS:.o=.d)

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
	@$(BISON) --defines=$(INCLUDE_DIR)/syntax/syntax.tab.h -o $@ $<

$(INCLUDE_DIR)/syntax/syntax.tab.h : $(SRC_DIR)/syntax/syntax.tab.c

$(BUILD_DIR)/$(TARGET_NAME) : $(OBJS)
	@mkdir -p $(dir $@)
	@echo + [LD] $^
	@$(LD) $(CFLAGS) -o $@ $^

$(TARGET_NAME): $(BUILD_DIR)/$(TARGET_NAME)

run: $(TARGET_NAME)
	./$(BUILD_DIR)/$(TARGET_NAME)

clean :
	@echo - [RM] $(BUILD_DIR) $(INCLUDE_DIR)/syntax/syntax.tab.h $(SRC_DIR)/syntax/syntax.tab.c $(SRC_DIR)/lexical/lex.yy.c 
	@rm -rf $(BUILD_DIR) $(INCLUDE_DIR)/syntax/syntax.tab.h $(SRC_DIR)/syntax/syntax.tab.c $(SRC_DIR)/lexical/lex.yy.c 



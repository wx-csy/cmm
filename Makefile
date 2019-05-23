TARGET_NAME = parser
PACKAGE_NAME = 161240004.zip

CC      = gcc
LD      = gcc
FLEX	= flex
BISON	= bison

CFLAGS  += -std=gnu11 -Wall -ggdb -O1
# CFLAGS  += -fsanitize=undefined -fsanitize=address
# CFLAGS  += -DDEBUG

LDFLAGS = $(CFLAGS)
LDFLAGS += -lfl -ly

BUILD_DIR     = Build
SRC_DIR       = Code
INCLUDE_DIR   = Include

GENERATED = $(INCLUDE_DIR)/syntax.tab.h $(SRC_DIR)/syntax.tab.c $(SRC_DIR)/lex.yy.c \
    $(TARGET_NAME)

SRCS = $(shell find $(SRC_DIR) -type f \
    \( -iname "*.c" -not \( -iname "*.yy.c" -or -iname "*.tab.c" \) \) )
SRCS += $(SRC_DIR)/syntax.tab.c $(SRC_DIR)/lex.yy.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS += -iquote./$(INCLUDE_DIR)
CFLAGS += -I./$(INCLUDE_DIR)/container

.DEFAULT_GOAL = $(TARGET_NAME)
.PHONY : run clean package

# generate dependency files
$(BUILD_DIR)/%.d : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo + [DEP] $@
	@$(CC) $(CFLAGS) -M -MMD -o $@ $<

-include $(COBJS:.o=.d)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo + [CC] $@
	@$(CC) $(CFLAGS) -c -o $@ $<

$(SRC_DIR)/lex.yy.c : $(SRC_DIR)/lexical.l $(INCLUDE_DIR)/syntax.tab.h
	@mkdir -p $(dir $@)
	@echo + [FLEX] $@
	@$(FLEX) -o $@ $<

$(SRC_DIR)/syntax.tab.c : $(SRC_DIR)/syntax.y
	@mkdir -p $(dir $@)
	@echo + [BISON] $@
	@$(BISON) --defines=$(INCLUDE_DIR)/syntax.tab.h -o $@ $<

$(INCLUDE_DIR)/syntax.tab.h : $(SRC_DIR)/syntax.tab.c

$(BUILD_DIR)/$(TARGET_NAME) : $(OBJS)
	@mkdir -p $(dir $@)
	@echo + [LD] $@
	@$(LD) $(LDFLAGS) -o $@ $^

$(TARGET_NAME): $(BUILD_DIR)/$(TARGET_NAME)
	@echo + [CP] $@
	@cp $< $@

run: $(TARGET_NAME)
	./$(TARGET_NAME)

clean :
	@echo - [RM] $(BUILD_DIR) $(GENERATED) $(PACKAGE_NAME)
	@rm -rf $(BUILD_DIR) $(GENERATED) $(PACKAGE_NAME)

$(PACKAGE_NAME): $(TARGET_NAME)
	@echo + [ZIP] $@
	@rm -rf $@
	@zip -r $@ Code Include README.txt testrun.sh Test report.pdf report.md parser Makefile -x Test/.\* Test/README.md

package: $(PACKAGE_NAME)

CC	= gcc
FLEX	= flex
BISON	= bison

.PHONY : lex clean

Build/%.tab.h : Code/%.y
	@mkdir -p $(dir $@)
	@echo + [BISON]\\t$@
	@$(BISON) --defines=$@ -o $(basename $@).c -d $<

Build/%.tab.c : Build/%.tab.h

Build/%.yy.c : Code/%.l 
	@mkdir -p $(dir $@)
	@echo + [FLEX]\\t$@
	@$(FLEX) -o $@ $<

lex : Build/lexical.yy.c

syntax : Build/syntax.tab.h Build/syntax.tab.c

clean :
	rm -rf Build

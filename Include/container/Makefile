TARGETS = vector 

.DEFAULT_GOAL := build
.PHONY : build .FORCE

build : 
	@for target in $(TARGETS); do \
		echo ">>> " $${target}; \
		(cd $${target} && make) ; \
	done

clean : 
	@for target in $(TARGETS); do \
		echo ">>> " $${target}; \
		(cd $${target} && make clean) ; \
	done

.FORCE :


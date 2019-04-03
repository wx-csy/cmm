TARGETS = vector 

.DEFAULT_GOAL := build
.PHONY : build .FORCE

build : 
	@for target in $(TARGETS); do \
		echo ">>> " $${target}; \
		(cd $${target} && make) ; \
		cp $${target}/header.h $${target}.h; \
		echo [CP] $${target}.h; \
	done

clean : 
	@for target in $(TARGETS); do \
		echo ">>> " $${target}; \
		(cd $${target} && make clean) ; \
		rm -f $${target}.h; \
	done

.FORCE :


SUBDIRS = day*
test: $(SUBDIRS)
	for i in $^; do make -C $$i test; done

all: $(SUBDIRS)
	for i in $^; do make -C $$i all; done
clean: $(SUBDIRS)
	for i in $^; do make -C $$i clean; done

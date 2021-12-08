SUBDIRS = day*

all: $(SUBDIRS)
	for i in $^; do make -C $$i all; done
clean: $(SUBDIRS)
	for i in $^; do make -C $$i clean; done
test: $(SUBDIRS)
	for i in $^; do make -C $$i test; done

SUBDIRS = task_1 task_2

default: 
	for dir in $(SUBDIRS); do \
        $(MAKE) -C $$dir; \
    done

clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done
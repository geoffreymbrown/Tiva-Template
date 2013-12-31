SUBDIRS= Build Tiva Demo UartEcho

.PHONY:  clean 

all:   startup_lm4f.c
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE)); done

startup_lm4f.c : startup_generator
	./startup_generator > startup_lm4f.c

startup_generator:
	gcc -o startup_generator startup_generator.c

clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean); done
	rm startup_lm4f.c startup_generator

	

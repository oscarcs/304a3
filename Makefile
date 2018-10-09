OPT = -O1

default: assignment

assignment: task1 task2

task1:
	gcc task1.c $(OPT) -o task1

task2:
	gcc task2.c $(OPT) -o task2

clean:
	rm -f task1
	rm -f task2


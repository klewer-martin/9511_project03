CC=gcc
CFLAGS=-pedantic -Wall -g
SRCFOLDER=source
HFOLDER=include
PROGNAME=main

all: main clean

main: cla.o status.o utils.o main.o user.o vector.o
	$(CC) $(CFLAGS) main.o cla.o status.o utils.o user.o vector.o -o $(PROGNAME)

main.o: $(HFOLDER)/cla.h $(HFOLDER)/status.h $(HFOLDER)/user.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/main.c

cla.o: $(HFOLDER)/cla.h $(HFOLDER)/status.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/cla.c

vector.o: $(HFOLDER)/vector.h $(HFOLDER)/status.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/vector.c

status.o: $(HFOLDER)/status.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/status.c

utils.o: $(HFOLDER)/status.h $(HFOLDER)/user.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/utils.c

user.o: $(HFOLDER)/status.h $(HFOLDER)/user.h
	$(CC) $(CFLAGS) -c $(SRCFOLDER)/user.c

clean:
	rm *.o

run5:
	./main -fmt csv -out output.csv -in examples/test_file_5.csv -ti 1320498000 -tf 1320498046

run20:
	./main -fmt csv -out output.csv -in examples/test_file_20.csv -ti 1320498000 -tf 1320498046

run2k:
	./main -fmt csv -out output.csv -in examples/test_file_2k.csv -ti 1320498000 -tf 1325499000

run50:
	./main -fmt csv -out output.csv -in examples/test_file_50.csv -ti 1320498000 -tf 1320498049

run500:
	./main -fmt csv -out output.csv -in examples/test_file_500.csv -ti 1320498000 -tf 1320529000

run5k:
	./main -fmt csv -out output.csv -in examples/test_file_5k.csv -ti 1320498000 -tf 1320529000

run50k:
	./main -fmt csv -out output.csv -in examples/test_file_50k.csv -ti 1320498000 -tf 1420529000

run100k:
	./main -fmt csv -out output.csv -in examples/test_file_100k.csv -ti 1320498000 -tf 1420529000

run500k:
	./main -fmt csv -out output.csv -in examples/test_file_500k.csv -ti 1320498000 -tf 1420529000

run1m:
	./main -fmt csv -out output.csv -in examples/test_file_1m.csv -ti 1320498000 -tf 1420529000

run10m:
	./main -fmt csv -out output.csv -in examples/test_file_10m.csv -ti 1320498000 -tf 1420529000

run5m:
	./main -fmt csv -out output.csv -in examples/test_file_5m.csv -ti 1320498000 -tf 1420529000

run50xml:
	./main -fmt xml -out output.xml -in examples/test_file_50.csv -ti 1320498000 -tf 1320498049

run5kxml:
	./main -fmt xml -out output.xml -in examples/test_file_5k.csv -ti 1320498000 -tf 1360498049

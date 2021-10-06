SRC = ./src
INC = ./include
OBJS = test.o dwnldr.o region.o kiwit.o
CFLAGS = -lcurl -lpthread -lcrypto
test: $(OBJS)
	gcc -o test $(OBJS) $(CFLAGS)

test.o: test.c $(INC)/dwnldr.h
	gcc -c test.c -I $(INC)

dwnldr.o: $(SRC)/dwnldr.c $(INC)/dwnldr.h
	gcc -c $(SRC)/dwnldr.c -I $(INC)

kiwit.o: $(SRC)/kiwit.c $(INC)/kiwit.h
	gcc -c $(SRC)/kiwit.c -I $(INC)

region.o: $(SRC)/region.c
	gcc -c $(SRC)/region.c -I $(INC)

clean:
	rm -rf ./*.o test

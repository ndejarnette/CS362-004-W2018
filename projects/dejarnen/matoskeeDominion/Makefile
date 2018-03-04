CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	#./testDrawCard &> unittestresult.out
	#./unittest1 &> unittestresult.out
	./unittest1 &>> unittestresult.out
	echo "getCost stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/getCost/{n;p; n;p; n;p; n;p}' >> unittestresult.out
	./unittest2 &>> unittestresult.out
	echo "isGameOver stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/isGameOver/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./unittest3 &>> unittestresult.out
	echo "compare stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/compare/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./unittest4 &>> unittestresult.out
	echo "numHandCards stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/numHandCards/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./cardtest1 &>> unittestresult.out
	echo "card_smithy stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/card_smithy/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./cardtest2 &>> unittestresult.out
	echo "village stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/village/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./cardtest3 &>> unittestresult.out
	echo "card_council_room stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/card_council_room/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	./cardtest4 &>> unittestresult.out
	echo "adventurer stats: " >> unittestresult.out
	gcov -abcfu dominion.c | sed -n '/card_adventurer/{n;p; n;p; n;p; n;p;}' >> unittestresult.out
	#cat dominion.c.gcov >> unittestresult.out
	./randomtestadventurer &>> randomtestadventurer.out
	echo "card_adventurer stats" >> randomtestadventurer.out
	gcov -abcfu dominion.c | sed -n '/card_adventurer/{n;p; n;p; n;p; n;p}' >> randomtestadventurer.out
	./randomtestcard1 &>> randomtestcard1.out
	echo "card_smithy stats" >> randomtestcard1.out
	gcov -abcfu dominion.c | sed -n '/card_smithy/{n;p; n;p; n;p; n;p}' >> randomtestcard1.out
	./randomtestcard2 &>> randomtestcard2.out
	echo "village card stats" >> randomtestcard2.out
	gcov -abcfu dominion.c | sed -n '/cardEffect/{n;p; n;p; n;p; n;p}' >> randomtestcard2.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 \
	unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer \
	runtests

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard badTestDrawCard.exe
	rm -f unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe
	rm -f cardtest1 cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe
	rm -f randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe randomtestadventurer randomtestadventurer.exe


all: test_1 test_2 test_3 test_4 test_5 test_6

test_1: test1.c
	gcc -Wall -Werror -o test_1 test1.c
		
test_2: test2.c
	gcc -Wall -Werror -o test_2 test2.c

test_3: test3.c
	gcc -Wall -Werror -o test_3 test3.c
	
test_4: test4.c
	gcc -Wall -Werror -std=gnu99 -pthread -o test_4 test4.c

test_5: test5.c
	gcc -Wall -Werror -o test_5 test5.c
	
test_6: test6.c
	gcc -Wall -Werror -std=gnu99 -pthread -o test_6 test6.c
	
clean: 
	rm -f test_?

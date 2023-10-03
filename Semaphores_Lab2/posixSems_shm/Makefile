all: semtest_a semtest_b

semtest_a: semtest_a.c
	gcc -g -Wall semtest_a.c -o semtest_a

semtest_b: semtest_b.c
	gcc -g -Wall semtest_b.c -o semtest_b

clean:
	rm -f semtest_a semtest_b

build:
	@echo COMPILE MYADD
	gcc -c myadd.c
	@echo COMPILE MAIN
	gcc -c main.c
	@echo LINK
	gcc main.o myadd.o
	@echo EXECUTE
	test "$$(./a.out)" = "3157"
	@echo SUCCESS

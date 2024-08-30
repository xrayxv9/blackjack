C_files = main.c main_game.c sources.c lyb.h
O_files = main.o main_game.o sources.o
CC = cc -Wall -Werror -Wextra
AC_files = account_in_game.c manage_account.c main_game.c lyb.h
AO_files = account_in_game.o manage_account.o main_game.o




output: $(O_files)
	$(CC) -o output $(O_files)
	rm *.o lyb.h.gch

$(O_files): $(C_files)
	$(CC) -c $(C_files)

account: $(AO_files)
	$(CC) -o output $(AO_files)
	rm *.o lyb.h.gch

$(AO_files): $(AC_files)
	$(CC) -c $(AC_files)

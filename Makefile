all:
	gcc src/main.c src/sqliteManager/manager.c -lsqlite3 -o executable.o

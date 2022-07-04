all:
	gcc src/main.c src/sqliteManager/manager.c src/dateManager/dateManager.c -lsqlite3 -o executable.o

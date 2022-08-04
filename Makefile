CC = gcc
MAIN_O_CFLAGS = -lpaho-mqtt3c -lpthread
CFLAGS = -c -g
JSONMANAGER_O_CFLAGS = -ljson-c
SQLITE_MANAGER_CFLAGS = -lsqlite3 

all: mainapp

mainapp: main.o mqttMessageParser.o jsonManager.o sqliteManager.o setup.o
	$(CC) $(MAIN_O_CFLAGS) $(JSONMANAGER_O_CFLAGS) $(SQLITE_MANAGER_CFLAGS) main.o mqttMessageParser.o jsonManager.o sqliteManager.o -o domoticHouseExecutable
	$(CC) $(SQLITE_MANAGER_CFLAGS) setup.o sqliteManager.o -o domoticHouseRemoteDBSetup
	mv domoticHouseExecutable executables/remoteDatabaseExecutable/
	mv domoticHouseRemoteDBSetup executables/remoteDatabaseExecutable/
	mv *.o build/

main.o: src/remoteDatabaseSrc/main.c
	$(CC) $(CFLAGS) $(MAIN_O_CFLAGS) src/remoteDatabaseSrc/main.c 

mqttMessageParser.o: src/remoteDatabaseSrc/mqttMessageParser/mqttMessageParser.c 
	$(CC) $(CFLAGS) src/remoteDatabaseSrc/mqttMessageParser/mqttMessageParser.c

jsonManager.o: src/remoteDatabaseSrc/jsonManager/jsonManager.c
	$(CC) $(CFLAGS) $(JSONMANAGER_O_CFLAGS) src/remoteDatabaseSrc/jsonManager/jsonManager.c

sqliteManager.o: src/remoteDatabaseSrc/sqliteManager/manager.c
	$(CC) $(CFLAGS) $(SQLITE_MANAGER_CFLAGS) src/remoteDatabaseSrc/sqliteManager/manager.c -o sqliteManager.o

setup.o: src/remoteDatabaseSrc/setup.c
	$(CC) $(CFLAGS) src/remoteDatabaseSrc/setup.c

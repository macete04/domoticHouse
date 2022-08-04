/*
 * This file is the main program that runs the remote database. 
 * It is a MQTT client that receives messages and sends other messages, based on what is the input from the received message.
 * */

#include<stdio.h>
#include<MQTTClient.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#include"mqttMessageParser/mqttMessageParser.h"
#include"jsonManager/jsonManager.h"


// callback functions
void messageDelivered(void *context, MQTTClient_deliveryToken deliveryToken); // will have to understand what 'context' is and why it's needed here
int messageArrived(void *context, char* topicName, int topicLength, MQTTClient_message *message);
void connectionLost(void *context, char* cause);

#define BROKER "tcp://cow.rmq2.cloudamqp.com:1883"
#define CLIENT_ID "client_id"
#define TOPIC "ciao/come/va"
#define QOS 1

#define CONFIG_JSON_SIZE 1024

int main(){

  printf("Process id: %d\n", getpid());
  
  mqttClientInfos mqttStuff;
  mqttClientInfos* ptr_mqttStuff = &mqttStuff;

  FILE* ptr_configFile;
  char* buffer = malloc(CONFIG_JSON_SIZE);
  memset(buffer, 0, CONFIG_JSON_SIZE);

  // to keep this directory to open the file you have to start the proram from INSIDE 
  // the executables/remoteDatabaseExecutable/ dir
  ptr_configFile = fopen("../../src/remoteDatabaseSrc/config.json", "r");
  
  // segfault happens here.
  fread(buffer, CONFIG_JSON_SIZE, 1, ptr_configFile);
  
  bool isSuccess = getInfosFromConfigFile(buffer, &ptr_mqttStuff);
  free(buffer); 
  
  printf("%d", mqttStuff.topicsArrayLength);

  MQTTClient mqttClient;
	MQTTClient_connectOptions connectionOptions = MQTTClient_connectOptions_initializer;
	MQTTClient_create(&mqttClient, mqttStuff.broker, mqttStuff.clientID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	
	connectionOptions.keepAliveInterval = 20; // secs
	connectionOptions.cleansession = true;

  connectionOptions.username = mqttStuff.username;
  connectionOptions.password = mqttStuff.password;
	
	MQTTClient_setCallbacks(mqttClient, NULL, connectionLost, messageArrived, messageDelivered);	
	
	// connecting to broker
	int rc = 0;
	if(rc = MQTTClient_connect(mqttClient, &connectionOptions) != MQTTCLIENT_SUCCESS){
		printf("Failed to connect to broker, error code: %d", rc);
		MQTTClient_destroy(&mqttClient); // freeing up memory
		exit(EXIT_FAILURE);
	}
	
	printf("Connection completed successfully!\nSubscribing to given topic(s)\n");
	for(short int i = 0; i < mqttStuff.topicsArrayLength; ++i){
    MQTTClient_subscribe(mqttClient, mqttStuff.topics[i], QOS);
  }
	printf("Subscriptions complete\n");
  
  // loop to wait for messages
	char thing;
	do {
		thing = getchar();
	}while(thing != 'Q' && thing != 'q'); // gotta catch ctrlC too?

	MQTTClient_disconnect(mqttClient, 1000);
	MQTTClient_destroy(&mqttClient);
	
	return 0;
}

void messageDelivered(void *context, MQTTClient_deliveryToken deliveryToken){

	printf("Message with token %d delivered successfully", deliveryToken);

}

int messageArrived(void *context, char* topicName, int topicLength, MQTTClient_message *message){
	
	printf("A message has arrived\n");
  
  // I'm using threads as i can't call a function or the program will crash (deadlock)
  pthread_t t1;
  if(pthread_create(&t1, NULL, &mqttMessageParser, (void*)message->payload) != 0){

    printf("An error occured while creating the thread");

  }
  if(pthread_join(t1, NULL) != 0){

    printf("An error occured while joining thread");
  
  } 
  
  return 1;  
}

void connectionLost(void *context, char* cause){

	printf("Connection has been lost, due to: %s", cause);

}

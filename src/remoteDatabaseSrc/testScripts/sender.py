import paho.mqtt.publish as publish

import json as js

dati_per_grafici = {
  "date":"15-07-2022",
  "hour":18,
  "device":"deviceName",
  "request" : 0,  
  "measurements":{
    "temperature":23.5,
    "humidity":66.700000000000003,
    "co2":234
  }
}

dati_per_boh = {
        "hourOrDay":"date",
        "deviceID":"deviceName",
        "request":1,
        "chosenParameter":1,
        "minDate": "12-07-2022", 
        "maxDate": "14-07-2022"
}

dati_per_grafici = js.dumps(dati_per_grafici)
dati_per_boh = js.dumps(dati_per_boh)

credentials = {'username': 'qqgorhjw:qqgorhjw',
               'password': 'eUyUIYzmhC5UIW1nWUE0pBUmcgornIwz'}

instruction = input("insert a or b (a for request = 0, b for request = 1)")

if instruction == 'a':

         publish.single("ciao/come/va", dati_per_grafici,
                       hostname="cow.rmq2.cloudamqp.com", port=1883, auth=credentials)
elif instruction == 'b':

         publish.single("ciao/come/va", dati_per_boh,
                       hostname="cow.rmq2.cloudamqp.com", port=1883, auth=credentials)

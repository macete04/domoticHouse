import paho.mqtt.publish as publish

import json as js

dati_per_grafici = {
  "date":"12-07-2022",
  "hour":14,
  "device":"deviceName",
  "request" : 0,  
  "measurements":{
    "temperature":27.5,
    "humidity":65.700000000000003,
    "co2":234
  }
}

dati_per_boh = {
        "hourOrDay":"date",
        "deviceID":"deviceName",
        "request":1, 
        "maxDate": "12-12-2012", 
        "minDate": "8-12-2012"
}

dati_per_grafici = js.dumps(dati_per_grafici)
dati_per_boh = js.dumps(dati_per_boh)

credentials = {'username': 'yourUsername',
               'password': 'yourPwd'}

instruction = input("insert a or b (a for request = 0, b for request = 1)")

if instruction == 'a':

         publish.single("ciao/come/va", dati_per_grafici,
                       hostname="cow.rmq2.cloudamqp.com", port=1883, auth=credentials)
elif instruction == 'b':

         publish.single("ciao/come/va", dati_per_boh,
                       hostname="cow.rmq2.cloudamqp.com", port=1883, auth=credentials)

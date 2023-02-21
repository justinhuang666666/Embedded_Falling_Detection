import paho.mqtt.client as mqtt
import time
import json

class MQTTClient:
    def __init__(self, broker_address, portnum):
        self.client = mqtt.Client("P1")
        self.connected = False
        self.broker_address = broker_address
        self.port = portnum
        self.connect_broker()

    def connect_broker(self):
        if self.client.connect(self.broker_address,self.port) != 0: 
            print("could not connect")
            sys.exit(-1)
        print('connected to server')
        time.sleep(0.4)
        self.client.loop_start()
    
    def publish(self, topic, message):
        self.client.publish(topic, json.dumps(message))
        #print("Publishing... " + topic)
    
    def stop(self):
        self.client.loop_stop()

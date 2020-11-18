import paho.mqtt.client as paho
import time

broker = "broker.hivemq.com"
port = 1883
publish_topic = "Dev/ESP32/Test/"


def on_publish(client, userdata, result):  # create function for callback
    print("data published \n")
    pass


client1 = paho.Client("control2")  # create client object
client1.on_publish = on_publish  # assign function to callback
client1.connect(broker, port)  # establish connection


client1.publish(publish_topic, "1")
time.sleep(5)
client1.publish(publish_topic, "0")
time.sleep(5)
client1.publish(publish_topic, "1")
time.sleep(5)
client1.publish(publish_topic, "0")

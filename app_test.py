# GUI
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
#from PyQt5.QtWidgets import QPushButton

# MQTT
import paho.mqtt.client as paho
#broker = "broker.hivemq.com"
broker = "172.31.92.244"
port = 1883
#publish_topic = "Dev/ESP32/Test/"
publish_topic = "test"


class MainWindow(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):

        self.resize(350, 270)
        self.setWindowTitle('Cuarto_IoT')

        self.mqttclient = paho.Client('franco')
        self.mqttclient.connect(broker, port)

        btn1 = QPushButton('abrir', self)
        btn1.setGeometry(50, 50, 250, 50)
        btn1.clicked.connect(self.abrir)

        btn1 = QPushButton('cerrar', self)
        btn1.setGeometry(50, 150, 250, 50)
        btn1.clicked.connect(self.cerrar)
        # btn1.clicked.connect(self.new_window)

    def abrir(self):
        # self.mqttclient = paho.Client('franco')
        # self.mqttclient.connect(broker, port)
        self.mqttclient.publish(publish_topic, "1")
        print('Abriendo puerta', '90 grados')

    def cerrar(self):
        # self.mqttclient = paho.Client('franco')
        # self.mqttclient.connect(broker, port)
        self.mqttclient.publish(publish_topic, "0")
        print('Cerrando puerta', '90 grados')

    # def new_window(self):
    #     self.w = MainWindow_2()  # atributo de la clase


def main():
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()

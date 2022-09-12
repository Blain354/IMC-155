from ctypes import sizeof
import socket
import json
import time
from struct import pack, unpack

sock = socket.socket()

host = "192.168.137.246" #ESP32 IP in local network
port = 80            #ESP32 Server Port

sock.connect((host, port))
while True:
    data = sock.recv(8)
    data_clean  = unpack('d',data)
    print(f"{data_clean[0]:.4f}")
sock.close()
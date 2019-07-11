import socket
import os

UDP_IP = "192.168.1.2"
UDP_PORT = 8888

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True: #listen the port as long as the PC is awake
	response, addr = sock.recvfrom(255)
	response_str = response.decode("cp1252") #from bytes to string
	if len(response_str) == 9 :
		os.system('shutdown now') #shutdown the PC



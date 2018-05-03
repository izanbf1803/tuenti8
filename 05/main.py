import socket, sys, subprocess

debug = True

def send(msg):
	global debug, sock
	msg = msg
	sock.sendall(msg.encode())
	if debug: print("send:", msg)

def recive():
	global debug, sock
	msg = sock.recv(512).decode().replace('\n', '')
	if debug: print("recive:", msg)
	return msg

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
addr = ("52.49.91.111", 3241)
sock.connect(addr)

recive()
recive()
send("TEST\n")
while True:
	recive()
	chains = recive()
	print("chains:", chains)
	output = subprocess.Popen(' '.join(["a.exe"]+chains.split()), stdout=subprocess.PIPE, shell=True).communicate()[0].decode()
	print("out:", output)
	send(output)
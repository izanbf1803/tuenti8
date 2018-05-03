import socket, sys, subprocess

debug = True

def send(msg):
    global debug, sock
    msg = msg
    sock.sendall(msg.encode())
    if debug: 
        print("send:", msg)
        print("---------------------")

def recive():
    global debug, sock
    msg = sock.recv(512).decode().replace('\n', '')
    if debug: 
        if len(msg) > 0:
            print("recive:", msg)
        print("---------------------")
    return msg

addr = ("52.49.91.111", 3240)

while True:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(addr)
    print("CONNECTED:\n---------------------")

    send("live\n")
    recive()
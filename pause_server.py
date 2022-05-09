# Pauser Server
from pynput.keyboard import Key, Controller
import socket

kb = Controller()

ip = socket.gethostname()
port = 9516

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind((ip, port))

while True:
    data, addr = s.recvfrom(1)
    
    data = data.decode()
    
    if data == 'a':
        kb.press(Key.left)
        kb.release(Key.left)
    elif data == 's':
        kb.press(Key.space)
        kb.release(Key.space)
    else:
        kb.press(Key.right)
        kb.release(Key.right)
    

s.close

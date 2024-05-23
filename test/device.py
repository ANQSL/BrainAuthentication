import socket
import time

with open("raw_data.bin", "rb") as f:
    device_data = f.read()
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.1.101', 5001))

time.sleep(20)
print("开始传输")
for i in range(120000):
    send_data = device_data[i*103:(i + 1) * 103]
    value=send_data[7:10]
    send_data = bytearray(send_data)
    send_data[0] = 0xa1
    send_data[1] = 0x05
    s.send(send_data)
    time.sleep(0.001)

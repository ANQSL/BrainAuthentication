# 通信线程，主要负责与采集的通信
import json
import socket
import struct
import threading
import time
import numpy as np

calculate_result = 0
calculate_status = False
# recv_data = []
recv_data = None
recv_status = False
lock = threading.Lock()


class Communication(threading.Thread):
    def __init__(self, channel_num, samplerate):
        super().__init__()
        # 数据服务端口
        self.data_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.data_server.bind(("", 7777))
        self.data_server.setblocking(False)
        self.data_server.listen(1)
        self.data_client = None
        # 接收数据
        self.recv_data = None
        # 命令服务端口
        self.command_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.command_server.bind(("", 7778))
        self.command_server.setblocking(False)
        self.command_server.listen(1)
        self.command_client = None
        # 解析配置
        self.channel_num = channel_num
        self.samplerate = samplerate
        self.time_seq = 5
        self.data_len = 1

    def data_recv(self):
        global calculate_result, calculate_status, recv_data, recv_status
        if self.data_client:
            lock.acquire()
            try:
                if self.recv_data is None:
                    self.recv_data = self.data_client.recv(self.channel_num * 8 * self.samplerate)
                else:
                    data = self.data_client.recv(self.channel_num * 8 * self.samplerate)
                    if not data:
                        self.data_client = None
                    self.recv_data = self.recv_data + data
                if len(self.recv_data) >= (self.channel_num * 8 * self.samplerate * self.time_seq):
                    data = self.recv_data[0:self.channel_num * 8 * self.samplerate * self.time_seq]
                    self.recv_data = self.recv_data[self.channel_num * 8 * self.samplerate * self.time_seq:-1]
                    data = struct.unpack("{}d".format(self.channel_num * self.samplerate * self.time_seq), data)
                    data = np.reshape(np.array(data), (self.time_seq, self.samplerate, self.channel_num))
                    recv_data = np.transpose(data, (0, 2, 1))
                    recv_status = True
            except socket.error as e:
                if e.errno == 10054:
                    self.data_client = None
                if e.errno == 10053:
                    self.data_client = None
                # print(e)
            lock.release()
        else:
            try:
                self.data_client, _ = self.data_server.accept()
                calculate_result = 0
                calculate_status = False
                recv_data = []
                recv_status = False
                print("采集连接")
            except Exception as e:
                print("没有连接")

    def back_result(self):
        global calculate_result, calculate_status, recv_data
        if calculate_status:
            if self.data_client is not None:
                try:
                    # result = struct.pack('i', calculate_result)
                    result = json.dumps(calculate_result).encode(encoding="utf8")
                    # print(result)
                    self.data_client.send(result)
                    print("计算结果：{}".format(calculate_result))
                    # 用于一次性识别中需要去除之前的数据,例如身份识别，而像认知任务着不需要
                    lock.acquire()
                    self.recv_data = None
                    lock.release()
                except Exception as e:
                    print(e)
            calculate_status = False

    def command_recv(self):
        if self.command_client:
            try:
                data = self.command_client.recv(self.channel_num * 8 * self.samplerate)
                if not data:
                    self.command_client = None
                else:
                    command = str(data, 'utf-8')
                    print(command)
            except socket.error as e:
                if e.errno == 10054:
                    self.command_client = None
                if e.errno == 10053:
                    self.command_client = None
        else:
            try:
                global recv_data
                self.command_client, _ = self.command_server.accept()
                self.recv_data = None
                recv_data = None
                print("采集连接")
            except Exception as e:
                print("没有连接")

    def run(self):
        while (1):
            self.data_recv()
            self.back_result()
            time.sleep(1)

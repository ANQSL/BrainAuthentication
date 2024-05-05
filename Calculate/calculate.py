import time

import threading

import copy
import random

import numpy as np

import communicate


class Calculate(threading.Thread):
    def __init__(self):
        super().__init__()

    def run(self):
        while (1):
            if communicate.recv_status:
                # 数据复制
                communicate.lock.acquire()
                data = copy.deepcopy(communicate.recv_data)
                communicate.lock.release()
                communicate.recv_status = False

                print("开始计算")
                # 计算
                start_time = time.time()

                # 计算结束
                print("计算结束")
                communicate.calculate_status = True
            time.sleep(2)

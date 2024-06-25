import time

import threading

import copy
import random

import numpy as np
import yaml

import communicate

from identity_recognition.infer import Inference


class Calculate(threading.Thread):
    def __init__(self):
        super().__init__()
        config_path = "identity_recognition/config/config_mat.yaml"
        cfg_file = open(config_path, 'r')
        cfg = yaml.safe_load(cfg_file)
        self.inference = Inference(cfg)

    def run(self):
        while (1):
            if communicate.recv_status:
                # 数据复制
                communicate.lock.acquire()
                data = copy.deepcopy(communicate.recv_data)
                communicate.lock.release()
                communicate.recv_status = False
                data = data.transpose(1, 0, 2)
                data = data.reshape(32, 5000)
                # np.save("data.npy", data)
                # pass
                print("开始计算")
                # 计算
                start_time = time.time()
                result = self.inference.infer(data, True)
                communicate.calculate_result = {"id": result["id"], "count": result["count"]}
                # 计算结束
                print("计算结束")
                communicate.calculate_status = True
            time.sleep(2)

import os
import sys

sys.path.append("D:\\project\\BrainAuthentication\\Calculate\\identity_recognition")
import scipy.io
import yaml

from identity_recognition.infer import Inference

config_path = "identity_recognition/config/config_mat.yaml"
cfg_file = open(config_path, 'r')
cfg = yaml.safe_load(cfg_file)
inference = Inference(cfg)
# 计算端数据
flies = os.listdir("real_time_data")
cal_result = []
for file in flies:
    path = os.path.join("real_time_data", file)
    data = scipy.io.loadmat(path)
    data = data["data"]
    cal_result.append(inference.infer(data))
print("计算端计算结果")
print(cal_result)
# 采集端数据
eeg = scipy.io.loadmat("off_time_data/raw_data.mat", struct_as_record=False, squeeze_me=True)
events = eeg["EEG"].event
events_index = []
for event in events:
    event_index = event.latency
    if event_index != 0:
        events_index.append(event_index)
print(events_index)
eeg = scipy.io.loadmat("off_time_data/filter_data.mat", struct_as_record=False, squeeze_me=True)
data = eeg["EEG"].data
samples = []
result = []
for event_index in events_index:
    samples.append(data[:, event_index:event_index + 5000])
for sample in samples:
    result.append(inference.infer(sample))
print("计算端计算结果")
print(cal_result)
print("采集端计算结果")
print(result)


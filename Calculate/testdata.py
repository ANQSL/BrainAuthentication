import numpy as np
import matplotlib.pyplot as plt

data = np.load("data.npy")
plt.figure(1)
fig, axes = plt.subplots(4, 6)
for i in range(4):
    for j in range(6):
        axes[i][j].plot(data[i * 4 + j])


save_data = []
for i in range(32):
    path = "identity_recognition/data/zqy/zqy5/ssvep/Channel_{}.txt".format(i + 1)
    with open(path) as f:
        file_data = f.read().split(" ")[0:5000]
        file_data = np.array(file_data)
        file_data = file_data.astype(np.int)
        file_data = np.expand_dims(file_data, 0)
        save_data.append(file_data)
save_data = np.concatenate(save_data, axis=0)
save_data = (save_data - 8388608) / 8388608 * 5000000 / 50
plt.figure(2)
fig, axes = plt.subplots(4, 6)
for i in range(4):
    for j in range(6):
        axes[i][j].plot(save_data[i * 4 + j])

plt.show()

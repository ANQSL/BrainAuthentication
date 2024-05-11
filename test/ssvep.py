import struct

import numpy as np
from matplotlib import pyplot as plt

with open("2024_05_07_1_ssvep.bin", "rb") as file:
    data = file.read()
    double_value = struct.unpack('d' * 5000 * 32, data)
double_value = np.array(double_value)
double_value = double_value.reshape(32, 5000)
print(double_value[0][0:100])

X=np.fft.fft(double_value[3])
X_magnitude = np.abs(X)
frequencies = np.fft.fftfreq(5000, 1/1000)
plt.figure(figsize=(10, 6))
plt.plot(frequencies[:5000//2], X_magnitude[:5000//2])
plt.xlim(0,10)
plt.xlabel('Frequency (Hz)')
plt.ylabel('Magnitude')
plt.title('Spectrum')
plt.grid(True)
plt.show()
import struct
import matplotlib.pyplot as plt
from collections import deque

# Binary file parameters
BIN_FILE = 'C:/Users/Lenovo/Desktop/tmp/Pindar/firmware/tools/imu_sensor_vbr_test/data.bin'


# Deque for storing data for plotting
data = {'timestamp': deque(), 'gyro_x': deque(), 'gyro_y': deque(), 'gyro_z': deque(),
        'accel_x': deque(), 'accel_y': deque(), 'accel_z': deque()}

# CRC16 function


def crc16(data):
    crc = 0xFFFF
    for b in data:
        x = crc >> 8 ^ b
        x ^= x >> 4
        crc = ((crc << 8) ^ ((x << 12)) ^ ((x << 5)) ^ (x)) & 0xFFFF
    return crc


# Open the binary file
with open(BIN_FILE, 'rb') as f:
    while True:
        # Read a packet from the binary file
        packet = f.read(33)  # 33 is the size of DataPack

        if len(packet) < 33:
            break

        # Unpack the packet
        datapack = struct.unpack('<BI3i3ihH', packet)

        # Check header and crc
        if datapack[0] != 0xAA:
            continue
        if crc16(packet[:-2]) != datapack[-1]:
            continue

        # Append the timestamp, accelerometer and gyroscope data to the deque
        data['timestamp'].append(datapack[1])
        data['gyro_x'].append(datapack[2])
        data['gyro_y'].append(datapack[3])
        data['gyro_z'].append(datapack[4])
        data['accel_x'].append(datapack[5])
        data['accel_y'].append(datapack[6])
        data['accel_z'].append(datapack[7])

# Plot the data
plt.figure(figsize=(12, 8))
plt.subplot(2, 1, 1)
plt.plot(data['timestamp'], data['gyro_x'], label='Gyro X')
plt.plot(data['timestamp'], data['gyro_y'], label='Gyro Y')
plt.plot(data['timestamp'], data['gyro_z'], label='Gyro Z')
plt.legend(loc='upper left')
plt.title('Gyroscope Data')

plt.subplot(2, 1, 2)
plt.plot(data['timestamp'], data['accel_x'], label='Accel X')
plt.plot(data['timestamp'], data['accel_y'], label='Accel Y')
plt.plot(data['timestamp'], data['accel_z'], label='Accel Z')
plt.legend(loc='upper left')
plt.title('Accelerometer Data')

plt.tight_layout()
plt.show()

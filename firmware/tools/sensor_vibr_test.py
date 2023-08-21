import serial
import matplotlib.pyplot as plt
from crccheck.crc import Crc8
import time

# Open the serial port
ser = serial.Serial('COM5', 9600)  # replace '/dev/ttyACM0' with your serial port

timestamps = []
gyroX = []
gyroY = []
gyroZ = []

try:
    while True:
        if ser.in_waiting:
            line = ser.readline().decode('utf-8').strip()  # read a '\n' terminated line
            data = line.split(',')
            if len(data) == 5:
                crc_received = int(data[4])
                crc_calculated = Crc8.calc(bytearray(','.join(data[:4]), 'utf-8'))
                if crc_received == crc_calculated:
                    timestamps.append(float(data[0]))
                    gyroX.append(float(data[1]))
                    gyroY.append(float(data[2]))
                    gyroZ.append(float(data[3]))

                    # Plot the data
                    plt.figure(1)
                    plt.clf()
                    plt.title('Gyro Data')
                    plt.grid(True)
                    plt.plot(timestamps, gyroX, 'r', label='X')
                    plt.plot(timestamps, gyroY, 'g', label='Y')
                    plt.plot(timestamps, gyroZ, 'b', label='Z')
                    plt.legend(loc='upper left')
                    plt.pause(0.01)

except KeyboardInterrupt:
    ser.close()
    plt.show()
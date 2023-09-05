import serial
from serial.tools import list_ports
import time

# Automatically select the first available serial port
port = list_ports.comports()[0].device

# Open the serial port
ser = serial.Serial(port, 115200)

# Open the output file
with open('data.bin', 'wb') as f:
    # Get the current time
    start_time = time.time()

    # Read data from the serial port for 10 seconds
    while time.time() - start_time < 10:
        if ser.in_waiting:
            data = ser.read(ser.in_waiting)  # read all available data
            # Write data to the file
            f.write(data)



# This application is a test for the serial communication between a NodeMCU
# and a Raspberry Pi or a Linux based computer. This script gets temperature
# and humidity data from the NodeMCU wireless mesh network over the serial port.

import serial.tools.list_ports
import time
import sys
import json

def find_arduino_port():
    # get a list of the available serial ports
    ports = serial.tools.list_ports.comports()

    # test if the NodeMCU board is connected
    for item in ports:
        if 'USB2.0-Serial' in item:
            port_name = str(item).split(' ')
            return port_name[0]

        else:
            return 'None'

com_port = find_arduino_port()

# if the NodeMCU board is connected
if com_port != 'None':

    # print the name of the serial port where the board is connected
    print('NodeMCU port found: {}'.format(com_port))

    # try to connect to the serial port
    try:
        ser = serial.Serial(com_port, baudrate = 9600, timeout = 1)
        
        # give 2 seconds for the connection to establish
        time.sleep(2)
        
        # print feedback and the connection object
        print('Connected to NodeMCU!')
        print(ser)

    # give feedback and stop the program on any connection error
    except:
        print('Connection issue!')
        sys.exit(1)

    # send the 'g' character to the NodeMCU board
    ser.write(b'g')
    
    # wait for the response
    arduino_data = ser.readline().decode().split('\r\n')
    data = json.loads(arduino_data[0])
    
    # print the received data
    print('Received from the NodeMCU:')
    print('==========================')
    print('Temperature: {} C'.format(float(data["TEMP"])))
    print('Humidity: {} %'.format(int(data["HUM"])))
    print('==========================')

    # close the serial connection
    ser.close()
    print('Connection closed!')

# if the NodeMCU board is not connected
else:
    print('NodeMCU port not found!')

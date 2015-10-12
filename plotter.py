import serial
from time import sleep
import math
import numpy as np
import matplotlib.pyplot as plt
import pickle
import json

def parse_serial(data):
	# Split serival values, convert to correct data types
	vals = data.split(" ")
	irValRight = int(vals[0])
	irValLeft = int(vals[1])
	rightSpeed = int(vals[2])
	leftSpeed = int(vals[3])

	return [irValRight, irValLeft, rightSpeed, leftSpeed]

if __name__ == '__main__':
	# Set up arrays to hold data

	irValLeftArr = []
	irValRightArr = []
	rightSpeedArr = []
	leftSpeedArr = []

	serin = ""

	# Set up the serial connection
	raw_input("Press ENTER to begin Serial connection. ")
	ser = serial.Serial('/dev/ttyACM0',9600,timeout=50)
	print "Hacking into the mainframe... "
	sleep(2)

	print "Hacking complete"
	sleep(1)
	raw_input("Press ENTER to begin. ")

	for i in xrange(300):

		# Check to see if data is available
		if (ser.inWaiting() > 0):
			serin = ser.readline()
			# print serin

		try:
			irValRight, irValLeft, rightSpeed, leftSpeed = parse_serial(serin)

			irValRightArr.append(np.clip(irValRight, 0, 1000))
			irValLeftArr.append(np.clip(irValLeft, 0, 1000))
			rightSpeedArr.append(np.clip(rightSpeed, 0, 150))
			leftSpeedArr.append(np.clip(leftSpeed, 0, 150))

		except Exception, e:
			print e
			sleep(.1)

		sleep(.1)

	f = open('data.txt', 'w')

	arrs = [irValRightArr, irValLeftArr, rightSpeedArr, leftSpeedArr]

	for arr in arrs:
		jsonstr = json.dumps(arr)
		f.write(jsonstr)
		f.write("\n")

	raw_input("Values have been written to data.txt - Press ENTER to exit.")

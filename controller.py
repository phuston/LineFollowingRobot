import serial
import os
from time import sleep


if __name__ == '__main__':
	serin = ""

	raw_input("Press ENTER to begin the serial connection.")
	os.system('clear')

	ser = serial.Serial('/dev/ttyACM1',9600,timeout=50)

	print("Hacking into the mainframe...")

	sleep(2)

	print("Hacking complete.")

	raw_input("Press ENTER to begin.")

	while True:
		new_p = raw_input("Enter 1, 2, or 3 to select P Constant of 5, 10, or 15: ")

		# Writes value 10 times to serial to account for dropped vals
		for i in xrange(10):
			ser.write(new_p)


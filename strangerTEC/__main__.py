import serial
import time
from tkinter import *
arduino_port = "COM3" 
baud_rate = 9600

root = Tk()
root.title('PokeTEC')
root.minsize(600, 600)
root.resizable(width=NO, height=NO)
is_fullscreen = True
root.attributes('-fullscreen', True)

def fullscreen(root):
    global is_fullscreen
    is_fullscreen = not is_fullscreen
    root.attributes('-fullscreen', is_fullscreen)
root.bind('<F11>',lambda x: fullscreen(root))

root.mainloop()
#PLANTILLA
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    print(f"Connected to {arduino_port}")
    
    time.sleep(2)

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"Arduino says: {line}")
            
except KeyboardInterrupt:
    print("\nClosing connection...")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()

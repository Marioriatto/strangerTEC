import serial
import time
from tkinter import *
from PIL import Image, ImageTk
import os

arduino_port = "COM3" 
baud_rate = 9600

def load_fondo():
    path = os.path.join(os.path.dirname(__file__),'assets','fondo.png')
    imagenCruda = Image.open(path)
    imagen = ImageTk.PhotoImage(imagenCruda)
    return imagen

def fullscreen(root):
    global is_fullscreen
    is_fullscreen = not is_fullscreen
    root.attributes('-fullscreen', is_fullscreen)

root = Tk()
root.title('strangerTEC')
root.minsize(600, 600)
root.resizable(width=NO, height=NO)
is_fullscreen = True
root.attributes('-fullscreen', is_fullscreen)
root.bind('<F11>',lambda event: fullscreen(root))

# PA DIBUJAR BIEN y UBICAR LOS WIDGETS
root.update_idletasks()

canvas = Canvas(root, width=root.winfo_width(), height=root.winfo_height())
canvas.pack(fill='both', expand=True, anchor='center')

imagen = load_fondo()
canvas.create_image(int(canvas.cget('width'))//2, int(canvas.cget('height'))//2, image=imagen)

canvas.create_text(
        root.winfo_width()//2,
        root.winfo_height() // 3,
        text="STRANGER\n       TEC",
        font=("Benguiat",60),
        fill="#ffffff",
        anchor='center'
    )
entry_value = StringVar(root)
entry = Entry(root, textvariable=entry_value, font=("Benguiat",20))
print(root.winfo_width()//2, root.winfo_height()//2)
entry.place(x=root.winfo_width()//2, y=(root.winfo_height()*2)//3, anchor='center')
root.mainloop()

def print(ser:serial):
    ser.writelines("'" + entry_value + "'")
#PLANTILLA
try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"Arduino says: {line}")
            
except KeyboardInterrupt:
    if 'ser' in locals() and ser.is_open:
        ser.close()
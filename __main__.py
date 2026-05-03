import serial
import time
from tkinter import *
from PIL import Image, ImageTk
import os
from random import randint
arduino_port = "COM3" 
baud_rate = 9600

frases = ["67", "SOS","JOYCE","MIKE","DUSTIN","LUCAS","WILL","DEMOGORGON","HAWKINS","SHEINBAUM"]

def load_fondo():
    path = os.path.join(os.path.dirname(__file__),'assets','fondo.png')
    imagenCruda = Image.open(path)
    imagen = ImageTk.PhotoImage(imagenCruda)
    return imagen

def fullscreen(root):
    global is_fullscreen
    is_fullscreen = not is_fullscreen
    root.attributes('-fullscreen', is_fullscreen)

def printSerial(ser:serial, frase:str):
    for char in frase:
        ser.write((char).encode('utf-8'))

def switch_screen(root, canvas, func, widgets=[], canvas_elements=[]):
    for widget in widgets:
        widget.place_forget()
    for element in canvas_elements:
        canvas.delete(element)
    func(root, canvas)

def screen_main(root, canvas):
    widgets = list()
    transmision_Escucha = Button(root, text="Transmisión y escucha", font=("Benguiat",20))
    transmision_Escucha.config(command=lambda :switch_screen(root=root, canvas=canvas, func=screen_escucha, widgets=widgets))
    transmision_Escucha.place(x=(root.winfo_width()//2)+250, y=(root.winfo_height()*2)//3, anchor='center')

    transmision_simple = Button(root, text="Transmisión simple", font=("Benguiat",20))
    transmision_simple.config(command=lambda :switch_screen(root=root, canvas=canvas, func=screen_simple, widgets=widgets))
    transmision_simple.place(x=(root.winfo_width()//2)-250, y=(root.winfo_height()*2)//3, anchor='center')

    widgets.append(transmision_Escucha)
    widgets.append(transmision_simple)

def screen_escucha(root, canvas):
    entry = Entry(root, textvariable=entry_value, font=("Benguiat",20))
    entry.place(x=root.winfo_width()//2, y=(root.winfo_height()*2)//3, anchor='center')
    
def screen_simple(root, canvas):
    widgets = list()
    elementos_canvas = list()
    elementos_canvas.append(canvas.create_text(
            root.winfo_width()//2,
            root.winfo_height()*2//3,
            text="Escribe: " + frases[randint(0,len(frases)-1)],
            font=("Benguiat",60),
            fill="#ffffff",
            anchor='center'
        ))
    printSerial(ser=ser, frase='!')

root = Tk()
root.title('strangerTEC')
root.minsize(600, 600)
root.resizable(width=NO, height=NO)
is_fullscreen = True
root.attributes('-fullscreen', is_fullscreen)
root.bind('<F11>',lambda event: fullscreen(root))

entry_value = StringVar(root)

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
screen_main(root, canvas)

root.mainloop()

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
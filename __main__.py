import serial
import time
from tkinter import *
from PIL import Image, ImageTk
import os
from random import randint
from threading import Thread
arduino_port = "COM3" 
baud_rate = 9600

letras = ['A','B','C','D','E','F','G','H','I','J','K','L','M',
          'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
          '1','2','3','4','5','6','7','8','9','0','+','-']
frases = ["67", "SOS","JOYCE","MIKE","DUSTIN","LUCAS","WILL","DEMOGORGON","HAWKINS","SHEINBAUM"]
escribir = False
frase_comunicacion_serial = str().encode('utf-8')
frase_escrita = list()

def interrupted_sleep():
    while escribir:
        time.sleep(0.1)

def printSerial(frase:str):
    global escribir
    global frase_comunicacion_serial
    for letter in frase:
        frase_comunicacion_serial = (letter).encode('utf-8')
        escribir = True
        # Esperar hasta que la letra esté escrita antes de continuar
        Thread(target=interrupted_sleep)
start = False
def serial_contact():
    global escribir
    global frase_comunicacion_serial
    global frase_escrita
    global start
    start = True
    #PLANTILLA
    try:
        ser = serial.Serial(arduino_port, baud_rate, timeout=1)
        time.sleep(2)
        while True:
            if ser.in_waiting > 0:
                c = ser.readline().decode('utf-8').rstrip()
                print(c)
                if c in letras:
                    print(c)
                    frase_escrita.append(c)
            if escribir:
                print(f"print(frase_comunicacion_serial): {frase_comunicacion_serial.decode('utf-8')}")
                ser.write(frase_comunicacion_serial)
                escribir = False
    except KeyboardInterrupt:
        if 'ser' in locals() and ser.is_open:
            ser.close()

def load_fondo():
    path = os.path.join(os.path.dirname(__file__),'assets','fondo.png')
    imagenCruda = Image.open(path)
    imagen = ImageTk.PhotoImage(imagenCruda)
    return imagen

def fullscreen(root):
    global is_fullscreen
    is_fullscreen = not is_fullscreen
    root.attributes('-fullscreen', is_fullscreen)

def switch_screen(root, canvas, func, widgets=[], canvas_elements=[]):
    for widget in widgets:
        widget.place_forget()
    for element in canvas_elements:
        canvas.delete(element)
    func(root, canvas)

def screen_main(root, canvas):
    if not start:
        Thread(target=serial_contact).start()
    widgets = list()
    transmision_Escucha = Button(root, text="Transmisión y escucha", font=("Benguiat",20))
    transmision_Escucha.config(command=lambda :switch_screen(root=root, canvas=canvas, func=screen_escucha, widgets=widgets))
    transmision_Escucha.place(x=(root.winfo_width()//2)+250, y=(root.winfo_height()*2)//3, anchor='center')

    transmision_simple = Button(root, text="Transmisión simple", font=("Benguiat",20))
    transmision_simple.config(command=lambda :switch_screen(root=root, canvas=canvas, func=screen_simple, widgets=widgets))
    transmision_simple.place(x=(root.winfo_width()//2)-250, y=(root.winfo_height()*2)//3, anchor='center')

    widgets.append(transmision_Escucha)
    widgets.append(transmision_simple)

accuracy = 0
def medir_puntaje(frase_original:str, canvas:Canvas, elementos_canvas, finish_button:Button):
    global accuracy
    global frase_escrita
    total = 0
    frase = "".join(frase_escrita)
    for index in range(min(len(frase_original), len(frase))):
        if frase_original[index] == frase[index]:
            total += 1
    print(f'{total}{len(frase)} {total / len(frase)}')
    accuracy =  total / len(frase)
    canvas.itemconfig(elementos_canvas[0], text=("Escribiste:\n" + str(frase) + "\nPrecision: " + str(accuracy*100) + "%"))
    finish_button.place_forget()
    frase_escrita = list()


def screen_escucha(root, canvas):
    entry = Entry(root, textvariable=entry_value, font=("Benguiat",20))
    entry.place(x=root.winfo_width()//2, y=(root.winfo_height()*2)//3, anchor='center')
    
def screen_simple(root, canvas):
    widgets = list()
    elementos_canvas = list()
    frase = frases[randint(0,len(frases)-1)]
    elementos_canvas.append(canvas.create_text(
            root.winfo_width()//2,
            (root.winfo_height()*2//3),
            text="Escribe: " + frase,
            font=("Benguiat",30),
            fill="#ffffff",
            anchor='center'
        ))
    finish_button =Button(root, text="Confirmar", font=("Benguiat",15))
    finish_button.config(command=lambda :medir_puntaje(frase, canvas, elementos_canvas, finish_button))
    finish_button.place(x=(root.winfo_width()//2), y=((root.winfo_height()*2)//3)+100, anchor='center')
    widgets.append(finish_button)
    Thread(target=printSerial, args=(['!'])).start()


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
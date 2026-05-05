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

def printSerial(frase:str):
    global escribir
    global frase_comunicacion_serial
    for letter in frase:
        frase_comunicacion_serial = letter
        escribir = True
        
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
                    frase_escrita.append(c)
            if escribir:
                for c in frase_comunicacion_serial:
                    print(c)
                    ser.write(c.encode('utf-8'))
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
    global frase_escrita
    frase_escrita = list()
    if func == screen_main:
        printSerial(['~'])
    for widget in widgets:
        widget.place_forget()
    for element in canvas_elements:
        canvas.delete(element)
    func(root, canvas)

def screen_main(root, canvas):
    global serial_thread
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
time_start = 0
accuracy = 0
def medir_puntaje(canvas:Canvas, elementos_canvas, finish_button:Button, tipo_de_juego:str):
    global accuracy
    global frase_escrita
    global turno
    global frase
    global time_start
    if len(finish_button.cget('text')) == 9:
        total = 0
        escrita = "".join(frase_escrita)
        for index in range(min(len(escrita), len(frase))):
            if frase[index] == escrita[index]:
                total += 1
        accuracy = (total / len(frase)) if (len(escrita) > 0) else 0
        canvas.itemconfig(elementos_canvas[0], text=("Escribiste:\n" + str(escrita) + "\nPrecision: " + str(accuracy*100) + "%"))
        if turno == 'Jugador 1':
            turno = 'Jugador 2'
            jugador1['puntaje'] = (accuracy / round(time.time() - time_start))
            finish_button.config(text = 'Empezar turno de Jugador 2')
            time_start = 0
        elif turno == 'Jugador 2':
            turno = 'Fin'
            jugador2['puntaje'] = (accuracy / round(time.time() - time_start))
            finish_button.config(text = 'Terminar ' \
            '')
            time_start = 0
        elif turno == 'Fin':
            finish_button.place_forget()
            time_start = 0
            if jugador1['puntaje'] > jugador2['puntaje']:
                ganador = "Jugador 1"
                puntaje_ganador = jugador1['puntaje']
                perdedor = "Jugador 2"
                puntaje_perdedor = jugador2['puntaje']
            elif jugador1['puntaje'] < jugador2['puntaje']:
                ganador = "Jugador 2"
                puntaje_ganador = jugador2['puntaje']
                perdedor = "Jugador 1"
                puntaje_perdedor = jugador1['puntaje']
            else:
                canvas.itemconfig(elementos_canvas[0],
                              text="Empate\n Puntaje: " + f"{jugador2['puntaje']:.2f}")
                return
            canvas.itemconfig(elementos_canvas[0],
                              text="Ganó: " + ganador + " Puntaje: " + f"{puntaje_ganador:.2f}" +
                              "\nPerdió: " + perdedor + " Puntaje: "+ f"{puntaje_perdedor:.2f}")
    else:
        frase = frases[randint(0,len(frases)-1)]
        frase_escrita = list()
        finish_button.config(text = 'Confirmar')
        if tipo_de_juego == 'simple':
            canvas.itemconfig(elementos_canvas[0],text=turno + " escribe: " + frase)
        time_start = time.time()
def escucha():
    printSerial(randint(0,len(frases)-1))
frase = ""
def screen_escucha(root, canvas):
    global frase_escrita
    global turno
    turno = "Jugador 1"
    widgets = list()
    elementos_canvas = list()
    elementos_canvas.append(canvas.create_text(
            root.winfo_width()//2,
            (root.winfo_height()*2//3),
            text= "Escucha y transmisión",
            font=("Benguiat",30),
            fill="#ffffff",
            anchor='center'
        ))
    finish_button =Button(root, text="Empezar turno de Jugador 1", font=("Benguiat",15))
    finish_button.config(command=lambda :medir_puntaje(canvas, elementos_canvas, finish_button,'escucha'))
    finish_button.place(x=(root.winfo_width()//2), y=((root.winfo_height()*2)//3)+100, anchor='center')
    widgets.append(finish_button)

    regresar =Button(root, text="Regresar", font=("Benguiat",15))
    widgets.append(regresar)
    regresar.config(command=lambda :switch_screen(root,canvas,screen_main, widgets, elementos_canvas))
    regresar.place(x=(root.winfo_width()*4//5), y=((root.winfo_height()*4)//5), anchor='center')
    
    Thread(target=printSerial, args=(['?'])).start()

def screen_simple(root, canvas):
    global frase_escrita
    global turno
    turno = "Jugador 1"
    widgets = list()
    elementos_canvas = list()
    elementos_canvas.append(canvas.create_text(
            root.winfo_width()//2,
            (root.winfo_height()*2//3),
            text= "Transmisión simple",
            font=("Benguiat",30),
            fill="#ffffff",
            anchor='center'
        ))
    finish_button =Button(root, text="Empezar turno de Jugador 1", font=("Benguiat",15))
    finish_button.config(command=lambda :medir_puntaje(canvas, elementos_canvas, finish_button, 'simple'))
    finish_button.place(x=(root.winfo_width()//2), y=((root.winfo_height()*2)//3)+100, anchor='center')
    widgets.append(finish_button)

    regresar =Button(root, text="Regresar", font=("Benguiat",15))
    widgets.append(regresar)
    regresar.config(command=lambda :switch_screen(root,canvas,screen_main, widgets, elementos_canvas))
    regresar.place(x=(root.winfo_width()*4//5), y=((root.winfo_height()*4)//5), anchor='center')
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
jugador1 = {'puntaje':-1}
jugador2 = {'puntaje':-1}
turno = 'Jugador 1'
screen_main(root, canvas)

root.mainloop()
#define punto 1
#define raya 2
#define blank 0
// BOOLEANOOOOS
#define True 1
#define False 0
#define max 6
#define button 13
#define clockPin1 6
#define clockPin2 7
#define datPin1 2
#define datPin2 3
int button_valor, reading = False, time_pressed = 0, time_NOT_pressed = 0;
long start, finish;
char morse;
/*time_pressed expresado en ms*/

//millis()
int index = 0, cadena[max];
void setup()
{
  Serial.begin(9600);
  pinMode(clockPin1, OUTPUT);
  pinMode(clockPin2, OUTPUT);
}
int compararCadenas(int otraCadena[])
{
  if(sizeof(otraCadena) != max)
  {
    return False;
  }
  for (int i = 0; i < max; i++)
  {
      if(otraCadena[i] != cadena[i])
      {
        return False;
      }
  }
  return True;
}
void convertirCadena()
{
  /*
  switch (cadena)
  case:
    morse = ''
  */
}
void rellenarCadena()
{
  for (int i = index; i < max; i++)
  {
    cadena[i] = blank;
  }
}
void dotOrDoot(long time)
{
  if (time <= 300)
  cadena[index] = punto;
  else
  cadena[index] = raya;
  index ++;
}
void deteccion(int button_valor)
{
if (button_valor == 1)
  {
    reading = True;
    start = millis();
  }
  else
  {
    if (start != 0)
    {
      finish = millis();
      dotOrDoot(finish - start);
      start = 0;
    }
    if(reading)
    {
      if(millis()-finish > 2000 && start == 0)
      {
        if (index < max)
        {
          rellenarCadena();
        }
        for (int i = 0; i < max; i++)
        {
          if (cadena[i] == punto)
          Serial.println("punto");
          else if (cadena[i] == raya)
          Serial.println("raya");
        }
        index = 0;
        finish = 0;
        convertirCadena();
        reading = False;
      }
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  button_valor = (digitalRead(button) == True) ? False : True;
  deteccion(button_valor);
}

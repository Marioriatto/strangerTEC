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

int a[max] = {punto,raya,blank,blank,blank,blank}, b[max] = {raya, punto, punto, punto, blank, blank},
c[max] = {raya, punto, raya, punto, blank, blank}, d[max] = {raya, punto, punto, blank, blank, blank},
e[max] = {punto, blank, blank, blank, blank, blank}, f[max] = {punto, punto, raya, punto, blank, blank},
g[max] = {raya, raya, punto, blank, blank, blank}, h[max] = {punto, punto, punto, punto, blank, blank},
ii[max] = {punto, punto, blank, blank, blank, blank}, j[max] = {punto, raya, raya, raya, blank, blank},
k[max] = {raya, punto, raya, blank, blank, blank}, l[max] = {punto, raya, punto, punto, blank, blank},
m[max] = {raya, raya, blank, blank, blank, blank}, n[max] = {raya, punto, blank, blank, blank, blank},
o[max] = {raya, raya, raya, blank, blank, blank}, p[max] = {punto, raya, raya, punto, blank, blank},
q[max] = {raya, raya, punto, raya, blank, blank}, r[max] = {punto, raya, punto, blank, blank, blank},
s[max] = {punto, punto, punto, blank, blank, blank}, t[max] = {raya, blank, blank, blank, blank, blank},
u[max] = {punto, punto, raya, blank, blank, blank}, v[max] = {punto, punto, punto, raya, blank, blank},
w[max] = {punto, raya, raya, blank, blank, blank}, x[max] = {raya, punto, punto, raya, blank, blank},
y[max] = {raya, punto, raya, raya, blank, blank}, z[max] = {raya, raya, punto, punto, blank, blank},
uno[max] = {punto, raya, raya, raya, raya, blank}, dos[max] = {punto, punto, raya, raya, raya, blank},
tres[max] = {punto, punto, punto, raya, raya, blank}, cuatro[max] = {punto, punto, punto, punto, raya, blank},
cinco[max] = {punto, punto, punto, punto, punto, blank}, seis[max] = {raya, punto, punto, punto, punto, blank},
siete[max] = {raya, raya, punto, punto, punto, blank}, ocho[max] = {raya, raya, raya, punto, punto, blank},
nueve[max] = {raya, raya, raya, raya, punto, blank}, cero[max] = {raya, raya, raya, raya, raya, blank},
mas[max] = {punto, raya, punto, raya, punto, blank}, menos[max] = {raya, punto, punto, punto, punto, raya};
   
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
  if (compararCadenas(a)) Serial.println('A');
  else if (compararCadenas(b))  Serial.println('B');
  else if (compararCadenas(c))  Serial.println('C');
  else if (compararCadenas(d))  Serial.println('D');
  else if (compararCadenas(e))  Serial.println('E');
  else if (compararCadenas(f))  Serial.println('F');
  else if (compararCadenas(g))  Serial.println('G');
  else if (compararCadenas(h))  Serial.println('H');
  else if (compararCadenas(ii)) Serial.println('I');
  else if (compararCadenas(j))  Serial.println('J');
  else if (compararCadenas(k))  Serial.println('K');
  else if (compararCadenas(l))  Serial.println('L');
  else if (compararCadenas(m))  Serial.println('M');
  else if (compararCadenas(n))  Serial.println('N');
  else if (compararCadenas(o))  Serial.println('O');
  else if (compararCadenas(p))  Serial.println('P');
  else if (compararCadenas(q))  Serial.println('Q');
  else if (compararCadenas(r))  Serial.println('R');
  else if (compararCadenas(s))  Serial.println('S');
  else if (compararCadenas(t))  Serial.println('T');
  else if (compararCadenas(u))  Serial.println('U');
  else if (compararCadenas(v))  Serial.println('V');
  else if (compararCadenas(w))  Serial.println('W');
  else if (compararCadenas(x))  Serial.println('X');
  else if (compararCadenas(y))  Serial.println('Y');
  else if (compararCadenas(z))  Serial.println('Z');
  else if (compararCadenas(uno))  Serial.println('1');
  else if (compararCadenas(dos))  Serial.println('2');
  else if (compararCadenas(tres)) Serial.println('3');
  else if (compararCadenas(cuatro)) Serial.println('4');
  else if (compararCadenas(cinco))  Serial.println('5');
  else if (compararCadenas(seis)) Serial.println('6');
  else if (compararCadenas(siete))  Serial.println('7');
  else if (compararCadenas(ocho)) Serial.println('8');
  else if (compararCadenas(nueve))  Serial.println('9');
  else if (compararCadenas(cero)) Serial.println('0');
  else if (compararCadenas(mas))  Serial.println('+');
  else if (compararCadenas(menos))  Serial.println('-');
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
  if (time < 100)return;
  if (time <= 400)
  {
    cadena[index] = punto;
  }
  else if(time > 400)
  {
    cadena[index] = raya;
  }
  index ++;
}
void deteccion(int button_valor)
{
if (button_valor == 1)
  {
    if (start == 0){start = millis();}
    reading = True;
  }
  else
  {
    if(reading)
    {
      if (start != 0)
      {
        dotOrDoot(millis() - start);
        finish = millis();
        start = 0;
      }
      if((millis()-finish) > 2000 && start == 0)
      {
        if (index < max)
        {
          rellenarCadena();
        }
        convertirCadena();
        index = 0;
        rellenarCadena();
        finish = 0;
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

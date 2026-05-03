// CODIGO MORSE
#define punto 1
#define raya 2
#define blank 0
// MODOS DE JUEGO
#define escucha 0
#define transmision 1

// BOOLEANOOOOS
#define True 1
#define False 0

#define max 6
#define button 13
#define clockPin1 6
#define clockPin2 7
#define dataPin1 2
#define dataPin2 3
#define row1 10
#define row2 11
#define row3 12

// VARIABLES DEL PROGRAMA
int button_valor, reading = False, modo_juego, time_pressed = 0, time_NOT_pressed = 0;
long start, finish;
char morse;
/*
time_pressed expresado en ms
contado con millis()
*/

// POSICIONES DE ABC EN LA MAQUETA
const int A[2] = {0,0}, B[2] = {1,0}, C[2] = {0,1},
D[2] = {1,1}, E[2] = {0,2}, F[2] = {1,2}, G[2] = {0,3},
H[2] = {1,3}, I[2] = {0,4}, J[2] = {1,4}, K[2] = {0,5},
L[2] = {1,5}, M[2] = {0,6}, N[2] = {1,6}, O[2] = {0,7},
P[2] = {1,7}, Q[2] = {0,8}, R[2] = {1,8}, S[2] = {0,9},
T[2] = {1,9}, U[2] = {0,10}, V[2] = {1,10}, W[2] = {0,11},
X[2] = {1,11}, Y[2] = {0,12}, Z[2] = {1,12}, CERO[2] = {2,0},
UNO[2] = {2,1}, DOS[2] = {2,2}, TRES[2] = {2,3}, CUATRO[2] = {2,4},
CINCO[2] = {2,5}, SEIS[2] = {2,6}, SIETE[2] = {2,7}, OCHO[2] = {2,8},
NUEVE[2] = {2,9}, MENOS[2] = {2,10}, MAS[2] = {2,11};

// VALOR MORSE DEL ABC
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
   
int index = 0, cadena[max];

void setup()
{
  Serial.begin(9600);
  pinMode(dataPin1, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(button, INPUT);
  printLED(20,20);
}

void printLED(int row, int col)
{
  shiftOut(dataPin1, clockPin1, LSBFIRST, 0b00000000);
  shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00000000);
  digitalWrite(row1, 0);
  digitalWrite(row2, 0);
  digitalWrite(row3, 0);
  // no quiero hacer un switch :v
  
  if (col == 12)
    shiftOut(dataPin1, clockPin1, LSBFIRST, 0b10000000);
  else if (col == 11)
    shiftOut(dataPin1, clockPin1, LSBFIRST, 0b01000000);
  else if (col == 10)
    shiftOut(dataPin1, clockPin1, LSBFIRST, 0b00100000);
  else if (col == 9)
    shiftOut(dataPin1, clockPin1, LSBFIRST, 0b00010000);
  else if (col == 8)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b10000000);
  else if (col == 7)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b01000000);
  else if (col == 6)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00100000);
  else if (col == 5)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00010000);
  else if (col == 4)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00001000);
  else if (col == 3)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00000100);
  else if (col == 2)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00000010);
  else if (col == 1)
    shiftOut(dataPin2, clockPin2, LSBFIRST, 0b00000001);
  else if (col == 0)
    shiftOut(dataPin1, clockPin1, LSBFIRST, 0b00001000);
  if (row == 2)
  {
    digitalWrite(row3, 1);
  }
  else if (row == 1)
  {
    digitalWrite(row2, 1);
  }
  else if (row == 0)
  {
    digitalWrite(row1, 1);
  }
}

/*
columna 12 bit 0bx0000000 shf1
columna 11 bit 0b0x000000 shf1
columna 10 bit 0b00x00000 shf1
columna 09 bit 0b000x0000 shf1
columna 08 bit 0bx0000000 shf2
columna 07 bit 0b0x000000 shf2
columna 06 bit 0b00x00000 shf2
columna 05 bit 0b000x0000 shf2
columna 04 bit 0b0000x000 shf2
columna 03 bit 0b00000x00 shf2
columna 02 bit 0b000000x0 shf2
columna 01 bit 0b0000000x shf2
columna 00 bit 0b0000x000 shf1
*/
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
  int row, col;              
  if (compararCadenas(a))       {row = A[0]; col = A[1];              Serial.println('A');}
  else if (compararCadenas(b))  {row = B[0]; col = B[1];              Serial.println('B');}
  else if (compararCadenas(c))  {row = C[0]; col = C[1];              Serial.println('C');}
  else if (compararCadenas(d))  {row = D[0]; col = D[1];              Serial.println('D');}
  else if (compararCadenas(e))  {row = E[0]; col = E[1];              Serial.println('E');}
  else if (compararCadenas(f))  {row = F[0]; col = F[1];              Serial.println('F');}
  else if (compararCadenas(g))  {row = G[0]; col = G[1];              Serial.println('G');}
  else if (compararCadenas(h))  {row = H[0]; col = H[1];              Serial.println('H');}
  else if (compararCadenas(ii)) {row = I[0]; col = I[1];              Serial.println('I');}
  else if (compararCadenas(j))  {row = J[0]; col = J[1];              Serial.println('J');}
  else if (compararCadenas(k))  {row = K[0]; col = K[1];              Serial.println('K');}
  else if (compararCadenas(l))  {row = L[0]; col = L[1];              Serial.println('L');}
  else if (compararCadenas(m))  {row = M[0]; col = M[1];              Serial.println('M');}
  else if (compararCadenas(n))  {row = N[0]; col = N[1];              Serial.println('N');}
  else if (compararCadenas(o))  {row = O[0]; col = O[1];              Serial.println('O');}
  else if (compararCadenas(p))  {row = P[0]; col = P[1];              Serial.println('P');}
  else if (compararCadenas(q))  {row = Q[0]; col = Q[1];              Serial.println('Q');}
  else if (compararCadenas(r))  {row = R[0]; col = R[1];              Serial.println('R');}
  else if (compararCadenas(s))  {row = S[0]; col = S[1];              Serial.println('S');}
  else if (compararCadenas(t))  {row = T[0]; col = T[1];              Serial.println('T');}
  else if (compararCadenas(u))  {row = U[0]; col = U[1];              Serial.println('U');}
  else if (compararCadenas(v))  {row = V[0]; col = V[1];              Serial.println('V');}
  else if (compararCadenas(w))  {row = W[0]; col = W[1];              Serial.println('W');}
  else if (compararCadenas(x))  {row = X[0]; col = X[1];              Serial.println('X');}
  else if (compararCadenas(y))  {row = Y[0]; col = Y[1];              Serial.println('Y');}
  else if (compararCadenas(z))  {row = Z[0]; col = Z[1];              Serial.println('Z');}
  else if (compararCadenas(uno))    {row = UNO[0];    col = UNO[1];   Serial.println('1');}
  else if (compararCadenas(dos))    {row = DOS[0];    col = DOS[1];   Serial.println('2');}
  else if (compararCadenas(tres))   {row = TRES[0];   col = TRES[1];  Serial.println('3');}
  else if (compararCadenas(cuatro)) {row = CUATRO[0]; col = CUATRO[1];Serial.println('4');}
  else if (compararCadenas(cinco))  {row = CINCO[0];  col = CINCO[1]; Serial.println('5');}
  else if (compararCadenas(seis))   {row = SEIS[0];   col = SEIS[1];  Serial.println('6');}
  else if (compararCadenas(siete))  {row = SIETE[0];  col = SIETE[1]; Serial.println('7');}
  else if (compararCadenas(ocho))   {row = OCHO[0];   col = OCHO[1];  Serial.println('8');}
  else if (compararCadenas(nueve))  {row = NUEVE[0];  col = NUEVE[1]; Serial.println('9');}
  else if (compararCadenas(cero))   {row = CERO[0];   col = CERO[1];  Serial.println('0');}
  else if (compararCadenas(mas))    {row = MAS[0];    col = MAS[1];   Serial.println('+');}
  else if (compararCadenas(menos))  {row = MENOS[0];  col = MENOS[1]; Serial.println('-');}
  printLED(row,col);
}
void rellenarCadena()
{
  for (int i = index; i < max; i++)
  {
    cadena[i] = blank;
  }
}
void formatearCadena()
{
  index = 0;
  rellenarCadena();
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
      if((millis()-finish) > 1500 && start == 0)
      {
        if (index < max)
        {
          rellenarCadena();
        }
        convertirCadena();
        formatearCadena();
        finish = 0;
        reading = False;
      }
    }
  }
}
void loop() {
  if (Serial.available() > 0) {
    // read the oldest byte in the buffer
    incomingByte = Serial.read();
    // necesito un caracter para comunicar el script tkinter con el arduino a traves del serial
    // ! por exclamar el mensaje en la maqueta y ? por adivinar el mensaje en la maqueta :v
    if ((char)incomingByte == '!') modo_juego = transmision;
    else if ((char)incomingByte == '?') modo_juego = escucha;
  }
  if (modo_juego == transmision) 
  {
    // leemos la transmision que mandan desde el boton
    button_valor = (digitalRead(button) == True) ? False : True;
    deteccion(button_valor);
  }

}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"progowanie.h"


/*E************************PROGOWANIE***********************************J*/
int progowanie(t_obraz *obraz,int liczba)
{
  int i,j;
  int prog;
  int (*pikselep)[obraz->wym_x];/*deklaracja zmiennej pomocnicznej by odnosic sie do tablicy dynamicznej*/
  pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
  if(liczba<=100 && liczba>=0)/*sprawdzanie poprawnosci wartosci progu wpisanej przez uzytkownika*/
  {
    prog=(liczba*obraz->odcieni)/100;/*obliczanie progu*/
    for (i=0;i<obraz->wym_y;i++) {/*progowanie*/
      for (j=0;j<obraz->wym_x;j++) {
    
        if(pikselep[i][j]<=prog)
        {
      	  pikselep[i][j]=0;
        }
        else
        {
      	  pikselep[i][j]=obraz->odcieni;
        }
    }
    
  }
  return 0;/*poprawna wartosc progu*/
  }
  return -1;/*nie poprawna warosc progu*/
  
}


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"negacja.h"

/*M************************NEGACJA**************************************I*/  
int negatyw(t_obraz *obraz)
{
  int i,j;
  int (*pikselep)[obraz->wym_x];/*deklaracja zmiennej pomocnicznej by odnosic sie do tablicy dynamicznej*/
  pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
  for (i=0;i<obraz->wym_y;i++) {/*negacja obrazu*/
    for (j=0;j<obraz->wym_x;j++) {
      pikselep[i][j]=obraz->odcieni-pikselep[i][j];
    }
  }
  return 0;
}



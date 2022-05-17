#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"zapisywanie.h"
int i,j;
/*L**************************ZAPISYWANIE************************************************O*/
int zapisz(t_opcje *opcje,t_obraz *obraz,int jaki) {

  int (*pikselep)[obraz->wym_x];/*deklaracja zmiennej pomocnicznej by odnosic sie do tablicy dynamicznej*/
  pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
  printf("\n-------------------------------------------------------------------\n");
  if(jaki==1)/*Dla obrazu PGM*/
  {
    fprintf(opcje->plik_wy,"P2 %d %d %d ",obraz->wym_x,obraz->wym_y,obraz->odcieni); //Zapisywanie numeru magicznego, wymiarow i maksymalnej szarosci
    for (i=0;i<obraz->wym_y;i++) {
      
      for (j=0;j<obraz->wym_x;j++) {
        //printf("%d ",pikselep[i][j]);
        
        fprintf(opcje->plik_wy,"%d ",pikselep[i][j]); //Zapisywanie wartosci szarosci pikseli 
        
      }
      fprintf(opcje->plik_wy,"\n");
  }
  }
  else/*Dla obrazu PPM*/
  {
    fprintf(opcje->plik_wy,"P3 %d %d %d ",(obraz->wym_x/3),obraz->wym_y,obraz->odcieni); //Zapisywanie numeru magicznego, wymiarow i maksymalnej szarosci
    for (i=0;i<obraz->wym_y;i++) {
      for (j=0;j<obraz->wym_x;j++) {
        fprintf(opcje->plik_wy,"%d ",pikselep[i][j]); //Zapisywanie wartosci szarosci pikseli 
      }
      fprintf(opcje->plik_wy,"\n");
  }
  }
  return 0;
}

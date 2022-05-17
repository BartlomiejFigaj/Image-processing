#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"odczytywanie.h"

#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
int i,j;
/*B*******************************ODCZYTYWANIE********************************************A*/
int czytaj(t_opcje *opcje,t_obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int jaki=0;
  
  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (opcje->plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(-1);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,opcje->plik_we)==NULL) /* Wczytanie pierwszej linii pliku do bufora */
  {
    koniec=1;                              /* Nie udalo sie? Koniec danych! */
  }
  if ( (buf[0]=='P') && (buf[1]=='2')) /* Czy jest magiczne "P2"? */
  {  
    jaki=1;//przypisujemy wartosci jaki 1
  }
  else if((buf[0]=='P') && (buf[1]=='3'))/* Czy jest magiczne "P3"? */
  {
    
    jaki=2;//przypisujemy warotsc jaki 2
  }
  else
  {
    return -1;
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(opcje->plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,opcje->plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,opcje->plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni*/
  if (fscanf(opcje->plik_we,"%d %d %d",&(obraz->wym_x),&(obraz->wym_y),&(obraz->odcieni))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /*W zaleznosci od rodzaju pliku rezerwujemy odpowiedna ilosc pamieci*/
  if(jaki==1)/*dla obrazu PGM*/
  {
    obraz->piksele=malloc(obraz->wym_x*obraz->wym_y*sizeof(int));//Rezerwowanie miejsca na tablice dynamiczna
    int (*pikselep)[obraz->wym_x];//Tworzenie zmiennej pomocniczej(łamanie zasady ansi 99)
    pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
    for (i=0;i<obraz->wym_y;i++) {
      for (j=0;j<obraz->wym_x;j++) {
        fscanf(opcje->plik_we,"%d",&(pikselep[i][j]));

    }
  }
  }
  else if(jaki==2)/*dla obrazu PPM*/
  {
    obraz->wym_x=obraz->wym_x*3;/*zwiekszamy wymiar poniewaz jest 3 razy wiecej liczb*/
    obraz->piksele=malloc(obraz->wym_x*obraz->wym_y*sizeof(int));//Rezerwowanie miejsca na tablice dynamiczna
    int (*pikselep)[obraz->wym_x];//Tworzenie zmiennej pomocniczej(łamanie zasady ansi 99)
    pikselep=(int(*)[obraz->wym_x]) obraz->piksele;
    for (i=0;i<(obraz->wym_y);i++) {
      for (j=0;j<(obraz->wym_x);j++) {
        fscanf(opcje->plik_we,"%d",&(pikselep[i][j]));

    }
  }
  }
  
  return jaki;   /* Czytanie zakonczone sukcesem    */
}                       


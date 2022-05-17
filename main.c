#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"wyswietlanie.h"
#include"odczytywanie.h"
#include"zapisywanie.h"
#include"negacja.h"
#include"progowanie.h"
#include"kont.h"
#include"konwesja.h"
#include"opcje.h"
#include"struktura.h"
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define B_BLADWCZYTANIA   -5
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
/****************************GLOWNA*FUNKCJA**********************************/
/********************************************************************/
/* COPYRIGHT (c) 2007-2021 KCiR                                     */
/********************************************************************/

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola dla opcji, ktore  */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne            */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor, t_obraz *obraz) {
  int i, prog;
  char *nazwa_pliku_we, *nazwa_pliku_wy,jaki;
  

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
    {
      return B_NIEPOPRAWNAOPCJA; 
    }
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	{
	  wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	}
	else                               /* otwieramy wskazany plik   */
	{
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
	  jaki=czytaj(wybor,obraz);//wczytywanie obrazu do pamieci (modul odczytywanie.c)
  	  if(jaki<1)
  	  {
  	    return B_BLADWCZYTANIA;
 	  }	
 	  }
        } 
	else
	{
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
	}
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	{
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
	  zapisz(wybor,obraz,jaki);//zapisywanie obrazu do pliku (modul zapisywanie.c)
	}
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowanie=1;
	  wybor->w_progu=prog;
	  printf("%d\n",prog); /*i progujemy*/
	  progowanie(obraz,prog);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }
    case 'n': {                 /* mamy wykonac negatyw */
      wybor->negatyw=1;
      negatyw(obraz);
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      wybor->konturowanie=1;
      kont(obraz,jaki);
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
      if(nazwa_pliku_wy!=NULL)
      {
        wyswietl(nazwa_pliku_wy);
      }
      break;
    }
    case 'm': {                 /* operacja konwersji */
      jaki=konwersja(wybor,obraz,jaki);
      break;
    }
    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  } /* koniec for */

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}


/*******************************************************/
/* Testowe wywołanie funkcji przetwarzaj_opcje         */
/* PRE:                                                */
/*      brak                                           */
/* POST:                                               */
/*      brak                                           */
/*******************************************************/

int main(int argc, char ** argv) {
  t_opcje opcje;
  t_obraz obraz;
  int kod_bledu;
  
  kod_bledu=przetwarzaj_opcje(argc,argv,&opcje,&obraz);
  

  if (kod_bledu)
    printf("Blad nr %d\n", kod_bledu);
  else
    printf("Opcje poprawne\n");

  return kod_bledu;
}


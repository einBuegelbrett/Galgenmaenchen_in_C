#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "listeWoerter.c"

int hauptspiel(FILE *, char *);
void ausgabeHangman(int);
char * wortRückgabe(char *, char, char[]);
char * buchstabenSpeicher(char, char[]);
int gewinnProbe(char[], int);
void endNachricht(int, FILE *, char *);
bool buchstabenKontrolle(char, char [], int);

// globale Variablen
int fehlerNummer = 0;
int versuch = 1;

int main()
{
    // Die Variablen fürs öffnen der Datei wird angelegt
    FILE * fp;
    char * datScores = "hangmanScore.txt";
    hauptspiel(fp, datScores);
    return 0;
}

int hauptspiel(FILE * fp, char * datScore) //Schnittpunkt von allem
{
    // öffnen der Datei
    fp = fopen(datScore, "a");

    // gibt eine Fehlernachricht zurück falls es einen Fehler beim öffnen der Datei gab
    if(fp == NULL)
    {
        fprintf(stderr,"Fehler beim öffnen der Datei %s\n", datScore);
        return EXIT_FAILURE;
    }

    char gerwortListe[26]; //Array für geratene Buchstaben
    
    char * wort = zufaelligesWort(); // wählt ein zufälliges Wort aus

    int laenge = strlen(wort);//länge des Wortes
    char ertwortListe[laenge];//Array mit erratenen Buchstaben

    // Füllt die Eratenenbuchstabenliste mit Unterstrichen voll 
    for(int i = 0; i < laenge; i++)
    {
        ertwortListe[i] = '_';
    }

    // Reserviert die Plätze (es behebt einen bug der beim printen der Liste manchmal andere Zeichen zeigt)
    for(int i = 0; i < 26; i++)
    {
        gerwortListe[i] = ' ';
    }

    // Zeilenumbruch zur besseren veranschaulischung
    printf("\n");
    
    // testet ob man gewonnen hat
    int gewonnen = gewinnProbe(ertwortListe, laenge);

    // Die Schleife in dem das Spiel passiert, bei 11 fehlern verliert man, wenn gewonnen gleich 1 ist gewinnt man
    while(fehlerNummer < 11 && gewonnen == 0)
    {
        // Buchstaben den der User eingibt
        char buchstabe;

        // Die Schleife printet das Spiel aus und fragt nach dem Buchstaben ab, falls er schon benutzt wurde, wird die Schleife wiederholt
        do
        {
            // printet die benötigten informationen aus
            printf("\n###########################################################\n");
            printf("\nVersuch %d\n", versuch);
            ausgabeHangman(fehlerNummer);

            // Gibt die Erateneliste aus
            for(int i = 0; i < strlen(wort); i++)
            {
                printf("%c", ertwortListe[i]);
            }

            printf("\n\n["); // Start der Liste (zur besseren veranschaulischung)

            // Gibt die Gerateneliste aus
            for(int i = 0; i < 26; i++)
            {
                printf("%c ", gerwortListe[i]);
            }

            printf("]\n\n"); // Ende der Liste

            // macht die Buchstabenanfrage
            printf("Gib einen Buchstaben an: ");
            scanf(" %c", &buchstabe);
        } while(buchstabenKontrolle(buchstabe, gerwortListe, laenge));

        //führt die verschiedene Proben aus
        wortRückgabe(wort, buchstabe, ertwortListe);
        buchstabenSpeicher(buchstabe, gerwortListe);
        gewonnen = gewinnProbe(ertwortListe, laenge);

        // Jeder Versuch wird in der globalen Variable gespeichert
        versuch++;
    }
    endNachricht(gewonnen, fp, wort);
    fclose(fp);
    }

//ausgabe des Galgenmänchens nach je Fehleranzahl
void ausgabeHangman(int versuchNummer)
{
    switch(versuchNummer) {
        case(0):printf(""); break; //Anfangswert
        case(1):printf("\n   _______\n _/       \\_\n\n");break;     /*1 print Hangman*/
        case(2):printf("\n      |\n      |\n      |\n   ___|___\n _/       \\_\n\n"); break;    /*2 print Hangman*/
        case(3):printf("\n      |/\n      |\n      |\n   ___|___\n _/       \\_\n\n"); break;     /*3 print Hangman*/
        case(4):printf("\n      _________\n      |/\n      |\n      |\n   ___|___\n _/       \\_\n\n"); break;    /*4 print Hangman*/
        case(5):printf("\n      _________\n      |/      |\n      |\n      |\n   ___|___\n _/       \\_\n\n"); break;     /*5 print Hangman*/
        case(6):printf("\n      _________\n      |/      |\n      |      ( )\n      |\n   ___|___\n _/       \\_\n\n"); break;    /*6 print Hangman*/
        case(7):printf("\n      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___\n _/       \\_\n\n"); break;    /*7 print Hangman*/
        case(8):printf("\n      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___     \\\n _/       \\_\n\n"); break;    /*8 print Hangman*/
        case(9):printf("\n      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___   / \\\n _/       \\_\n\n"); break;    /*9 print Hangman*/
        case(10):printf("\n      _________\n      |/      |\n      |      ( )\n      |       |\\\n   ___|___   / \\\n _/       \\_\n\n"); break;    /*10 print Hangman*/
        case(11):printf("\n      _________\n      |/      |\n      |      ( )\n      |      /|\\\n   ___|___   / \\\n _/       \\_\n\n"); break;    /*11 print Hangman*/
        default:printf("Fehler in der ausgabe Hangman Funktion");
    }
}

// Setzt den Buchstaben in die Erateneliste und gibt sie aus
char * wortRückgabe(char * wort, char buchstabe, char ertwortListe[]) //Kontrolle ob Buchstabe richtig oder nicht
{
    int laenge = strlen(wort);//länge des Wortes
    int gesetzteZahl = 0;

    for(int i = 0; i < laenge; i++) //gibt die eratenen Buchstaben oder Unterstriche aus
    {
        char c = wort[i];
       
        if (c == buchstabe) {
            ertwortListe[i] = buchstabe;
            gesetzteZahl++;
        }
    }

    if(gesetzteZahl == 0)
    {
        fehlerNummer++;
    }

    for(int j = 0; j < laenge; j++)
    {
      printf("%c",ertwortListe[j]);
    }
    printf("\n");
    return ertwortListe;
}

// speichert die Geratenenbuchstaben im Array
char * buchstabenSpeicher(char buchstabe, char gerwortListe[])
{
    gerwortListe[versuch - 1] = buchstabe;
    return gerwortListe;
}

// testet ob der User gewonnen hat
int gewinnProbe(char liste[],int laenge)
{
    for(int i = 0; i < laenge; i++)
    {
        if(liste[i] == '_')
        {
            return 0;
        }
    }
    return 1;
}

// Gibt die Endnachricht aus ob man gewonnen oder verloren hat
void endNachricht(int ergebnis, FILE * fp, char * wort)
{
    if(ergebnis == 1)
    {
        printf("Sie haben gewonnen !");
    }
    else
    {
        ausgabeHangman(fehlerNummer);
        printf("Sie haben verloren.\nDas Wort war: %s\n", wort); // Zeigt das Wort an wenn man verloren hat
    }
    //hängt an die Datei wie viele Versuche man für ein Wort gebraucht hat
    fprintf(fp, "Versuche: %d ; Wort: %s\n", versuch, wort);
}

// kontrolliert ob der eingegebene Buchstabe schon benutzt wurde
bool buchstabenKontrolle(char buchstabe, char Liste[],int laenge)
{
    for(int i = 0; i < laenge; i++)
    {
        if(buchstabe == Liste[i])
        {
            return true;
        }
    }
    return false;
}
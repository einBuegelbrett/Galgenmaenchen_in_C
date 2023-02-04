#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int hauptspiel();
void ausgabeHangman(int);
char * zufaelligesWort(char *[]);
char * woerterliste[];
char * wortRückgabe(char *, char, char[]);
char * buchstabenSpeicher(char, int, char []);
int gewinnProbe(char[], int);
void endNachricht(int);
bool buchstabenKontrolle(char, char [], int );

int fehlerNummer = 0;

int main()
{
  hauptspiel();
  return 0;
}

int hauptspiel() //Schnittpunkt von allem
{

  char gerwortListe[11]; //Array für geratene Buchstaben

  char * wort = zufaelligesWort(woerterliste);
  printf(wort);                                         //Kommt weg

    int laenge = strlen(wort);//länge des Wortes

    char ertwortListe[laenge];//Array mit erratenen Buchstaben
    for(int i = 0; i < laenge; i++)
    {
        ertwortListe[i] = '_';
    }
    printf("\n");
    printf(ertwortListe);
    // wenn gewonnen gleich 1 ist, hat man gewonnen
    int gewonnen = gewinnProbe(ertwortListe, laenge);
  while(fehlerNummer < 11 && gewonnen == 0)
  {
     // printf("%d", fehlerNummer);
      //printf("\n"); //nur zum formatieren der Ausgabe
    // den Buchstaben den der User eingibt
    char buchstabe;
    do
    {
        printf("Gib ein Buchstaben an: ");
        scanf(" %c", &buchstabe);
    }
            while(buchstabenKontrolle(buchstabe, gerwortListe, laenge));

      wortRückgabe(wort, buchstabe,ertwortListe);
      buchstabenSpeicher(buchstabe, fehlerNummer, gerwortListe);
    ausgabeHangman(fehlerNummer);
    gewonnen = gewinnProbe(ertwortListe, laenge);
  }
    endNachricht(gewonnen);
}

//ausgabe des Galgenmänchens nach je Fehleranzahl
void ausgabeHangman(int versuchNummer)
{
    switch(versuchNummer) {
        case(0):printf(""); break; //default Wert
        case(1):printf("   _______\n _/       \\_\n");break;     /*1 print Hangman*/
        case(2):printf("      |\n      |\n      |\n   ___|___\n _/       \\_\n"); break;    /*2 print Hangman*/
        case(3):printf("      |/\n      |\n      |\n   ___|___\n _/       \\_\n"); break;     /*3 print Hangman*/
        case(4):printf("      _________\n      |/\n      |\n      |\n   ___|___\n _/       \\_\n"); break;    /*4 print Hangman*/
        case(5):printf("      _________\n      |/      |\n      |\n      |\n   ___|___\n _/       \\_\n"); break;     /*5 print Hangman*/
        case(6):printf("      _________\n      |/      |\n      |      ( )\n      |\n   ___|___\n _/       \\_\n"); break;    /*6 print Hangman*/
        case(7):printf("      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___\n _/       \\_\n"); break;    /*7 print Hangman*/
        case(8):printf("      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___     \\\n _/       \\_\n"); break;    /*8 print Hangman*/
        case(10):printf("      _________\n      |/      |\n      |      ( )\n      |       |\\\n   ___|___   / \\\n _/       \\_\n"); break;    /*10 print Hangman*/
        case(11):printf("      _________\n      |/      |\n      |      ( )\n      |      /|\\\n   ___|___   / \\\n _/       \\_\n"); break;    /*11 print Hangman*/
        default:printf("Fehler in der ausgabeHangman Funktion");
    }
}

// gibt ein zufälliges Wort zurück
char * zufaelligesWort(char *liste[])
{
  srand(time(0));
  int nummer = rand() % 656;

  return woerterliste[nummer];
}

char *wortRückgabe(char * wort, char buchstabe, char ertwortListe[]) //Kontrolle ob Buchstabe richtig oder nicht
{
    int laenge = strlen(wort);//länge des Wortes
    int gesetzteZahl = 0;

    for(int i = 0; i <= laenge - 1; i++) //gibt die Striche und Buchstaben aus
    {
        char c = wort[i];


        if (c == buchstabe) {
            //printf("%s",&buchstabe);
            ertwortListe[i] = buchstabe;
            gesetzteZahl++;

        }

    }
    printf("%d\n",gesetzteZahl);

    if(gesetzteZahl == 0)
    {
        fehlerNummer++;
    }
    for(int j = 0; j < laenge; j++)
    {
        printf("%c",ertwortListe[j] );
    }
    printf("\n");
    return ertwortListe;

}

char * buchstabenSpeicher(char buchstabe, int fehlerNummer, char gerwortListe[])
{
    gerwortListe[fehlerNummer] = buchstabe;
    //printf(gerwortListe);
    return gerwortListe;
}
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
void endNachricht(int ergebnis)
{
    if(ergebnis == 1)
    {
        printf("Sie haben gewonnen");
    }
    else
    {
        printf("Sie haben verloren");
    }
}

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


char *woerterliste[] = {"Ärger", 
"Ärztin",
"Abend",
"Abfahrt",
"Abflug",
"Absender",
"Adresse",
"Alkohol",
"Alter",
"Ampel",
"Anfang",
"Angebot",
"Angestellte",
"Angst",
"Ankunft",
"Anmeldung",
"Anrede",
"Anruf",
"Anrufbeantworter",
"Ansage",
"Anschluss",
"Antwort",
"Anzeige",
"Anzug",
"Apfel",
"Apotheke",
"Appartement",
"Appetit",
"April",
"Arbeit",
"Arbeitsplatz",
"Arm",
"Arzt",
"Aufenthalt",
"Aufgabe",
"Aufzug",
"Auge",
"August",
"Ausbildung",
"Ausflug",
"Ausgang",
"Auskunft",
"Ausländer",
"Ausländerin",
"Ausland",
"Aussage",
"Ausstellung",
"Ausweis",
"Auto",
"Autobahn",
"Automat",
"Bäckerei",
"Büro",
"Baby",
"Bad",
"Bahn",
"Bahnhof",
"Bahnsteig",
"Balkon",
"Banane",
"Bank",
"Batterie",
"Baum",
"Beamte",
"Beamtin",
"Bein",
"Beispiel",
"Bekannte",
"Benzin",
"Beratung",
"Berg",
"Beruf",
"Berufsschule",
"Besuch",
"Betrag",
"Bett",
"Bewerbung",
"Bier",
"Bild",
"Bildschirm",
"Birne",
"Bitte",
"Blatt",
"Bleistift",
"Blick",
"Blume",
"Bluse",
"Blut",
"Bogen",
"Bohne",
"Brötchen",
"Brücke",
"Brief",
"Briefkasten",
"Briefmarke",
"Brieftasche",
"Briefumschlag",
"Brille",
"Brot",
"Bruder",
"Buch",
"Buchstabe",
"Bus",
"Butter",
"Café",
"CD",
"CD-ROM",
"Chef",
"Computer",
"Creme",
"Dach",
"Dame",
"Dank",
"Datum",
"Dauer",
"Deutsche",
"Dezember",
"Dienstag",
"Ding",
"Disco",
"Doktor",
"Dom",
"Donnerstag",
"Doppelzimmer",
"Dorf",
"Drucker",
"Durchsage",
"Durst",
"Dusche",
"E-Mail",
"Ecke",
"Ehefrau",
"Ehemann",
"Ei",
"Einführung",
"Eingang",
"Einladung",
"Eintritt",
"Einwohner",
"Einzelzimmer",
"Eis",
"Eltern",
"Empfänger",
"Empfang",
"Ende",
"Enkel",
"Entschuldigung",
"Erdgeschoss",
"Erfahrung",
"Ergebnis",
"Erlaubnis",
"Ermäßigung",
"Erwachsene",
"Essen",
"Export",
"Fähre",
"Führerschein",
"Führung",
"Fabrik",
"Fahrer",
"Fahrkarte",
"Fahrplan",
"Fahrrad",
"Familie",
"Familienname",
"Familienstand",
"Farbe",
"Fax",
"Februar",
"Fehler",
"Fenster",
"Ferien",
"Fernsehgerät",
"Fest",
"Feuer",
"Feuerwehr",
"Feuerzeug",
"Fieber",
"Film",
"Firma",
"Fisch",
"Flasche",
"Fleisch",
"Flughafen",
"Flugzeug",
"Flur",
"Fluss",
"Formular",
"Foto",
"Fotoapparat",
"Frühjahr",
"Frühling",
"Frühstück",
"Frage",
"Frau",
"Freitag",
"Freizeit",
"Freund",
"Freundin",
"Friseur",
"Frist",
"Fuß",
"Fußball",
"Fundbüro",
"Gabel",
"Garage",
"Garten",
"Gas",
"Gast",
"Gebühr",
"Geburtsjahr",
"Geburtsort",
"Geburtstag",
"Gegenteil",
"Geld",
"Geldbörse",
"Gemüse",
"Gepäck",
"Gericht",
"Gesamtschule",
"Geschäft",
"Geschenk",
"Geschirr",
"Geschwister",
"Gesicht",
"Gespräch",
"Gesundheit",
"Getränk",
"Gewicht",
"Gewitter",
"Glück",
"Glückwunsch",
"Glas",
"Gleis",
"Goethe-Institut",
"Größe",
"Die Grenze",
"Grippe",
"Großeltern",
"Großmutter",
"Großvater",
"Gruß",
"Grundschule",
"Gruppe",
"Guthaben",
"Gymnasium",
"Hähnchen",
"Haar",
"Halbpension",
"Halle",
"Hals",
"Haltestelle",
"Hand",
"Handtuch",
"Handy",
"Haus",
"Hausaufgabe",
"Hausfrau",
"Haushalt",
"Hausmann",
"Heimat",
"Heizung",
"Hemd",
"Herbst",
"Herd",
"Herr",
"Herz",
"Hilfe",
"Hobby",
"Holz",
"Hose",
"Hund",
"Hunger",
"Idee",
"Import",
"Industrie",
"Information",
"Inhalt",
"Internet",
"Jacke",
"Jahr",
"Januar",
"Job",
"Jugendherberge",
"Jugendliche",
"Juli",
"Junge",
"Juni",
"Käse",
"Körper",
"Küche",
"Kühlschrank",
"Kündigung",
"Kaffee",
"Kalender",
"Kamera",
"Kanne",
"Karte",
"Kartoffel",
"Kasse",
"Kassette",
"Kassettenrecorder",
"Katze",
"Keller",
"Kellner",
"Kenntnisse",
"Kennzeichen",
"Kette",
"Kfz",
"Kind",
"Kindergarten",
"Kinderwagen",
"Kino",
"Kiosk",
"Kirche",
"Klasse",
"Kleid",
"Kleidung",
"Kneipe",
"Koffer",
"Kollege",
"Kollegin",
"Konsulat",
"Kontakt",
"Konto",
"Kontrolle",
"Konzert",
"Kopf",
"Kosmetik",
"Krankenkasse",
"Krankheit",
"Kredit",
"Kreditkarte",
"Kreis",
"Kreuzung",
"Kuchen",
"Kugelschreiber",
"Kunde",
"Kundin",
"Kurs",
"Löffel",
"Lösung",
"Laden",
"Lager",
"Lampe",
"Land",
"Landschaft",
"Leben",
"Lebensmittel",
"Leid",
"Lehre",
"Lehrer",
"Lehrerin",
"Leute",
"Licht",
"Lied",
"Lkw",
"Loch",
"Lohn",
"Lokal",
"Luft",
"Lust",
"Mädchen",
"März",
"Möbel",
"Müll",
"Mülltonne",
"Magen",
"Mai",
"Mal",
"Mann",
"Mantel",
"Markt",
"Maschine",
"Material",
"Mechaniker",
"Medikament",
"Meer",
"Mehrwertsteuer",
"Meinung",
"Menge",
"Mensch",
"Messer",
"Metall",
"Miete",
"Milch",
"Minute",
"Mittag",
"Mitte",
"Mitteilung",
"Mittel",
"Mittelschule",
"Mittwoch",
"Mode",
"Moment",
"Monat",
"Montag",
"Morgen",
"Motor",
"Mund",
"Museum",
"Musik",
"Mutter",
"Nähe",
"Nachbar",
"Nachbarin",
"Nachmittag",
"Nachrichten",
"Nacht",
"Name",
"Natur",
"Nebel",
"Norden",
"Notarzt",
"Note",
"Notfall",
"Notiz",
"November",
"Nudel",
"Nummer",
"Ober",
"Obst",
"Oktober",
"Oma",
"Opa",
"Operation",
"Orange",
"Ordnung",
"Ort",
"Osten",
"Öl",
"Päckchen",
"Paket",
"Panne",
"Papier",
"Papiere",
"Parfüm",
"Park",
"Partei",
"Partner",
"Partnerin",
"Party",
"Pass",
"Pause",
"Pension",
"Pkw",
"Plan",
"Plastik",
"Platz",
"Polizei",
"Portion",
"Post",
"Postleitzahl",
"Prüfung",
"Praktikum",
"Praxis",
"Preis",
"Problem",
"Das Produkt",
"Programm",
"Prospekt",
"Pullover",
"Qualität",
"Quittung",
"Rücken",
"Rabatt",
"Radio",
"Rathaus",
"Raucher",
"Raucherin",
"Raum",
"Realschule",
"Rechnung",
"Regen",
"Reifen",
"Reinigung",
"Reis",
"Reise",
"Reisebüro",
"Reiseführer",
"Reparatur",
"Restaurant",
"Rezept",
"Rezeption",
"Rind",
"Rock",
"Rose",
"Rundgang",
"Süden",
"S-Bahn",
"Sache",
"Saft",
"Salat",
"Salz",
"Satz",
"Schüler",
"Schülerin",
"Schalter",
"Scheckkarte",
"Schiff",
"Schild",
"Schinken",
"Schirm",
"Schlüssel",
"Schloss",
"Schluss",
"Schmerzen",
"Schnee",
"Schnupfen",
"Schokolade",
"Schrank",
"Schuh",
"Schule",
"Schwein",
"Schwester",
"Schwimmbad",
"See",
"Sehenswürdigkeit",
"Seife",
"Sekretärin",
"Sekunde",
"Sendung",
"Senioren",
"September",
"Service",
"Sessel",
"Sofa",
"Sohn",
"Sommer",
"Sonderangebot",
"Sonne",
"Sonntag",
"Sorge",
"Spülmaschine",
"Spaß",
"Spaziergang",
"Speisekarte",
"Spielplatz",
"Sprache",
"Sprachschule",
"Sprechstunde",
"Stück",
"Stadt",
"Standesamt",
"Stempel",
"Steuer",
"Stock",
"Stoff",
"Straße",
"Straßenbahn",
"Strand",
"Streichholz",
"Strom",
"Student",
"Studentin",
"Studium",
"Stuhl",
"Stunde",
"Supermarkt",
"Suppe",
"Tür",
"Tüte",
"Tag",
"Tankstelle",
"Tasche",
"Tasse",
"Taxi",
"Der Tee",
"Teil",
"Telefon",
"Telefonbuch",
"Teller",
"Teppich",
"Termin",
"Test",
"Text",
"Theater",
"Thema",
"Ticket",
"Tier",
"Tipp",
"Tisch",
"Tochter",
"Toilette",
"Tomate",
"Topf",
"Tourist",
"Treppe",
"Trinkgeld",
"Turm",
"U-Bahn",
"Uhr",
"Unfall",
"Universität",
"Unterhaltung",
"Unterkunft",
"Unterricht",
"Unterschied",
"Unterschrift",
"Untersuchung",
"Urlaub",
"Übernachtung",
"Vater",
"Verbindung",
"Verein",
"Verkäufer",
"Verkäuferin",
"Verkehr",
"Vermieter",
"Versicherung",
"Verspätung",
"Vertrag",
"Video",
"Vogel",
"Volksschule",
"Vormittag",
"Vorname",
"Vorsicht",
"Vorwahl",
"Wäsche",
"Wagen",
"Wald",
"Wasser",
"Weg",
"Wein",
"Welt",
"Werkstatt",
"Werkzeug",
"Westen",
"Wetter",
"Wiederhören",
"Wiedersehen",
"Wind",
"Winter",
"Wirtschaft",
"Woche",
"Wochenende",
"Wochentag",
"Wohnung",
"Wolke",
"Wort",
"Wunsch",
"Wurst",
"Zahl",
"Zahn",
"Zeit",
"Zeitschrift",
"Zeitung",
"Zentrum",
"Zettel",
"Zeugnis",
"Zigarette",
"Zimmer",
"Zitrone",
"Zoll",
"Zucker",
"Zug"};
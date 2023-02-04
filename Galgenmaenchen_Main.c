#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int hauptspiel(FILE *, char *);
void ausgabeHangman(int);
char * zufaelligesWort(char *[]);
char * woerterliste[];
char * wortRückgabe(char *, char, char[]);
char * buchstabenSpeicher(char, char[]);
int gewinnProbe(char[], int);
void endNachricht(int, FILE *, char *);
bool buchstabenKontrolle(char, char [], int);

int fehlerNummer = 0;

int versuch = 1;

int main()
{
    FILE * fp;
    char * datScores = "HangmanScore.txt";

    hauptspiel(fp, datScores);
    return 0;
}

int hauptspiel(FILE * fp, char * datScore) //Schnittpunkt von allem
{
    fp = fopen(datScore, "a");
    if(fp == NULL)
    {
        fprintf(stderr,"Fehler beim öffnen der Datei %s\n", datScore);
        return EXIT_FAILURE;
    }

    char gerwortListe[26]; //Array für geratene Buchstaben

    char * wort = zufaelligesWort(woerterliste);
    //printf(wort);

    int laenge = strlen(wort);//länge des Wortes
    char ertwortListe[laenge];//Array mit erratenen Buchstaben

    for(int i = 0; i < laenge; i++)
    {
        ertwortListe[i] = '_';
    }

    for(int i = 0; i < 26; i++)
    {
        gerwortListe[i] = ' ';
    }

    printf("\n");
    
    // wenn gewonnen gleich 1 ist, hat man gewonnen
    int gewonnen = gewinnProbe(ertwortListe, laenge);

  while(fehlerNummer < 11 && gewonnen == 0)
  {
    // den Buchstaben den der User eingibt
    char buchstabe;
    do
    {
        printf("\n###########################################################\n");
        printf("\nVersuch %d\n", versuch);
        ausgabeHangman(fehlerNummer);
        for(int i = 0; i < strlen(wort); i++)
        {
            printf("%c", ertwortListe[i]);
        }

        printf("\n\n[");

        for(int i = 0; i < 26; i++)
        {
            printf("%c ", gerwortListe[i]);
        }

        printf("]\n\n");

        printf("Gib einen Buchstaben an: ");
        scanf(" %c", &buchstabe);
    } while(buchstabenKontrolle(buchstabe, gerwortListe, laenge));

    wortRückgabe(wort, buchstabe, ertwortListe);
    buchstabenSpeicher(buchstabe, gerwortListe);
    gewonnen = gewinnProbe(ertwortListe, laenge);
    versuch++;
  }
  endNachricht(gewonnen, fp, wort);
  fclose(fp);
}

//ausgabe des Galgenmänchens nach je Fehleranzahl
void ausgabeHangman(int versuchNummer)
{
    switch(versuchNummer) {
        case(0):printf(""); break; //default Wert
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

// gibt ein zufälliges Wort zurück
char * zufaelligesWort(char *liste[])
{
  srand(time(0));
  int nummer = rand() % 648;

  return woerterliste[nummer];
}

char * wortRückgabe(char * wort, char buchstabe, char ertwortListe[]) //Kontrolle ob Buchstabe richtig oder nicht
{
    int laenge = strlen(wort);//länge des Wortes
    int gesetzteZahl = 0;

    for(int i = 0; i < laenge; i++) //gibt die Striche und Buchstaben aus
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

char * buchstabenSpeicher(char buchstabe, char gerwortListe[])
{
    gerwortListe[versuch - 1] = buchstabe;
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

void endNachricht(int ergebnis, FILE * fp, char * wort)
{
    if(ergebnis == 1)
    {
        printf("Sie haben gewonnen !");
    }
    else
    {
        ausgabeHangman(fehlerNummer);
        printf("Sie haben verloren.\nDas Wort war: %s\n", wort);
    }
    fprintf(fp, "Versuche: %d ; Wort: %s\n", versuch, wort);
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

char *woerterliste[] = {"aerger", 
"aerztin",
"abend",
"abfahrt",
"abflug",
"absender",
"adresse",
"alkohol",
"alter",
"ampel",
"anfang",
"angebot",
"angestellte",
"angst",
"ankunft",
"anmeldung",
"anrede",
"anruf",
"anrufbeantworter",
"ansage",
"anschluss",
"antwort",
"anzeige",
"anzug",
"apfel",
"apotheke",
"appartement",
"appetit",
"april",
"arbeit",
"arbeitsplatz",
"arm",
"arzt",
"aufenthalt",
"aufgabe",
"aufzug",
"auge",
"august",
"ausbildung",
"ausflug",
"ausgang",
"auskunft",
"auslaender",
"auslaenderin",
"ausland",
"aussage",
"ausstellung",
"ausweis",
"auto",
"autobahn",
"automat",
"baeckerei",
"buero",
"baby",
"bad",
"bahn",
"bahnhof",
"bahnsteig",
"balkon",
"banane",
"bank",
"batterie",
"baum",
"beamte",
"beamtin",
"bein",
"beispiel",
"bekannte",
"benzin",
"beratung",
"berg",
"beruf",
"berufsschule",
"besuch",
"betrag",
"bett",
"bewerbung",
"bier",
"bild",
"bildschirm",
"birne",
"bitte",
"blatt",
"bleistift",
"blick",
"blume",
"bluse",
"blut",
"bogen",
"bohne",
"broetchen",
"bruecke",
"brief",
"briefkasten",
"briefmarke",
"brieftasche",
"briefumschlag",
"brille",
"brot",
"bruder",
"buch",
"buchstabe",
"bus",
"butter",
"chef",
"computer",
"creme",
"dach",
"dame",
"dank",
"datum",
"dauer",
"deutsche",
"dezember",
"dienstag",
"ding",
"disco",
"doktor",
"dom",
"donnerstag",
"doppelzimmer",
"dorf",
"drucker",
"durchsage",
"durst",
"dusche",
"ecke",
"ehefrau",
"ehemann",
"ei",
"einführung",
"eingang",
"einladung",
"eintritt",
"einwohner",
"einzelzimmer",
"eis",
"eltern",
"empfaenger",
"empfang",
"ende",
"enkel",
"entschuldigung",
"erdgeschoss",
"erfahrung",
"ergebnis",
"erlaubnis",
"ermaeßigung",
"erwachsene",
"essen",
"export",
"faehre",
"fuehrerschein",
"fuehrung",
"fabrik",
"fahrer",
"fahrkarte",
"fahrplan",
"fahrrad",
"familie",
"familienname",
"familienstand",
"farbe",
"fax",
"februar",
"fehler",
"fenster",
"ferien",
"fernsehgeraet",
"fest",
"feuer",
"feuerwehr",
"feuerzeug",
"fieber",
"film",
"firma",
"fisch",
"flasche",
"fleisch",
"flughafen",
"flugzeug",
"flur",
"fluss",
"formular",
"foto",
"fotoapparat",
"fruehjahr",
"fruehling",
"fruehstueck",
"frage",
"frau",
"freitag",
"freizeit",
"freund",
"freundin",
"friseur",
"frist",
"fuss",
"fussball",
"fundbuero",
"gabel",
"garage",
"garten",
"gas",
"gast",
"gebuehr",
"geburtsjahr",
"geburtsort",
"geburtstag",
"gegenteil",
"geld",
"geldboerse",
"gemuese",
"gepaeck",
"gericht",
"gesamtschule",
"geschaeft",
"geschenk",
"geschirr",
"geschwister",
"gesicht",
"gespraech",
"gesundheit",
"getraenk",
"gewicht",
"gewitter",
"glueck",
"glueckwunsch",
"glas",
"gleis",
"groeße",
"grenze",
"grippe",
"großeltern",
"großmutter",
"großvater",
"gruß",
"grundschule",
"gruppe",
"guthaben",
"gymnasium",
"haehnchen",
"haar",
"halbpension",
"halle",
"hals",
"haltestelle",
"hand"
"handtuch",
"handy",
"haus",
"hausaufgabe",
"hausfrau",
"haushalt",
"hausmann",
"heimat",
"heizung",
"hemd",
"herbst",
"herd",
"herr",
"herz",
"hilfe",
"hobby",
"holz",
"hose",
"hund",
"hunger",
"idee",
"import",
"industrie",
"information",
"inhalt",
"internet",
"jacke",
"jahr",
"januar",
"job",
"jugendherberge",
"jugendliche",
"juli",
"junge",
"juni",
"kaese",
"koerper",
"kueche",
"kuehlschrank",
"kuendigung",
"kaffee",
"kalender",
"kamera",
"kanne",
"karte",
"kartoffel",
"kasse",
"kassette",
"kassettenrecorder",
"katze",
"keller",
"kellner",
"kenntnisse",
"kennzeichen",
"kette",
"kfz",
"kind",
"kindergarten",
"kinderwagen",
"kino",
"kiosk",
"kirche",
"klasse",
"kleid",
"kleidung",
"kneipe",
"koffer",
"kollege",
"kollegin",
"konsulat",
"kontakt",
"konto",
"kontrolle",
"konzert",
"kopf",
"kosmetik",
"krankenkasse",
"krankheit",
"kredit",
"kreditkarte",
"kreis",
"kreuzung",
"kuchen",
"kugelschreiber",
"kunde",
"kundin",
"kurs",
"loeffel",
"loesung",
"laden",
"lager",
"lampe",
"land",
"landschaft",
"leben",
"lebensmittel",
"leid",
"lehre",
"lehrer",
"lehrerin",
"leute",
"licht",
"lied",
"lkw",
"loch",
"lohn",
"lokal",
"luft",
"lust",
"maedchen",
"maerz",
"moebel",
"muell",
"muelltonne",
"magen",
"mai",
"mal",
"mann",
"mantel",
"markt",
"maschine",
"material",
"mechaniker",
"medikament",
"meer",
"mehrwertsteuer",
"meinung",
"menge",
"mensch",
"messer",
"metall",
"miete",
"milch",
"minute",
"mittag",
"mitte",
"mitteilung",
"mittel",
"mittelschule",
"mittwoch",
"mode",
"moment",
"monat",
"montag",
"morgen",
"motor",
"mund",
"museum",
"musik",
"mutter",
"naehe",
"nachbar",
"nachbarin",
"nachmittag",
"nachrichten",
"nacht",
"name",
"natur",
"nebel",
"norden",
"notarzt",
"note",
"notfall",
"notiz",
"november",
"nudel",
"nummer",
"ober",
"obst",
"oktober",
"oma",
"opa",
"operation",
"orange",
"ordnung",
"ort",
"osten",
"oel",
"paeckchen",
"paket",
"panne",
"papier",
"papiere",
"parfuem",
"park",
"partei",
"partner",
"partnerin",
"party",
"pass",
"pause",
"pension",
"pkw",
"plan",
"plastik",
"platz",
"polizei",
"portion",
"post",
"postleitzahl",
"pruefung",
"praktikum",
"praxis",
"preis",
"problem",
"produkt",
"programm",
"prospekt",
"pullover",
"qualitaet",
"quittung",
"ruecken",
"rabatt",
"radio",
"rathaus",
"raucher",
"raucherin",
"raum",
"realschule",
"rechnung",
"regen",
"reifen",
"reinigung",
"reis",
"reise",
"reisebuero",
"reisefuehrer",
"reparatur",
"restaurant",
"rezept",
"rezeption",
"rind",
"rock",
"rose",
"rundgang",
"sueden",
"sache",
"saft",
"salat",
"salz",
"satz",
"schueler",
"schuelerin",
"schalter",
"scheckkarte",
"schiff",
"schild",
"schinken",
"schirm",
"schluessel",
"schloss",
"schluss",
"schmerzen",
"schnee",
"schnupfen",
"schokolade",
"schrank",
"schuh",
"schule",
"schwein",
"schwester",
"schwimmbad",
"see",
"sehenswuerdigkeit",
"seife",
"sekretaerin",
"sekunde",
"sendung",
"senioren",
"september",
"service",
"sessel",
"sofa",
"sohn",
"sommer",
"sonderangebot",
"sonne",
"sonntag",
"sorge",
"spuelmaschine",
"spaß",
"spaziergang",
"speisekarte",
"spielplatz",
"sprache",
"sprachschule",
"sprechstunde",
"stueck",
"stadt",
"standesamt",
"stempel",
"steuer",
"stock",
"stoff",
"straße",
"straßenbahn",
"strand",
"streichholz",
"strom",
"student",
"studentin",
"studium",
"stuhl",
"stunde",
"supermarkt",
"suppe",
"tuer",
"tuete",
"tag",
"tankstelle",
"tasche",
"tasse",
"taxi",
"teil",
"telefon",
"telefonbuch",
"teller",
"teppich",
"termin",
"test",
"text",
"theater",
"thema",
"ticket",
"tier",
"tipp",
"tisch",
"tochter",
"toilette",
"tomate",
"topf",
"tourist",
"treppe",
"trinkgeld",
"turm",
"uhr",
"unfall",
"universitaet",
"unterhaltung",
"unterkunft",
"unterricht",
"unterschied",
"unterschrift",
"untersuchung",
"urlaub",
"uebernachtung",
"vater",
"verbindung",
"verein",
"verkaeufer",
"verkaeuferin",
"verkehr",
"vermieter",
"versicherung",
"verspaetung",
"vertrag",
"video",
"vogel",
"volksschule",
"vormittag",
"vorname",
"vorsicht",
"vorwahl",
"waesche",
"wagen",
"wald",
"wasser",
"weg",
"wein",
"welt",
"werkstatt",
"werkzeug",
"westen",
"wetter",
"wiederhoeren",
"wiedersehen",
"wind",
"winter",
"wirtschaft",
"woche",
"wochenende",
"wochentag",
"wohnung",
"wolke",
"wort",
"wunsch",
"wurst",
"zahl",
"zahn",
"zeit",
"zeitschrift",
"zeitung",
"zentrum",
"zettel",
"zeugnis",
"zigarette",
"zimmer",
"zitrone",
"zoll",
"zucker",
"zug"};
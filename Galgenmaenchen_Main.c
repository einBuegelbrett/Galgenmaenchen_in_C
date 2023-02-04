#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int hauptspiel();
void ausgabeHangman(int);
char * zufaelligesWort(char *[]);
char * woerterliste[];
char * wortRückgabe(char *, char, char[]);
char * buchstabenSpeicher(char, char []);
int gewinnProbe(char[], int);
void endNachricht(int);
bool buchstabenKontrolle(char, char [], int );

int fehlerNummer = 0;

int versuch = 1;

int main()
{
  hauptspiel();
  return 0;
}

int hauptspiel() //Schnittpunkt von allem
{
  char gerwortListe[26]; //Array für geratene Buchstaben

  char * wort = zufaelligesWort(woerterliste);
  printf(wort);

  int laenge = strlen(wort);//länge des Wortes
  char ertwortListe[laenge];//Array mit erratenen Buchstaben

  for(int i = 0; i < laenge; i++)
  {
    ertwortListe[i] = '_';
  }

  for(int i = 0; i < 11; i++)
  {
    gerwortListe[i] = ' ';
  }

  printf("\n");
  //printf(ertwortListe);
  // wenn gewonnen gleich 1 ist, hat man gewonnen
  int gewonnen = gewinnProbe(ertwortListe, laenge);

  while(fehlerNummer < 11 && gewonnen == 0)
  {
    //printf("%d", fehlerNummer);
    //printf("\n"); //nur zum formatieren der Ausgabe
    // den Buchstaben den der User eingibt
    char buchstabe;
    do
    {
        printf("\n-------------------------------\n");
        printf(ertwortListe);
        printf("\nVersuch %d\n", versuch);
        printf("\n[");
        for(int i = 0; i < strlen(gerwortListe); i++)
        {
            printf("%c " ,gerwortListe[i]);
        }
        printf("]\n");

        printf("Gib ein Buchstaben an: ");
        scanf(" %c", &buchstabe);
    } while(buchstabenKontrolle(buchstabe, gerwortListe, laenge));

    wortRückgabe(wort, buchstabe, ertwortListe);
    buchstabenSpeicher(buchstabe, gerwortListe);
    ausgabeHangman(fehlerNummer);
    gewonnen = gewinnProbe(ertwortListe, laenge);
    versuch++;
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
        case(9):printf("      _________\n      |/      |\n      |      ( )\n      |       |\n   ___|___   / \\\n _/       \\_\n"); break;    /*9 print Hangman*/
        case(10):printf("      _________\n      |/      |\n      |      ( )\n      |       |\\\n   ___|___   / \\\n _/       \\_\n"); break;    /*10 print Hangman*/
        case(11):printf("      _________\n      |/      |\n      |      ( )\n      |      /|\\\n   ___|___   / \\\n _/       \\_\n"); break;    /*11 print Hangman*/
        default:printf("Fehler in der ausgabe Hangman Funktion");
    }
}

// gibt ein zufälliges Wort zurück
char * zufaelligesWort(char *liste[])
{
  srand(time(0));
  int nummer = rand() % 656;

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
            //printf("%s",&buchstabe);
            ertwortListe[i] = buchstabe;
            gesetzteZahl++;
        }
    }
    //printf("%d\n",gesetzteZahl);

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
    //printf(gerwortListe);
    /*
    for(int i = 0; i < strlen(gerwortListe); i++)
    {
        printf("%c", gerwortListe[i]);
    }
    */
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
"ausländer",
"ausländerin",
"ausland",
"aussage",
"ausstellung",
"ausweis",
"auto",
"autobahn",
"automat",
"bäckerei",
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
"brötchen",
"brücke",
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
"empfänger",
"empfang",
"ende",
"enkel",
"entschuldigung",
"erdgeschoss",
"erfahrung",
"ergebnis",
"erlaubnis",
"ermäßigung",
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
"fernsehgerät",
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
"glück",
"glückwunsch",
"glas",
"gleis",
"größe",
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
"hähnchen",
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
"käse",
"körper",
"küche",
"kühlschrank",
"kündigung",
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
"löffel",
"lösung",
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
"mädchen",
"märz",
"möbel",
"müll",
"mülltonne",
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
"nähe",
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
"päckchen",
"paket",
"panne",
"papier",
"papiere",
"parfüm",
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
"prüfung",
"praktikum",
"praxis",
"preis",
"problem",
"produkt",
"programm",
"prospekt",
"pullover",
"qualität",
"quittung",
"rücken",
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
"reisebüro",
"reiseführer",
"reparatur",
"restaurant",
"rezept",
"rezeption",
"rind",
"rock",
"rose",
"rundgang",
"süden",
"sache",
"saft",
"salat",
"salz",
"satz",
"schüler",
"schülerin",
"schalter",
"scheckkarte",
"schiff",
"schild",
"schinken",
"schirm",
"schlüssel",
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
"sehenswürdigkeit",
"seife",
"sekretärin",
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
"spülmaschine",
"spaß",
"spaziergang",
"speisekarte",
"spielplatz",
"sprache",
"sprachschule",
"sprechstunde",
"stück",
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
"tür",
"tüte",
"tag",
"tankstelle",
"tasche",
"tasse",
"taxi",
"ter Tee",
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
"universität",
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
"verkäufer",
"verkäuferin",
"verkehr",
"vermieter",
"versicherung",
"verspätung",
"vertrag",
"video",
"vogel",
"volksschule",
"vormittag",
"vorname",
"vorsicht",
"vorwahl",
"wäsche",
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
"wiederhören",
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
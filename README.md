# Galgenmaenchen_in_C

# Anwenderdokumentation

# Intro
Beim Galgenmaenchen muss der Spieler ein Wort Buchstabe für Buchstabe eraten, wobei er nur 11 Fehler machen darf.

# Spielregeln
In diesem Spiel wird ein Wort zufällig gewählt, der Spieler gibt Buchstaben an und kann maximal 11 Fehler haben und muss das zufällig gewählte Wort erraten, um zu gewinnen. Bei jedem falschen Versuch wird das Galgenmännchen Schritt für Schritt aufgebaut und die schon benutzten Buchstaben werden angegeben, und die erratenen angezeigt. Der Spieler kann keinen Buchstaben mehrmals benutzen.


# Eigenschaften 
•	Ein Zufallswähler von Worten
•	Versuche und Wörter in einer Textdatei speichern
•	Galgenmännchen in der Konsole anzeigen
•	Benutzte Buchstaben in der Konsole anzeigen
•	Erratene Buchstaben in der Konsole anzeigen
•	Einen Zähler (11 Versuche)



# Entwicklerdokumentation

1. Wir haben eine Vorgefertigte Liste an Wörtern in einer C-Datei. Das Programm wird dann ein zufälliges Element aus dieser Liste wählen und mit diesem Wort das Spiel starten.

2. Beim Zähler wird eine Schleife kreiert, die nach 11 Versuchen spätestens abbricht. Wenn das Wort davor erraten wird, gewinnt der Spieler und die Schleife wird abgebrochen. 

3. Das Galgenmännchen hat ein Vorbestimmtes Muster, was nach jedem Versuch Schritt für Schritt aufgebaut wird. Die benutzten sowie die erratenen Buchstaben werden mit dem Galgenmännchen ausgegeben.

4. Beim Spielstart wird das Geheime Wort versteckt (Zum Beispiel wird Apfel in _ _ _ _ _ versteckt). Durch erraten des richtigen Buchstabens wird das „_“ -Symbol durch den richtig erratenen Buchstaben ausgetauscht (Zum Beispiel wenn der Buchstabe „a“ erraten wird, wird „a _ _ _ _“ in der Konsole angezeigt. 

5. Die Versuche und die Wörter, werden in einer Textdatei abgelegt, sodass sie abgespeichert bleiben auch nach Beendigung des Programms. Nach jedem Spiel wird das zu erratene Wort mit der Anzahl an benötigten Versuchen an die Datei angehängt. 

De hartslagopstelling bestaat uit het volgende: Een TTGO T4 berust van een TFT panel 2.2 inch display. 
Waarbij de hartslagsensor communiceert via I2C met de TTGO T4. 
De draadloze communicatie gebeurt via bluetooth met een smartphone. 
En de gegevens kunnen ook nog lokaal worden gelogd op een sd-kaart. 
Om het lokaal loggen te starten drukt men op de linkerknop. 
Om het loggen te stoppen drukt men op de rechterknop. 
De middelste knop ging worden gebruikt voor een deep-sleep functie. 
Uiteindelijk hebben we dit achterwege gelaten en gewoon een schakelaar toegevoegd.

Dit was voor de eerste versie hierbij hadden we dan telkens 3 files te verwerken
de GPS-coordinaten, fijnstofmetingen en hartslagmetingen. Met versie 2 van de code
ontvangt de centrale console van de fijnstofopstelling ook hartslagmetingen. Aan de hand van EPSNOW
waarbij twee EPS32 modules onder elkaar kunnen communiceren. En slechts enkel 2 files nu moeten verwerkt worden.
Namelijk de GPS-coordinaten & hart-fijnstofmetingen in één file.

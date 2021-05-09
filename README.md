
# Draagbare mobiel fijnstofmeter & Hartslagteller
Fijnstofmeter &amp; Hartslagteller

Het doel van het project is om een draagbare mobiel fijnstof meter te hebben op een fiets. Gepaard met een hartslagteller. Om zo de fysieke inspanning te meten en lokale fijnstof. Samen met een main Python programma dat de meetwaardes visualiseert op een kaart. Voorbeeld:

![resultMap1](https://user-images.githubusercontent.com/78153942/117574484-89bc1d80-b0dd-11eb-8aaa-2bfb0591817b.png)

Als we in de files spreken over VERSIE 1:

Gaat dit om de opstelling waarbij zowel de hartslagteller als de fijnstofmeter met BLE communiceren met de smartphone en dus twee files worden aangemaakt.

Als we in de files spreken over VERSIE 2:

Dan werkt de opstelling als volgt de hartslagteller verzend hierbij zijn waardes door naar fijnstofopstellings centrale console op de fiets. Deze verzamelt dan beide metingen (dus zowel de hartslag als de fijnstofwaardes) in een file. En verzend deze dan via BLE naar de smartphone.
Hierbij wordt er slecht één file aangemaakt voor beide. Los hiervan kan men nog steeds op beide lokaal loggen op de SD kaart.
De itercommunicatie van de hartslag met de fijnstofopstelling gebeurt via ESPNOW. Dit is een ingebouwd functie waarbij twee EPS32 modules met elkaar kunnen communiceren aan de hand van WI-FI. Maar waarbij het verbruik ervan even lager ligt als traditionele WI-FI connectie. Maar gelijkaardig is als een gewone BLE connectie.

Dit is versie 2: Waarbij we zowel de hartslag als de fijnstof op de centrale console zien dat op de fiets komt

![Inked183075131_521261572379747_7215796782377619925_n_LI](https://user-images.githubusercontent.com/78153942/117577190-0bfe0f00-b0e9-11eb-8e33-209d2956543e.jpg)



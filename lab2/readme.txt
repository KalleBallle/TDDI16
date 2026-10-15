Hitta dubbletter
================

- Ungefärligt antal timmar spenderade på de två delarna av labben (valfritt):

del a:
del b:

- Vad är tidskomplexiteten på följande operationer i din hashtabell?

insert_key: Θ(1) 
  find_key: Θ(1)
 erase_key: Θ(n)


- Antag att vi vill sätta in många element i en Hash_Map<int, int>. Vi sätter
  därmed kapaciteten till 1000. Sedan sätter vi in element med nycklarna
  1000, 2000, 3000, 4000, och så vidare tills vi har satt in 500 element.
  Kommer hashtabellen fungera bra i det här fallet? Varför/varför inte?
	
  SVAR:
	Den kommer fungera sämre för varje gång du insert:ar multiplar av tusen så måste den linjärsonderera mycket
	det kommer efterlikna en lista. Alla kommer ligga på varandra i 12345.. etc ordning. 
	Så man kommer behöver gå igenom alla tidigare element för att hitta den från samma bucket	

- När testprogrammet jämför Hash_Map med std::unordered_map (alternativ 9) så
  använder vi int som både nyckel och värde. Typen int är lite speciell i
  avseendet att både hashning och jämförelse av int är mycket billiga. Titta
  på resultaten av jämförelsen, med fokus på "max chain". Vad tror du skulle
  hända med exempelvis tiden för uppslagning om vi i stället använder strängar
  som nyckel? Anta att strängarna är långa (ca 1000 tecken vardera) och att
  de första 500 tecknen i alla strängar är desamma.

SVAR:
	Den skulle ta mycket längre tid för string kollar char för char, så den skulle behöver göra minst 500 "char jämförelser"

- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

SVAR:
slow: O(n^2)
fast: O(n*p) där p är antalet pixlar som behöver läsas av loadimage. Men eftersom P är konstant så är det O(n)!


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?
  Tips: Använd flaggan "--nowindow" för enklare tidsmätning.
  Tips: Det är okej att uppskatta tidsåtgången för de fall du inte orkar vänta
  på att slow blir klar med det största testfallet. Om du gör detta är det en
  bra idé att beräkna tiden det tar att läsa in och skala ner bilderna separat
  från tiden det tar att jämföra bilderna. (Varför?) Du kan anta att inläsning
  är det dyra, och att inläsning tar lika lång tid i både "slow" och "fast"

|--------+-----------+--------+--------|
|        | inläsning |  slow  |  fast  |
|--------+-----------+--------+--------|
| tiny   |225        |327     |197     |
| small  |648        |831     |779     |
| medium |2561       |3560    |2690    |
| large  |66147      |657272  |75688   |
|--------+-----------+--------+--------|

- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?

SVAR: 
YES! Eftersom  detaljnivån sjunker med mindre summary_size eftersom man kollar på en 
mindre del av bildenrna (Man skalar ner bilden till en mindre storlek).

- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna använda den för
  att hitta bilder som liknar varandra? (Dvs. vilka egenskaper förväntar sig
  kod som *använder* "compute_summary"?) Tycker du att implementationen av
  "compute_summary" som är given i labbhandledningen uppfyller dessa egenskaper?

SVAR: 
Så länge bildernas kontrast inte skiftas, eller att den inte är flyttad (t.o.m på pixelskala) så 
kommer implementationen att hantera bilderna som lika, men om ljusstyrkan för hela bilden skiftas, 
(varken upp eller ner i ljusstyrka) så kommer den att anse att den bilden är "lika" med originalbilden.

- Ser du några problem med metoden för att se om två bilder är lika dana?
  Fundera exempelvis på vilka typer av olikheter som tolereras, och vilka
  typer av olikheter som anses vara för stora. Matchar detta din uppfattning
  om vad som borde vara lika?

SVAR: 
Eftersom brightness tar endast ett medelvärde mellan de olika r g b värdena finns det en möjlighet 
att compute summary och hashfunktionen säger att två bilder är samma, 
fast en bild är vanlig och en bild är samma bild fast alla färger "inverterade" färger.
Eller om man tar samma värdena för r g och b och byter plats på dem kommer den fortfarande
hantera den som "lika" mot originalbilden, och visas på skärmen. (Coolt testfall?) 
Så länge slutresultatet ger samma medelvärde så kommer våran funktion säga att de är lika.
Men annars så fungerar den relativt bra för majoriteten av fallen,
Speciellt vid en högre detaljnivå. Så länge man 

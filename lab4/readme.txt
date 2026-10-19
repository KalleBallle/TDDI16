Mönsterigenkänning
==================

- Ungefärligt antal timmar spenderade på labben (valfritt):


- Vad är tidskomplexiteten (i ordo-notation) för värstafallstiden av
  programmen som en funktion av N (antal punkter). Ge en kort motivering.

  Matchar brute-lösningen sitt värstafall i praktiken, eller har den ett
  medelfall som är bättre?

brute:    O(n⁴), vilket sker då alla 3 punkter är på en rad, då loopar man igenom en fjärde gång för resten av punkterna, annars O(n³)

fast:     n²log(n), eftersom vi använder vår copy_if. Vilket gör att vi enbart kollar efter punkter som är framför origo. 


- Fyll i tabellen nedan med riktiga körtider i sekunder när det känns
  vettigt att vänta på hela beräkningen.
  Ge uppskattningar av körtiden (baserat på tidskomplexiteten)
  i övriga fall.
    
      N       brute [s]     sortering [s]
 ----------------------------------
    150       0,095         0,008
    200       0,143         0,014
    300       0,332         0,048
    400       0,764         0,050
    800       5,996         0,131
   1600       49,250        0,477
   3200       394,000       1,862
   6400       3152,000      7,965
  12800       25216,00      34,870


- Energianvändning

  Antag att du använder mönsterigenkänningsprogrammet för att analysera
  data från en kamera. Kameran sitter i en byggnad och tar en bild
  på stommen av byggnaden var 30:e minut. Bilden förbehandlas sedan
  lite, innan punkter som representerar stommen skickas till
  mönsterigenkänningsprogrammet. Hittas inte tillräckligt många raka
  linjer så betyder det att något håller på att gå sönder, och
  att byggnaden behöver noggrannare inspektion.

  Hur mycket energi sparar du på ett år om du använder din snabbare
  sorteringslösning i stället för brute-lösningen? Du kan anta följande:
  - Systemet körs 24/7 under hela året.
  - Inget annat körs på det här systemet.
  - Systemet drar 8 W när det inte gör något (idle)
  - Systemet drar 36 W när det arbetar (med 1 kärna)
  - Räkna med att ditt program körs var 60:e minut (= 1 gånger/timme)
  - För- och efterbehandling är snabba, så vi kan bortse från dem
  - Indata till programmet innehåller ca 6400 punkter
  - Det är inte skottår (= 365 dagar)                                         // inte en a? 265.2422 år ???

  Att jämföra med drar en kombinerad kyl/frys ca 200 kWh per år
  (enligt Energimyndigheten).
 
  Kom ihåg: energi mäts ofta i kWh, vilket är:
   energi (kWh) = effekt (kW) * tid (h)

  Tips: ett sätt att räkna på är att först räkna förbrukningen av
  ett system som inte gör något på ett helt år, sedan lägga till
  den extra förbrukningen (36 W - 8 W = 28 W) för tiden som systemet
  är aktiv.

  (Siffrorna är löst baserade på en Intel i9-9900K, vi räknar bara på
  CPU:n för enkelhets skull, besparingarna blir sannolikt större om
  vi räknar på större delar av systemet, även om andra komponenter
  också drar ström i "idle".)

  -> 6400 p, 24 h * 365 d, 0,028 kWh, 

  E = P * t

  t_h = 24 * 365 = 8760 h
  t_s = t_h / (60*60) = 8760/3600 s
  
  E_idle = 8 * 8760 = 70,080 kWh
  E_kör = ( (0,036 - 0,008) * 8760) / 3600 = 0,068 kWh/s

  E_b = 70,080 + (0,036 - 0,008 ) * (3152,000 * (8760/3600)) = 284,836267 kWh
  E_f = 70,080 + (0,036 - 0,008 ) * (   7,965 * (8760/3600)) =  70,622682 kWh

Förbrukning av brute på ett år: 284,84 kWh

Förbrukning av sortering på ett år: 70,62 kWh

284,836267 - 70,622682 = 214,213585 kWh

Skillnad: 214,21 kWh


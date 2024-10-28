# Plant_Watering_System
Proiectul intitulat Plant Watering System reprezinta un sistem de irigatie automat, care va fi controlat din aplicatie.
Aplicatia va prelua date din FireBase (baza noastra de date) si va genera pe baza lor o notificare. Datele incarcate in FireBase vor reprezenta valori generate de catre senzorul de umiditate din sol.

Partea hardware va contine urmatoarele componente :
- Placa dezvoltare ESP32, ESP-WROOM-32, WIFI si Bluetooth BLE, Dual Core
- Terminal expansiune pentru ESP32, 38P
- LCD 1602
- Pompa Apa/Aer cu diafragma, 6-12V, R385
- Modul interfata I2C LCD 1602,2S
- Fire Dupont
- Fortun Pompa Apa
- Senzor umiditate sol, higrometru
- Modul releu termic, 1 canal, senzor temperatura, 5V
- Bradboard MB102 + Sursa + Fire dupont


In ceea ce priveste partea software, avem urmatoarele mentiuni:

PARTEA DE BACKEND (vom folosi javascript pentru implementare)
- va prelucra informatiile preluate din baza de date, care au fost incarcate ulterior, si le va transforma intr-o notificare care te avertizeaza ca nivelul de umiditate din solul plantei este scazut (atunci cand valorile indica acest lucru).


PARTEA DE FRONTEND (vom folosi React Native pentru implementare)
- va contine o bara de progres semicirculara, care indica procentul de umiditate al solului, si un buton, la apasare caruia planta va fi udata automat cu ajutorul pompei de apa si al furtunului. 

Proiectul urmărește să simplifice munca de îngrijire a plantelor de interior, automatizând udarea acestora direct din aplicație. Astfel, îngrijirea plantelor devine mai comodă și accesibilă, fără a mai fi nevoie de deplasări sau intervenții frecvente din partea utilizatorului.

# EMOtto ESP32 2.0 — Marco Mortari

Pacchetto del programma completo per ESP32 a 30 pin con shield, display GC9A01, quattro servo SG90, due TTP223, VL53L0X e DFPlayer Mini.

## Iniziare qui

1. Estrarre completamente questo ZIP. Non aprire lo sketch dall'archivio compresso.
2. Installare il supporto ESP32 di Espressif dal Gestore schede. Selezionare la scheda che corrisponde al proprio ESP32 classico con Bluetooth Serial. Annotare modello e versione del core dopo la prova. Il pacchetto non contiene una configurazione di compilazione certificata né un firmware precompilato.
3. Chiudere Arduino IDE e copiare le cartelle `Librerie/EMOttoDIYLib` e `Librerie/TFT_eSPI` nella cartella `libraries` dello sketchbook (su Windows normalmente `Documenti/Arduino/libraries`). Dentro ciascuna deve esserci direttamente `library.properties`. Riaprire Arduino IDE. La posizione dello sketchbook si vede nelle Preferenze. Le librerie sono incluse come cartelle, non come ZIP separati.
4. Dal Gestore librerie installare ESP32Servo, Adafruit GFX Library, Adafruit VL53L0X e DFRobotDFPlayerMini, con le dipendenze proposte.
5. Aprire `Firmware/EMOttoESP32_2_0/EMOttoESP32_2_0.ino` e premere Verifica. Nella cartella dello sketch deve esserci solo questo .ino: i vecchi file .ino vanno conservati fuori dalla cartella.
6. Selezionare la porta della scheda e caricare. Aprire il Monitor seriale a 115200 baud.
7. Installare `App/EMOttoController_3_0.apk` sul telefono Android, abbinare il dispositivo Bluetooth `EMOtto` e selezionarlo nell'app.

Questo firmware usa EMOttoDIYLib, non OttoDIYLib e non EMOtto32_pca9685. Se sono presenti copie diverse che contengono EMOtto.h o Oscillator.h, controllare nel log quali cartelle vengono scelte. Non caricare EMOtto_Bluetooth_Control: è un esempio semplificato distinto dal programma completo.

## Progetto modificabile dell'app (.aia)

`App/EMOttoController_3_0.apk` è l'app da installare sul telefono Android. `App/EMOttoController_3_0.aia` è il progetto sorgente da importare in MIT App Inventor tramite Projects > Import project (.aia) from my computer. Dopo aver modificato il progetto generare un nuovo APK dal menu Build. Il file .aia non si installa direttamente sul telefono.

Il progetto .aia fornito contiene Screen1, i blocchi di connessione/invio Bluetooth e gli asset grafici richiamati. Sono state verificate integrità dell'archivio e presenza di questi elementi; non è stata eseguita una build dell'app. La corrispondenza tra il progetto .aia e l'APK incluso non è stata certificata ricompilando il progetto.

## Display

La TFT_eSPI fornita è versione 2.5.43 ed è già configurata con Setup200_GC9A01: MOSI 23, SCLK 18, CS 5, DC 17, RST 16; TFT_BL 22 disabilitato. Usare questa copia per riprodurre la configurazione, evitando una seconda TFT_eSPI con impostazioni diverse. Un aggiornamento della libreria può sovrascrivere il setup: conservarne una copia.

## Collegamenti di segnale

| Componente | Segnale | GPIO ESP32 |
|---|---|---|
| Servo gamba sinistra | Segnale | 25 |
| Servo gamba destra | Segnale | 26 |
| Servo piede sinistro | Segnale | 27 |
| Servo piede destro | Segnale | 14 |
| Buzzer | Segnale | 13 |
| Touch 1 | OUT | 12 |
| Touch 2 | OUT | 33 |
| Display GC9A01 | MOSI/SDA | 23 |
| Display GC9A01 | SCLK/SCL | 18 |
| Display GC9A01 | CS | 5 |
| Display GC9A01 | DC | 17 |
| Display GC9A01 | RST | 16 |
| VL53L0X | SDA | 21 |
| VL53L0X | SCL | 22 |
| DFPlayer | TX → RX ESP32 | 32 |
| DFPlayer | RX ← TX ESP32, resistenza 1 kΩ in serie | 4 |
| DFPlayer | BUSY | 34 |

Per alimentazioni e montaggio consultare le immagini nella cartella Collegamenti. Il display è indicato a 3,3 V nel progetto; servo e DFPlayer usano l'alimentazione 5 V prevista. Le masse devono essere comuni. Alimentare il robot con batteria e UBEC come nel progetto: l'USB del PC serve a programmarlo e non sostituisce l'alimentazione dei servo.

Nota: i GPIO 32 e 4 descrivono rispettivamente RX e TX dell'ESP32; i segnali UART si collegano incrociati al DFPlayer.

## Audio sulla microSD

Copiare la cartella `MicroSD/mp3` nella radice della microSD destinata al DFPlayer. Le tracce 4, 31, 35, 36 e 37 sono escluse dalla distribuzione per copyright. Non rinumerare gli altri file per chiudere i buchi. Per usare quelle funzioni aggiungere personalmente audio di cui si possiedono i diritti; non viene distribuita musica sostitutiva.

Il firmware originale utilizza `myDFPlayer.play(numero)`, che seleziona l'indice della traccia e non garantisce la corrispondenza con il prefisso del nome. I file mancanti e l'ordine di copia possono quindi causare una traccia diversa da quella prevista. Prima della pubblicazione definitiva controllare gli abbinamenti sulla propria microSD. Una semplice nota sul copyright non risolve questa dipendenza tecnica. Il codice è mantenuto originale: non è stato cambiato in playMp3Folder.

Riferimenti delle tracce escluse:

| Numero | Richiamo |
|---|---|
| 4 | dance.cpp, primo ballo |
| 31 | BluetoothCommands.cpp, comando `|`; anche scelta casuale cantante 31–34 |
| 35 | dance2.cpp, secondo ballo |
| 36 | dance3.cpp, terzo ballo |
| 37 | dance4.cpp, quarto ballo |

L'elenco completo dei file audio inclusi è in `Documentazione/Audio_inclusi.csv`.

## Comandi principali dell'app

| Comando | Azione |
|---|---|
| N / A / S / L | Normale / arrabbiato / triste / amore |
| g / e / b / a / u / n | Disgusto / imbarazzo / noia / ansia / sorpresa / nostalgia |
| W / i / s / D | Avanti / indietro / sinistra / destra |
| X | Ferma i movimenti |
| + / - | Aumenta / diminuisce velocità |
| F / V / E / G | Inseguimento / evita ostacoli / emozioni / cantante |
| Z / w | Dorme / risveglio |
| , / . / _ / * | Balli 1 / 2 / 3 / 4 |
| ^ | Ferma la musica |
| U / J | Volume su / giù |
| H | Posa iniziale |

Touch 1 cambia le emozioni nella modalità emozioni. Touch 2 scorre le modalità. Dopo 90 secondi di inattività il robot si addormenta quando non è in modalità movimento, ballo o cantante e non ha un client Bluetooth collegato.

## Stato di verifica

Sono stati controllati lo sketch principale, la corrispondenza delle librerie, il setup del display, le chiamate Bluetooth, i GPIO e il contenuto dell'archivio. Non è stata eseguita una compilazione ESP32 in questo ambiente né una prova sul robot. Non presentare il pacchetto come testato solo perché è stato riordinato.

Prima di pubblicare confermare sul robot: avvio, display, touch, Bluetooth, stop X, servo, VL53L0X, DFPlayer, corrispondenza audio, quattro balli, sonno e risveglio. Annotare scheda, versione Arduino IDE, core ESP32 e versioni delle librerie esterne usate.

## Crediti e licenze

Progetto EMOtto di Marco Mortari. La libreria personalizzata deriva da Otto DIY; i file LICENSE dei componenti sono mantenuti nelle rispettive cartelle. Il progetto cita Camilo Parra Palacio, Scotty Franzyshen ed ElectronBot EMO. Le licenze originali di librerie, app, modelli e audio rimangono distinte: questo documento non attribuisce una nuova licenza unica all'intero pacchetto.

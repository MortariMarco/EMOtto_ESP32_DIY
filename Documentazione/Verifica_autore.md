# Controlli per l'autore prima della pubblicazione

- Firmware, app, modelli, audio e librerie sono estratti dall'archivio fornito. Nessuna modifica ai sorgenti.
- Versioni di prova, vecchia OttoDIYLib, esempi semplificati, video, PSD e file duplicati non sono inclusi.
- EMOttoDIYLib 1.0.0 e TFT_eSPI 2.5.43 sono le copie originali.
- La libreria originale conserva il vecchio esempio Bluetooth: le istruzioni indicano esplicitamente di aprire il firmware principale, non quell'esempio.
- Le tracce 4, 31, 35, 36, 37 non sono incluse. play(numero) dipende dall'indice del DFPlayer: verificare gli abbinamenti audio e completare la microSD privata prima di dichiarare tutti i balli/canti funzionanti.
- Nello setup originale performExpression(EXP_NORMAL) chiama forceHome() prima di Otto.init(). Questo ordine è stato preservato per rispettare la richiesta di non cambiare il programma: verificare l'avvio sul robot; se occorre correggerlo, spostare l'espressione iniziale dopo Otto.init().
- Senza il VL53L0X rilevato lo setup entra in while(1): il sensore fa parte della configurazione richiesta.
- Incluso il progetto App Inventor .aia: archivio integro, Screen1 e blocchi Bluetooth presenti, asset grafici richiamati disponibili. Il progetto non è stato compilato; non è certificata la corrispondenza binaria con l’APK. Provare i pulsanti sul robot.
- Alcuni testi dei pulsanti nell’AIA includono i comandi `(`, `)` e `/`, che non hanno un case dedicato nel gestore Bluetooth della libreria. Questi controlli vanno verificati; app e firmware sono stati mantenuti come forniti.
- Le versioni esatte del core e delle dipendenze non sono registrate nell'archivio. Completare i dati qui sotto dopo la prova.

Scheda: ____________________
Arduino IDE: _______________
Core ESP32: ________________
ESP32Servo: ________________
Adafruit GFX: _____________
Adafruit VL53L0X: __________
DFRobotDFPlayerMini: _______
Data e risultato prova: ____

Aggiornamento del pacchetto: rimossi dall’elenco audio anche 0004 e 0036, aggiunto il progetto .aia alla documentazione. Il pacchetto contiene 32 file MP3. Nessuna modifica a firmware, librerie o sorgenti dell’app.

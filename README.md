# EMOtto ESP32 DIY — firmware 2.0

Robot project by Marco Mortari, for a classic ESP32 with Bluetooth Serial, GC9A01 display, four SG90 servos, two TTP223 touch sensors, VL53L0X and DFPlayer Mini.

Project and printable parts: https://www.printables.com/model/1362284-emotto_esp32-diy

## Start here

1. Download and extract the repository.
2. Install the Espressif ESP32 board support in Arduino IDE and select the board matching your classic ESP32.
3. Close Arduino IDE. Copy `Librerie/EMOttoDIYLib` and `Librerie/TFT_eSPI` into your Arduino sketchbook's `libraries` directory. Each copied folder must contain `library.properties` directly. Reopen Arduino IDE.
4. Install ESP32Servo, Adafruit GFX Library, Adafruit VL53L0X and DFRobotDFPlayerMini through Library Manager, including their dependencies.
5. Open **`Firmware/EMOttoESP32_2_0/EMOttoESP32_2_0.ino`**. Verify and upload. This is the full firmware; do not use the simplified Bluetooth example inside the library.
6. Install `App/EMOttoController_3_0.apk` on Android, pair the robot named `EMOtto`, and select it in the app.

Read [the Italian installation guide and pinout](LEGGIMI.md) before connecting or powering the robot.

## Included files

- Full Arduino firmware: `Firmware/EMOttoESP32_2_0/`.
- Original EMOttoDIYLib 1.0.0 and configured TFT_eSPI 2.5.43: `Librerie/`.
- Android APK and editable MIT App Inventor `.aia` source: `App/`.
- Audio files: `MicroSD/mp3/`.
- Wiring diagrams: `Collegamenti/`.
- Printable parts and documentation: see the corresponding folders.

The supplied TFT_eSPI is configured for GC9A01: MOSI 23, SCLK 18, CS 5, DC 17, RST 16, with TFT_BL 22 disabled. Avoid replacing it with a differently configured copy.

## App source

Import `App/EMOttoController_3_0.aia` into MIT App Inventor using Projects > Import project (.aia) from my computer. The Build menu can generate an Android APK. The `.aia` file is source code, not an installable app.

## Audio exclusions

Tracks **4, 31, 35, 36 and 37** are not distributed for copyright reasons. Do not renumber the remaining files. Use only audio you have the rights to use when completing your own microSD.

The original firmware uses DFPlayer `play(number)`, which selects a track index. Missing files or copy order can affect which sound is played; verify the mapping on your microSD. See `Documentazione/Audio_inclusi.csv` and the Italian guide.

## Verification status

This distribution preserves the supplied firmware and library sources. Archive integrity and the presence of the App Inventor project components were checked. No ESP32 compilation, app rebuild or hardware test was performed while preparing this package. Tested board/core/dependency versions are not recorded in the supplied archive; the author checklist is in `Documentazione/Verifica_autore.md`.

## Credits and licenses

EMOtto project by Marco Mortari. The custom library derives from Otto DIY; original library license files are preserved in their respective folders. The project credits Camilo Parra Palacio, Scotty Franzyshen and ElectronBot EMO. Components retain their respective licenses; this repository does not introduce one blanket license for all firmware, app, models and audio.

# SerialJSON
Clase para Arduino para convertir a JSON.

Es necesario tener instalada las biblioteca "ArduinoJson".

```c++
#include <SerialJson>
...
SerialJson serialJson;
...
if (serialJson.check()) {
    // do something
}
...
void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        serialJson.inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '}') {
            serialJson.stringComplete = true;
        }
    }
}
```

https://github.com/bblanchon/ArduinoJson


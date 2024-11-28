#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int irSensor = 13; // IR sensor pin
int pulseCount = 0;     // Number of pulses detected in one second
int rpm = 0;            // Calculated RPM value
unsigned long lastMillis = 0; // Time tracking for RPM calculation

void setup() {
  Serial.begin(9600);
  pinMode(irSensor, INPUT_PULLUP); // Configure IR sensor as input with pull-up
  lcd.init();                      // Initialize LCD
  lcd.backlight();                 // Turn on LCD backlight
}

void loop() {
  unsigned long currentMillis = millis(); // Get current time

  // Check IR sensor state
  if (digitalRead(irSensor) == LOW) { // Pulse detected
    pulseCount++;
    delay(10); // Simple debounce to avoid multiple counts per pulse
  }

  // Calculate RPM every 1 second
  if (currentMillis - lastMillis >= 1000) {
    rpm = (pulseCount * 60); // Calculate RPM (pulses per second * 60)
    pulseCount = 0;        // Reset pulse count for the next second
    lastMillis = currentMillis; // Update lastMillis

    // Print to serial monitor
    Serial.print("RPM: ");
    Serial.println(rpm);

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RPM Counter");
    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(rpm);
  }
}

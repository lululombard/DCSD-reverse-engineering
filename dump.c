#include <Wire.h>

#define I2C_START 0x50
#define I2C_END 0x57
#define BLOCK_SIZE 512

void setup(){
	Wire.begin();
	Serial.begin(115200);
}

void loop(){
	if (Serial.available() && Serial.read()) {
		Serial.print("Starting the dump from 0x");
		Serial.print(I2C_START, HEX);
		Serial.print(" to 0x");
		Serial.print(I2C_END, HEX);
		Serial.print(" (");
		Serial.print((I2C_END - I2C_START) + 1);
		Serial.print(" * ");
		Serial.print(BLOCK_SIZE);
		Serial.print(" = ");
		Serial.print(((I2C_END - I2C_START) + 1) * BLOCK_SIZE);
		Serial.println(" bytes in total)...");

		unsigned int errors = 0;

		for (byte addr = I2C_START; addr <= I2C_END; addr++) {
			Serial.print("\n");
			Serial.println("----------------------");
			Serial.print("Reading bank 0x");
			Serial.println(addr, HEX);
			Serial.println("----------------------");

			//Set the memory pointer to the start (it will add +1 at each request)
			Wire.beginTransmission(addr);
			Wire.write(0x00);
			Wire.endTransmission();

			int count = 0;
			int charcount = 0;
			Wire.beginTransmission(addr);
			Wire.requestFrom(addr, 1);
			while (count++ < BLOCK_SIZE/2) {
				int val = -1;
				if (!Wire.available()) errors++;
				else val = Wire.read();
				if (val == -1) Serial.print("##");
				else {
					if (val < 16) Serial.print("0");
					Serial.print(val, HEX);
				}
				if (++charcount >= 16) {
					charcount = 0;
					Serial.print("\n");
				}
				else if (charcount % 2 == 0) Serial.print(" ");
				if (!Wire.requestFrom(addr, 1)) errors++;
			}
			Serial.print("\n");
			Serial.println("----------------------");
			Serial.print("Read ");
			Serial.print((count - 1) * 2);
			Serial.print(" bytes from 0x");
			Serial.println(addr, HEX);
			Serial.println("----------------------");
			Wire.endTransmission();
		}
		if (errors == 0) Serial.println("--- END OF DUMP - NO ERRORS ---");
		else {
			Serial.print("--- END OF DUMP - ");
			Serial.print(errors);
			Serial.println(" ERRORS ---");
		}
	}
}

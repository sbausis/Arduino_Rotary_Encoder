/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

int rotation = 0;
int get_rotation(long reading, long previous) {
	int rotation = (reading > previous);
	return rotation;
}

int cnt = 0;
float turns = 0;

int turn_indicator_PIN = 4;
int turn_indicator_value_new = 0;
int turn_indicator_value_old = 0;
void setup_turn_indicator() {
	pinMode(turn_indicator_PIN, INPUT);
	turn_indicator_value_new = digitalRead(turn_indicator_PIN);
	turn_indicator_value_old = turn_indicator_value_new;
}
long get_turn_indicator_new_value(long reading, long previous) {
	long new_value = reading;
	turn_indicator_value_new = digitalRead(turn_indicator_PIN);
	if (turn_indicator_value_new != turn_indicator_value_old) {
		if (reading > previous) {
			cnt++;
			Serial.print(cnt);
			Serial.print(" +\t");
		} else {
			cnt--;
			Serial.print(cnt);
			Serial.print(" -\t");
		}
		new_value = (cnt * 3600);
	} else {
		Serial.print(cnt);
		Serial.print("\t");
	}
	
	turns = (cnt/2);
	Serial.print(turns);
	Serial.print("\t");
	Serial.print(new_value);
	Serial.print("\t");
	turn_indicator_value_old = turn_indicator_value_new;
	return new_value;
}

int encoder_A_PIN = 2;
int encoder_B_PIN = 3;

Encoder myEnc(encoder_A_PIN, encoder_B_PIN);

void setup() {
	
	//setup_turn_indicator();
	
	Serial.begin(9600);
	Serial.println("Basic Encoder Test:");
	
}

long oldPosition  = -999;
void loop() {
	long newPosition = myEnc.read();
	if (newPosition != oldPosition) {
		//get_turn_indicator_new_value(newPosition, oldPosition);
		
		Serial.print(newPosition);
		
		Serial.println("");
		
		oldPosition = newPosition;
	}
}


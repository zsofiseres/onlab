#ifndef INC_MAIN_H_
#define INC_MAIN_H_

void LEDprocess(int tomb[][24]);
void clear();
void AD_process();
void color2array();
void color2led(int led, int red, int green, int blue);
void oneColor(int red, int green, int blue);
void setArray(int szin_tomb[]);

#endif /* INC_MAIN_H_ */

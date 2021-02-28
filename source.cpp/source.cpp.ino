#define READER
#ifdef WRITER
//void setup() {  
//  Serial.begin(115200);
//}
//const int buffer_size=255;
//char buffer[buffer_size];
//void loop() {  
//  if(Serial.available()>0){
//    int len=Serial.readBytesUntil('\n', buffer, buffer_size);
//    if(len<=buffer_size)buffer[len]='\0';
//    Serial.write(buffer);
//    //Serial.flush();
//  }
//}
char str[4];
void setup() {
  Serial.begin(9600);
}
void loop() {
  int value=1234; //this would be much more exciting if it was a sensor value  
  itoa(value, str, 10); //Turn value into a character array
  Serial.write(str, 4);
}
#endif
#ifdef READER
//void setup() {  
//  Serial.begin(115200);
//  Serial1.begin(115200);
//  pinMode(LED_BUILTIN, OUTPUT); 
//  digitalWrite(LED_BUILTIN, LOW);
//}
//const int buffer_size=255;
//char buffer[buffer_size];
//void loop() {  
//  if(Serial.available()>0){
//    int len=Serial.readBytesUntil('\n', buffer, buffer_size);
//    if(len<=buffer_size)buffer[len]='\0';
//    if(buffer[0]=='0')
//      digitalWrite(LED_BUILTIN, LOW);
//    else if(buffer[0]=='1')
//      digitalWrite(LED_BUILTIN, HIGH);
//    Serial1.println(buffer);
//  }
//}
char str[4];
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  int i=0;
  if (Serial1.available()) {
    delay(100); //allows all serial sent to be received together
    while(Serial1.available() && i<4) {
      str[i++] = Serial1.read();
    }
    str[i++]='\0';
  }
  if(i>0) {
    Serial.println(str);
  }
}
#endif

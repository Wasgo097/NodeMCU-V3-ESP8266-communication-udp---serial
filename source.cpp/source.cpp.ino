void setup() {  
  Serial.begin(115200);
}
const int buffer_size=255;
char buffer[buffer_size];
void loop() {  
  if(Serial.available()>0){
    int len=Serial.readBytesUntil('\n', buffer, buffer_size);
    if(len<=buffer_size)buffer[len]='\0';
    Serial.println(buffer);
    Serial.flush();
  }
}

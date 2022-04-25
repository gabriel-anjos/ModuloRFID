#include <SPI.h>
#include <MFRC522.h>
#define ledRed 04
#define ledGreen 05
constexpr uint8_t RST_PIN = D3;     
constexpr uint8_t SS_PIN = D4;
int Permitido = 0;
String conteudo= "";
    
String TagsCadastradas[] = {"06 8e 67 a5","6d fc e8ab"}; 
                            
                        
                            
MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;



void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT); 
  Serial.println("Aproxime o seu cartao do leitor...");
}

void acessoLiberado(){
  Serial.println("");
  Serial.println("Access granted!");
  Serial.println("Tag Cadastrada: " + conteudo);
  digitalWrite(ledGreen,HIGH);
  delay(2000);
  digitalWrite(ledGreen,LOW); 
  Permitido = 0;  
}
void acessoNegado(){
  Serial.println("");
  Serial.println("Access denied!");
  Serial.println("Tag NAO Cadastrada: " + conteudo); 
  digitalWrite(ledRed,HIGH);
  delay(2000);
  digitalWrite(ledRed,LOW);
}


void loop() {
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID da tag :");
  conteudo= ""; 
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i],HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i],HEX));
    
  }
       
   for (int i = 0;i<(sizeof(TagsCadastradas)/sizeof(TagsCadastradas)); i++) {
       if(  conteudo.substring(1).equalsIgnoreCase(TagsCadastradas[i])){
              Permitido = 1;
         }
     }
    if(Permitido == 1) acessoLiberado();         
    else acessoNegado(); 
        delay(2000); 
                
  Serial.println("");
 
}
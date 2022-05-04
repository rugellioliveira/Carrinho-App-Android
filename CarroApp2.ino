//Controlar carrinho pelo aplicativo gerado no MIT App Inventor

#include <WiFi.h>


String  ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

const char* nomeRede = "Conectando...";
const char* senhaRede = "positivo*";
String ipenvio;

int MotorA_sentido1 = 15; //IN1
int MotorA_sentido2 = 2; //IN2
int MotorB_sentido1 = 4; //IN3
int MotorB_sentido2 = 5; //IN4

//************************************************************************************************************************************************
void setup()
{
ClientRequest = "";

//inicializa serial com 115200 bits por segundo
  Serial.begin(115200);

  pinMode(MotorA_sentido1, OUTPUT);
  pinMode(MotorA_sentido2, OUTPUT);
  pinMode(MotorB_sentido1, OUTPUT);
  pinMode(MotorB_sentido2, OUTPUT);

  digitalWrite(MotorA_sentido2, LOW);
  digitalWrite(MotorB_sentido2, LOW);
  digitalWrite(MotorA_sentido1, LOW);
  digitalWrite(MotorB_sentido1, LOW);

  
  WiFi.begin(nomeRede, senhaRede); //conecta à rede Wifi

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado, IP: ");
  Serial.println(WiFi.localIP()); //obtemos aqui o IP do servidor

 server.begin(); //inicia o servidor
}

//**********************************************************************************************************************************************************
void loop()
{

    Serial.println(WiFi.localIP()); //obtemos aqui o IP do servidor
    Serial.println(""); //obtemos aqui o IP do servidor
    //Serial.println("ClientRequest");
    //Serial.println(ClientRequest);
    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (ReadIncomingRequest());
    ClientRequest.remove(0, 5);
    ClientRequest.remove(ClientRequest.length()-9,9);

    ipenvio=WiFi.localIP().toString(); //converte o endereço ip para string
    
    //IPAddress ip=WiFi.localIP(); //depois do ip ser definido pelo próprio esp ele ficará fixo

    if (ClientRequest == "frente") {
    digitalWrite(MotorA_sentido2, HIGH);
    digitalWrite(MotorA_sentido1, LOW);
    digitalWrite(MotorB_sentido2, HIGH);
    digitalWrite(MotorB_sentido1, LOW);
  }

  if (ClientRequest == "tras") {
    digitalWrite(MotorA_sentido2, LOW);
    digitalWrite(MotorA_sentido1, HIGH);
    digitalWrite(MotorB_sentido2, LOW);
    digitalWrite(MotorB_sentido1, HIGH);
  }

  if (ClientRequest == "esquerda") {
    digitalWrite(MotorA_sentido2, LOW);
    digitalWrite(MotorA_sentido1, LOW);
    digitalWrite(MotorB_sentido2, HIGH);
    digitalWrite(MotorB_sentido1, LOW);
  }

  if (ClientRequest == "direita") {
    digitalWrite(MotorA_sentido2, HIGH);
    digitalWrite(MotorA_sentido1, LOW);
    digitalWrite(MotorB_sentido2, LOW);
    digitalWrite(MotorB_sentido1, LOW);
  }
  
  if (ClientRequest == "pare") {
    digitalWrite(MotorA_sentido2, LOW);
    digitalWrite(MotorA_sentido1, LOW);
    digitalWrite(MotorB_sentido2, LOW);
    digitalWrite(MotorB_sentido1, LOW);
  }

    //se estiver no aplicativo esta exibição não será feita
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    //client.println("O carro esta indo para frente");
    //client.print("");
    client.print(ipenvio); ///exibe a string que é o endereço ip na página do servidor web
    client.println("</html>");
    client.stop();
    delay(1);
    
    client.flush();
}

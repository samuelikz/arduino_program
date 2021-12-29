// Bibliotecas 
#include <SPI.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Configurações de IP
byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(0, 0, 0, 0); // IP Padrão
IPAddress gateway(0, 0, 0, 0); // Gateway Padrão
IPAddress subnet(0, 0, 0, 0); 

// Configurações de conecxão com o phpMyadmin

IPAddress server_addr(0, 0, 0, 0);  // IP of the MySQL *server* here
char user[] = "user"; // MySQL user login username
char password[] = "passwd@"; // MySQL user login password

//Exemplo de insert
char INSERT_SQL[] = "INSERT INTO arduino.Funcionarios (Nome, Funcao) VALUES ('Samuel Nunes','Teste')";

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect
  
  Ethernet.begin(mac_addr, ip, gateway, subnet);
  Serial.println("Connecting...");
  delay(5000);
  
  if (conn.connect(server_addr, 3306, user, password)) {
    Sucess();
    delay(5000);
  }
  else
    Serial.println("Connection failed.");
}

void Sucess(){
  Serial.println("Connection accept."); // You would add your code here to run a query once on startup.
}

void loop() {
  delay(2000);

  Serial.println("Recording data.");

  //iniciar query
  
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  //execute

  cur_mem->execute(INSERT_SQL);
  delete cur_mem;
  conn.close();
}

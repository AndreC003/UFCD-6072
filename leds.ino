// Definir os pinos dos LEDs
const int PINO_VERDE = 5;    // Pino para o LED verde
const int PINO_VERMELHO = 3; // Pino para o LED vermelho
const int PINO_AZUL = 6;     // Pino para o LED azul

// Definir o pino para o sensor de som (leitura analógica)
const int PINO_SOM = A0;     // Pino analógico A0 para o sensor de som

// Variáveis de controle
int valorSom = 0; // Variável para armazenar o valor lido do sensor de som
int limiteSom = 300; // Limite para considerar um som detectado (ajustar conforme necessário)
int estado = 0; // Variável para controlar o estado atual (0 - verde, 1 - vermelho, 2 - azul)
unsi3gned long tempoAnterior = 0; // Variável para controlar o tempo de alternância
unsigned long intervalo = 2000;  // Intervalo de 2 segundos para alternância de cores

unsigned long ultima_leitura_sensor = millis();

void setup() {
  // Configurar os pinos dos LEDs como saída
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_VERMELHO, OUTPUT);
  pinMode(PINO_AZUL, OUTPUT);

  // Configurar o pino do sensor de som como entrada
  pinMode(PINO_SOM, INPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Ler o valor analógico do sensor de som
 if(millis() - ultima_leitura_sensor > 200) 
 {

  valorSom = analogRead(PINO_SOM);
  // Exibir o valor lido no Monitor Serial para depuração
  Serial.print("Valor do sensor de som: ");
  Serial.println(valorSom);

  ultima_leitura_sensor = millis();
 }


  // Verificar se o valor do sensor de som é superior ao limite (indica som)
  if (valorSom > limiteSom) {
    Serial.println("Som detectado! Mudando para azul.");
    // Mudar para azul diretamente
    estado = 2; // Mudar o estado para azul
  } else {
    // Se não houver som, alternar entre verde e vermelho a cada 2 segundos
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= intervalo) {
      tempoAnterior = tempoAtual;
      // Alterna entre verde e vermelho
      if (estado == 0) {
        estado = 1; // Muda para vermelho
      } else {
        estado = 0; // Muda para verde
      }
    }
  }

  // Controle de cores com switch-case
  switch (estado) {
    case 0: // Verde
      // Serial.println("Cor atual: VERDE");
      digitalWrite(PINO_VERDE, HIGH);   // Acender verde
      digitalWrite(PINO_VERMELHO, LOW); // Apagar vermelho
      digitalWrite(PINO_AZUL, LOW);     // Apagar azul
      break;

    case 1: // Vermelho
      // Serial.println("Cor atual: VERMELHO");
      digitalWrite(PINO_VERDE, LOW);    // Apagar verde
      digitalWrite(PINO_VERMELHO, HIGH); // Acender vermelho
      digitalWrite(PINO_AZUL, LOW);     // Apagar azul
      break;

    case 2: // Azul (som detectado)
      // Serial.println("Cor atual: AZUL");
      digitalWrite(PINO_VERDE, LOW);    // Apagar verde
      digitalWrite(PINO_VERMELHO, LOW); // Apagar vermelho
      digitalWrite(PINO_AZUL, HIGH);    // Acender azul
      break;

    default:
      Serial.println("Estado inválido!");
      break;
  }
}


// Definição dos pinos PWM para cada cor
const int pinRed = 9;
const int pinGreen = 8;
const int pinBlue = 10;
const int pinWhite = 11;

// Duração do amanhecer e anoitecer (em milissegundos)
const int duracaoAmanhecer = 5000; // 5 segundos
const int duracaoAnoitecer = 5000; // 5 segundos

// Função para suavizar a transição entre duas cores
void transicaoCor(int rStart, int gStart, int bStart, int wStart,
                  int rEnd, int gEnd, int bEnd, int wEnd, int duracao) {
    int steps = 255; // número de passos da transição para suavidade
    int delayTime = duracao / steps;

    for (int i = 0; i <= steps; i++) {
        int r = rStart + (rEnd - rStart) * i / steps;
        int g = gStart + (gEnd - gStart) * i / steps;
        int b = bStart + (bEnd - bStart) * i / steps;
        int w = wStart + (wEnd - wStart) * i / steps;

        analogWrite(pinRed, r);
        analogWrite(pinGreen, g);
        analogWrite(pinBlue, b);
        analogWrite(pinWhite, w);

        delay(delayTime);
    }
}

void setup() {
    // Definir pinos como saída
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);
    pinMode(pinWhite, OUTPUT);
}

void loop() {
    // Simular o amanhecer (do escuro para o branco quente)
    transicaoCor(0, 0, 20, 0,    // Início: fraco azul
                 255, 200, 100, 100, // Fim: branco quente
                 duracaoAmanhecer);

    delay(2500); // Manter "dia" por alguns segundos

    // Simular o anoitecer (do branco quente para o escuro)
    transicaoCor(255, 200, 100, 100, // Início: branco quente
                 0, 0, 20, 0,        // Fim: fraco azul
                 duracaoAnoitecer);

    delay(2500); // Manter "noite" por alguns segundos
}

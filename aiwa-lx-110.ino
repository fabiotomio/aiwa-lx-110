// https://www.arduino.cc/en/Reference/AttachInterrupt
// https://www.arduino.cc/en/Reference/Volatile



/**************************************
* Constants
***************************************/
int const clock = 2;
int const latch = 3;
int const data  = 4;

/**************************************
* Variables
***************************************/
int running = 0;
int tracks = 6;           // Amount of tracks on LP
boolean trackList[7] = {false, false, false, false, false, false, false};

/**************************************
* Setup
***************************************/
void setup() {
    
    // I/O init
    Serial.println('I/O init');
    Serial.begin(9600);
    pinMode(clock,OUTPUT);
    pinMode(latch,OUTPUT);
    pinMode(data,OUTPUT);

    // Read Sensors
    // Serial.println('Read sensors');
    // needlePosition = digitalRead(needleSensor) == HIGH ? true : false;
    
    // Ignition
    // Serial.println('Ignition');
}

/**************************************
* Loop
***************************************/
void loop() {
    // Processa a seleção das tracks
    processTrackButtons();
    updateTrackInterface();

    // Processa os comandos
    processCommandButtons();
}

/**************************************
* Interface - Tracks Functions
***************************************/
// Process track selection
void processTrackButtons() {
    // ler porta com entrada do Key das Tracks
    float value = 0.1;
    int track_button = 0;

    // montar tabela de conversao de tensão para track
    switch( (int) value ) {
        case 1:
            track_button = 1;
            break;
        case 2:
            track_button = 2;
            break;
        case 3:
            track_button = 3;
            break;
        case 4:
            track_button = 4;
            break;
        case 5:
            track_button = 5;
            break;
        case 6:
            track_button = 6;
            break;
        case 7:
            track_button = 7;
            break;
        case 8:
            track_button = 8;
            break; // clear all
        
        default:
            return;
    }

    if(track_button == 8) {
        // deseleciona todos
        for(int i = 0; i < 7; i++) { trackList[i] = false; }
    } else if(track_button >= tracks) { // tem que ser menor ou igual a quantidades de faixas do disco
        // inverte o conteudo do selecionado
        trackList[track_button] = !trackList[track_button];
    }   
}

// Process commands
void processCommandButtons() {

    float value;
    if (running == 0) {
        value = 0.1;
    } else {
        value = (float) running;
    }

    switch((int) value) {
        case 1:
            playCue();
            break;
        case 2:
            repeat();
            break;
        case 3:
            intro();
            break;
        case 4:
            forward();
            break;
        case 5:
            rewind();
            break;
        case 6:
            needle();
            break;
        case 7:
            nextTrack();
            break;
        case 8:
            previousTrack();
            break;
        case 9:
            scanTracks();
            break;
        default:
            break;
    }
}

/**************************************
* Player Functions
***************************************/
void intro() {
    // toca cada uma dela por x segundos
}

void repeat() {
    // repete infinitas vezes as musicas selecionadas
    // se não possuir musicas selecionadas repete o disco todo
}

void nextTrack() {
    // próxima musica
}

void forward() {
    // adianta um pouco a música
}

void previousTrack() {
    // musica anterior
}

void rewind() {
    // volta um pouco a música
}

void playCue() {
    // começa a tocar
    // caso tenha musicas selecionadas na playlist toca somente elas
    // caso não tenha, toca o disco todo
}

/**************************************
* Engine Functions
***************************************/

void needle() {
    // levanta a agulha ou abaixa a agulha
}

void fowardNeedle() {
    // anda com o carrinho pra frente
}

void rewindNeedle() {
    // anda com o carrinho pra trás
}

void directDrive(boolean status) {
    // controla o direct drive
}

int scanTracks() {
    // send needle to 0
    // upNeedle();
    return 5;
}

void updateTrackInterface() {

    digitalWrite(latch,LOW);    
    for (int x = 0; x <= 7; x++) {

        digitalWrite(clock,LOW); 
        if (trackList[x]) {
            digitalWrite(data,HIGH);
        } else {
            digitalWrite(data,LOW);
        }
        digitalWrite(clock,HIGH);

    }
    digitalWrite(latch,HIGH);
}

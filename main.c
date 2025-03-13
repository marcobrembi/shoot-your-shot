// Includo tutte le librerie che userò
#include "lib/lib.h"

bool run = true;
bool introyn = false;

// Richiamo delle funzioni
void spara(FILE *file, Punto *colpo);
void punto(Punto *bersaglio);
bool colpito(FILE *file, Punto colpo, Punto bersaglio, double dif);
void intro();
void introduzione();
void istruzioni();
void bomb();
void razzo();
void vittoria();
void lvlsuccessivo(int *colpi, int *livello, Punto *bersaglio);
void termina(FILE *file, int *vita, int *livello);
void fine(FILE *file, int *vita);
void ricomincia(FILE *file);
void lettura(FILE *generico);



// Il Main
int main() {
    while (run == true)
    {
        FILE *file = fopen("output/output.txt", "w");  // 'w' per scrivere, crea il file se non esiste
        Punto colpo, bersaglio; // Dichiaro le coordinate del colpo e del bersaglio con la struct Punto
        bool hit; // Dichiaro la variabile hit (colpito oppure no?)
        int colpi = 5, livello = 1, vita = 1; // dichiaro le variabili di servizio, come numero di colpi da sparare, livelli, sono ancora in vita?
        
        punto(&bersaglio); // Pregenerazione coordinate del bersaglio
        intro(); // Introduzione, con eventuali istruzioni
        
        while (vita == 1) {  // Inizio del gioco
            printf("Livello: %d, il raggio di azione della bomba e' di %lf metri \n", livello, (double)(225 - livello * 25));

            while (colpi > 0) {
                printf("\n");
                spara(file, &colpo); // Funzione per chiedere l'alzo e la rotazione del missile

                hit = colpito(file, colpo, bersaglio, livello); // funzione che verifica se il bersaglio è stato colpito
                if (hit) {
                    bomb(); // Simula l'effetto del colpo
                    colpi = 0; // Se colpito, termina il ciclo
                }
                colpi--; // decrementa ogni volta il numero di colpi
            }

            if (hit) { // Livello Successivo
                lvlsuccessivo(&colpi, &livello, &bersaglio);
            }

            if (colpi <= 0 && !hit) { // Se i colpi sono terminati e il bersaglio non è stato colpito, termina il gioco
                termina(file, &vita, &livello);
                ricomincia(file);
            }

            if (livello == 6){
                fine(file, &vita);
                ricomincia(file);
            }
        }
        
        fclose(file); //chiudo il file
    }
    return 0;
}
// --------------------------------------------------------------------------------------

// Funzione che calcola il punto dove la bomba cadrà
void spara(FILE *file, Punto *colpo) {
    float verticale, orizzontale, gittata;

    // file
    if (file == NULL) {
        printf("Errore nell'apertura del file.\n");
    }

    // Richiesta e verifica dell'alzo (da 0 a 70 gradi)
    printf("Inserisci l'alzo: ");
    scanf("%f", &verticale);
    while (verticale < 0 || verticale > 70) {
        printf("\n");
        printf("Alzo non valido. Deve essere tra 0 e 70 gradi.\n");
        printf("Inserisci l'alzo: ");
        scanf("%f", &verticale);
    }

    // Richiesta e verifica dell'orizzontale (da -45 a +45 gradi)
    printf("Inserisci l'orizzontale :");
    scanf("%f", &orizzontale);
    while (orizzontale < -45 || orizzontale > 45) {
        printf("\n");
        printf("Rotazione non valida. Deve essere tra -45 e +45 gradi.\n");
        printf("Inserisci l'orizzontale : ");
        scanf("%f", &orizzontale);
    }
    fprintf(file, "Colpo sparato! Verticale: %2f, Orizzontale: %2f" , verticale, orizzontale);
    // Conversione degli angoli da gradi a radianti
    orizzontale = orizzontale * (PI / 180);
    verticale = verticale * (PI / 180);

    // Calcolo della gittata
    gittata = (pow(v, 2) / g) * (sin(2 * verticale));

    // Calcolo delle coordinate del colpo
    colpo->x = gittata * cos(orizzontale);
    colpo->y = gittata * sin(orizzontale);

    printf("Colpo sparato! Coordinate del colpo: x = %.2f, y = %.2f\n", colpo->x, colpo->y);
    fprintf(file, " X: %2f, Y: %2f\n", colpo->x, colpo->y);
    
}
// --------------------------------------------------------------------------------------


// Genera il bersaglio randomicamente
void punto(Punto *bersaglio) {
    srand(time(0));
    
    bersaglio->x = rand() % (800 - 600 + 1) + 600;
    bersaglio->y = -200 + rand() % (200 + 200 + 1);
}
// --------------------------------------------------------------------------------------

// Controlli
bool colpito(FILE *file, Punto colpo, Punto bersaglio, double livello) {
    double distanza;
    bool hit;
    distanza = sqrt(pow(colpo.x - bersaglio.x, 2) + pow(colpo.y - bersaglio.y, 2));
    printf("La distanza dal bersaglio e' di %lf metri \n", distanza);
    if (distanza < (225 - livello * 25))  {
        hit = true;
        fprintf(file, "\nBERSAGLIO COLPITO!\n\n");
    } else {
        hit = false;
    }
    
    return hit;
}

void lvlsuccessivo(int *colpi, int *livello, Punto *bersaglio) {
    *colpi = 5; // Ripristina il numero di colpi
    (*livello)++; // Incrementa il livello
    punto(bersaglio); // Genera un nuovo bersaglio
}
// --------------------------------------------------------------------------------------

// Finali
void termina(FILE *file, int *vita, int *livello){
    printf("\n");
    printf("\n");
    *vita = 0; // Imposta vita a 0
    printf("Game over! Hai raggiunto il livello %d.\n", *livello);
    fprintf(file, "\nGame over! Hai raggiunto il livello %d.\n", *livello);
    sleep(5);
    
}

void fine(FILE *file, int *vita){
    vittoria();

    *vita = 0; // Imposta vita a 0 però in questo caso ho vinto
    printf("Hai VINTO!");
    fprintf(file, "\nHai VINTO!");
    sleep(5);
    
}
// --------------------------------------------------------------------------------------

// Introduzione del gioco
void intro(){
    if (introyn == false)
    {
        introduzione();
        introyn = true;
    }
    else{
        system("cls");
    }
}

void introduzione() {
    char istr;

    // introduzione scritta
    printf("\n");
    printf("=====================================\n");
    printf("         SHOOT YOUR SHOT        \n");
    printf("=====================================\n");
    printf("\n");
    razzo(); // pesca la funzione razzo per snellire il codice
    sleep(3); // Aspetta 2 secondi
    system("cls");
    
    printf("Il tuo obiettivo e' colpire il bersaglio!\n");
    sleep(2); 
    printf("Inserisci l'alzo e la rotazione per mirare con il lanciamissili.\n");
    sleep(2); 
    printf("Hai 5 colpi a disposizione. Buona fortuna!\n\n");
     
    
    sleep(1); // Aspetta 1  secondo
    printf("          Premi 1 per vedere le istruzioni, altrimenti invio per continuare...\n");
    istr = getchar();

    // Per controllare se vuole vedere le istruzioni
   
    switch (istr) {
        case '1': // Se l'utente preme '1'
            system("cls");
            istruzioni();
            break;
        case '\n': // Se l'utente preme "Invio"
            system("cls");
            break;
        default: // Qualsiasi altro carattere
            printf("Input non valido. Inizio del gioco!\n");
            sleep(2);
            system("cls");
            break;
    }  
}

void istruzioni() {
    FILE *generico = fopen("txt/istruzioni.txt", "r");
    lettura(generico);
}



// --------------------------------------------------------------------------------------

// Funzione di lettura generica
void lettura(FILE *generico) {
    char buffer[BUFSIZ];

    if (generico == NULL) {
        printf("Errore: impossibile aprire il file.\n");
        return;
    }

    // Legge e stampa una riga alla volta
    while (fgets(buffer, sizeof(buffer), generico) != NULL) {
        printf("%s", buffer);
    }

    fclose(generico);  // Chiude il file
}
// --------------------------------------------------------------------------------------




// animazione bomba
void bomb() {
    printf("\n");
    FILE *generico = fopen("txt/bomba.txt", "r");
    lettura(generico);
    printf("\n");
    sleep(3);
    system("cls");
}

// animazione razzo
void razzo() {
    FILE *generico = fopen("txt/razzo.txt", "r");
    lettura(generico);
}

void vittoria(){
    FILE *generico = fopen("txt/vittoria.txt", "r");
    lettura(generico);
}

void ricomincia(FILE *file){
    getchar(); // Svuota il buffer
    char istr;
    printf("          Premi 1 per terminare il gioco, altrimenti invio per continuare...\n");
    istr = getchar();
    
    // Per controllare se vuole vedere le istruzioni
   
    switch (istr) {
        case '1': // Se l'utente preme '1'
            system("cls");
            run = false;
            break;
        case '\n': // Se l'utente preme "Invio"
            system("cls");
            break;
        default: // Qualsiasi altro carattere
            printf("Input non valido. Inizio del gioco!\n");
            sleep(2);
            system("cls");
            break;
    }  
}
// Librerie
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> 
#include <unistd.h>

// Costanti
#define g 9.80505   // Valori gravitazionali per provincia di Milano
#define v 100   // velocità in m/s del colpo
#define PI 3.14159265358979323846   // pi greco

// Struct per il colpo e il bersaglio
typedef struct {
    float x;
    float y;
} Punto;


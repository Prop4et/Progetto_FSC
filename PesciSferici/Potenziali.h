


#ifdef POTENZIALI

#else
#include <math.h>
#include <iostream>
#include "Pesce.h"
#include "School.h"
#include "define.h"
#endif
/*
//==========================================
//Forze e potenziali con posizioni
//==========================================

float RepulsiveForceFishX(float*, float*); //Forze repulsive, scalari, primo argomento posizione del pesce che genera, secondo del pesce che subisce
float RepulsiveForceFishY(float*, float*); //avevo sbagliato un segno ora va
float RepulsiveForceFishZ(float*, float*);

float* RepulsiveForcesFish(float*, float*); // Forze repulsive, vettoriali, primo argomento pos pesce che genera, secondo del pesce che la subisce

float RepulsivePotenzialFish(float*, float*); //potenziale da cui si ricavano le forze, probabilmente inutile


float AttractiveForceSchoolX(float*, float*, float*, float); //Forze del potenziale attrattivo, primo argomento posizione del banco, secondo vel banco
float AttractiveForceSchoolY(float*, float*, float*, float); //terzo pos pesce che subisce, quarto dimensioni medie del banco
float AttractiveForceSchoolZ(float*, float*, float*, float); //#### DA TESTARE ####

float* AttractiveForcesSchool(float*, float*, float*, float); //Forze del potenziale del banco attrattive, vettoriali, prima banco poi pesce

float AttractivePotenzialSchool(float*, float*, float*, float); //potenziale attrattivo per interazioni banco-pesce


float AttractiveForceHoleX(float*, float*); //interazione pesce-buca, scalari con primo argomento posizione pesce, secondo posizione buca
float AttractiveForceHoleY(float*, float*); //
float AttractiveForceHoleZ(float*, float*); //#### DA TESTARE ####

float* AttractiveForcesHole(float*, float*); //interazione pesce-buca, vettoriali

float AttractivePotenzialHole(float*, float*); //potenziale dell'interazione pesce-buca

//==========================================
//Forze e potenziali con pesci (overload di pesci vari)
//==========================================

float RepulsiveForceFishX(Pesce, Pesce);  //idee per fare degli overload con pesce invece di posizioni? potrebbe essere comodo
//float RepulsiveForceFishX(Pesce *, Pesce *);
float RepulsiveForceFishY(Pesce, Pesce);
//float RepulsiveForceFishY(Pesce*, Pesce*);
float RepulsiveForceFishZ(Pesce, Pesce);
//float RepulsiveForceFishZ(Pesce*, Pesce*);

float* RepulsiveForcesFish(Pesce, Pesce);
//float* RepulsiveForcesFish(Pesce*, Pesce*);

float RepulsivePotenzialFish(Pesce, Pesce);
//float RepulsivePotenzialFish(Pesce*, Pesce*);


float AttractiveForceSchoolX(School, Pesce);  //da finire di overloaddare
float AttractiveForceSchoolY(School, Pesce); // #### da semplificare se vengono aggiunti attributi allo School ####
float AttractiveForceSchoolZ(School, Pesce);

float* AttractiveForcesSchool(School, Pesce);

//float AttractivePotenzialSchool(School, Pesce);



//float AttractiveForceHoleX(Pesce, Hole); //interazione pesce-buca, scalari con primo argomento
//float AttractiveForceHoleY(Pesce, Hole); //
//float AttractiveForceHoleZ(Pesce, Hole); //
//
//float* AttractiveForcesHole(Pesce, Hole); //interazione pesce-buca



//======================================
//Funzione per unire tutte le forze che due pesci sentono fra di loro
//======================================

float AllForceFishX(Pesce, Pesce); //il primo pesce è quello che subisce tutte le forze, il secondo è quello che le genera
float AllForceFishY(Pesce, Pesce); //basta ottenere dal secondo pesce la posizione della buca e aggiungere quello repulsiva
float AllForceFishZ(Pesce, Pesce);

float* AllForcesFish(Pesce, Pesce);

#define POTENZIALI
#endif
*/
void SetAccelerazioni(School& Oceano);
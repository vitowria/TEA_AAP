#include <stdio.h>  // sprintf
#include <string.h> // strdup

//#define CLEAR2CONTINUE
#include "include/traces.h"

#include "elt.h"

/////////////////////////////////////////////////////////////////////////
//
// Type T_elt
// char * toString(T_elt) :
// 	Renvoie une chaîne de caractère représentant un T_elt pour l’afficher
// T_elt genElt(void) :
// 	Génère un nouveau T_elt différent du précédent
// 	(utiliser une variable statique)
/////////////////////////////////////////////////////////////////////////

#ifdef ELT_CHAR
// T_elt est un char...
char *toString(T_elt e) {
  // Il faut transformer un char en chaine...
  static char buffer[2];
  buffer[0] = e;
  buffer[1] = '\0';
  return buffer;
  // Si on allouait de la mémoire pour buffer, il faudrait penser à la
  // libérer...
  // => Risque de fuite de mémoire...
  // On ne peut pas non plus allouer un tableau static sur la pile !
  // => On utilise un buffer déclaré comme variable statique !
  // Dans ce cas, deux appels à toString renverraient la même adresse...
}

T_elt genElt(void) {
  static int indice = 0;
  // on va égrainer les caractères alphabétiques de 'a' à 'z'
  // de manière circulaire pour ne pas déborder...
  return 'a' + (indice++ % 26);
}
#endif

#ifdef ELT_INT
// T_elt est un int...
char *toString(T_elt e) {
  // Il faut transformer un int en chaine...
  static char buffer[11]; // nbr max de chiffres nécessaires ?
  // 2^31 vaut 2147483648...
  sprintf(buffer, "%d", e);
  return buffer;
  // cf. remarques précédentes
}

T_elt genElt(void) {
  static int indice = 0;
  return indice++;
}
#endif

#ifdef ELT_STRING
// T_elt est un char * ...
char *toString(T_elt e) {
  return e; // c'est déjà une chaine !
}

T_elt genElt(void) {
  static int indice = 0;
  // produire une chaine aléatoire...
  // On va écrire elt_<numéro>
  char buffer[15]; // elt_+<11 chiffres>
  sprintf(buffer, "elt_%d", indice++);
  return strdup(buffer);
}
#endif

#ifdef ELT_RPN
char * toString(T_elt e) {
	static char buffer[100]; 
	sprintf(buffer, "v: %d, s: %c", e.result, e.status); 
	return buffer; 	
}

T_elt genElt(void) {
  T_elt aux;
  aux.result = 0;
  aux.status = 'z';
  return aux;
}
#endif

T_elt eltdup(T_elt e) {
  T_elt aux;
  aux.result = e.result;
  aux.status = e.status;
  return aux;
}

/*static char buffer[2];
        buffer[0] = e;
        buffer[1] = '\0';
        return buffer; */

/////////////////////////////////////////////////////

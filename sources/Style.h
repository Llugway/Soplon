#pragma once

#include "Auxilaire.h"

typedef struct for_style {
	unsigned int nb;
	unsigned int space_before_parenth;
	unsigned int space_after_parenth;

	unsigned accolade;
	unsigned accolade_solo;

	unsigned int affectation;
	unsigned space_before_affectation;
	unsigned space_after_affectation;

	unsigned int comparaison;
	unsigned space_before_comparaison;
	unsigned space_after_comparaison;

	unsigned int virgule;
	unsigned int space_before_virgule;
	unsigned int space_after_virgule;

	unsigned point_virgule;
	unsigned space_before_point_virgule;
	unsigned space_after_point_virgule;
};

typedef struct if_style {
	unsigned int nb;
	unsigned int space_before_parenth;
	unsigned int space_after_parenth;

	unsigned accolade;
	unsigned accolade_solo;

	unsigned int comparaison;
	unsigned space_before_comparaison;
	unsigned space_after_comparaison;

};

typedef struct while_style {
	unsigned int nb;
	unsigned int space_before_parenth;
	unsigned int space_after_parenth;

	unsigned accolade;
	unsigned accolade_solo;

	unsigned int comparaison;
	unsigned space_before_comparaison;
	unsigned space_after_comparaison;
};

typedef struct function_style {
	unsigned int nb;
	unsigned int space_before_parenth;
	unsigned int space_after_parenth;

	unsigned accolade;
	unsigned accolade_solo;

	unsigned int virgule;
	unsigned int space_before_virgule;
	unsigned int space_after_virgule;
};


typedef struct macro_style {
	unsigned int nb;

	unsigned int space_before_parenth;
	unsigned int space_after_parenth;

	unsigned int virgule;
	unsigned int space_before_virgule;
	unsigned int space_after_virgule;

};

typedef struct struct_style {
	unsigned accolade;
	unsigned accolade_solo;

	//unsigned int virgule;
	//unsigned int space_before_virgule;
	//unsigned int space_after_virgule;
};

class Style
{
public :

	struct_style struct_s;
	for_style for_s;
	if_style if_s;
	function_style function_s;
	while_style while_s;
	macro_style macro_s;
	
	unsigned space_before_point_virgule;
	unsigned point_virgule;

	unsigned int virgule;
	unsigned int space_before_virgule;
	unsigned int space_after_virgule;

	unsigned int affectation;
	unsigned space_before_affectation;
	unsigned space_after_affectation;
	unsigned tab_before_affectation;
	unsigned tab_after_affectation;

	unsigned int comparaison;
	unsigned space_before_comparaison;
	unsigned space_after_comparaison;

	//unsigned int pointer;
	//unsigned int space_after_pointer;

	void displayStyle();
	void styleAppend(Style s2);
};


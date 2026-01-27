#include "Style.h"

void Style::displayStyle()
{
	if (for_s.nb != 0) {
		std::cout << "For nb : " << for_s.nb << std::endl;
		std::cout << "Accolades ouvrantes: " << for_s.accolade << std::endl;
		std::cout << "Accolades open solo : " << for_s.accolade_solo << std::endl;

		std::cout << "Parenths space before : " << for_s.space_before_parenth << std::endl;
		std::cout << "Parenths space after : " << for_s.space_after_parenth << std::endl;

		std::cout << "Affectations : " << for_s.affectation << std::endl;
		std::cout << "Affectations space before : " << for_s.space_before_affectation << std::endl;
		std::cout << "Affectations space after : " << for_s.space_after_affectation << std::endl;

		std::cout << "Comparaisons : " << for_s.comparaison << std::endl;
		std::cout << "Comparaisons space before : " << for_s.space_before_comparaison << std::endl;
		std::cout << "Comparaisons space after : " << for_s.space_after_comparaison << std::endl;

		std::cout << "Virgules : " << for_s.virgule << std::endl;
		std::cout << "Virgules space before : " << for_s.space_before_virgule << std::endl;
		std::cout << "Virgules space after : " << for_s.space_after_virgule << std::endl;

		std::cout << "Points Virgules : " << for_s.point_virgule << std::endl;
		std::cout << "Points Virgules space before : " << for_s.space_before_point_virgule << std::endl;
		std::cout << "Points Virgules space after : " << for_s.space_after_point_virgule << std::endl;
		std::cout << std::endl;
	}


	if (if_s.nb != 0) {
		std::cout << "If nb : " << if_s.nb << std::endl;
		std::cout << "Accolades ouvrantes: " << if_s.accolade << std::endl;
		std::cout << "Accolades open solo : " << if_s.accolade_solo << std::endl;

		std::cout << "Parenths space before : " << if_s.space_before_parenth << std::endl;
		std::cout << "Parenths space after : " << if_s.space_after_parenth << std::endl;

		std::cout << "Comparaisons : " << if_s.comparaison << std::endl;
		std::cout << "Comparaisons space before : " << if_s.space_before_comparaison << std::endl;
		std::cout << "Comparaisons space after : " << if_s.space_after_comparaison << std::endl;

		std::cout << std::endl;
	}

	if (while_s.nb != 0) {
		std::cout << "While nb : " << while_s.nb << std::endl;
		std::cout << "Accolades ouvrantes: " << while_s.accolade << std::endl;
		std::cout << "Accolades open solo : " << while_s.accolade_solo << std::endl;

		std::cout << "Parenths space before : " << while_s.space_before_parenth << std::endl;
		std::cout << "Parenths space after : " << while_s.space_after_parenth << std::endl;

		std::cout << "Comparaisons : " << while_s.comparaison << std::endl;
		std::cout << "Comparaisons space before : " << while_s.space_before_comparaison << std::endl;
		std::cout << "Comparaisons space after : " << while_s.space_after_comparaison << std::endl;

		std::cout << std::endl;

	}


	if (function_s.nb != 0) {
		std::cout << "Function nb : " << function_s.nb << std::endl;
		std::cout << "Accolades ouvrantes: " << function_s.accolade << std::endl;
		std::cout << "Accolades open solo : " << function_s.accolade_solo << std::endl;

		std::cout << "Parenths space before : " << function_s.space_before_parenth << std::endl;
		std::cout << "Parenths space after : " << function_s.space_after_parenth << std::endl;

		std::cout << "Virgules : " << function_s.virgule << std::endl;
		std::cout << "Virgules space before : " << function_s.space_before_virgule << std::endl;
		std::cout << "Virgules space after : " << function_s.space_after_virgule << std::endl;

		std::cout << std::endl;
	}

	if (macro_s.nb != 0) {
		std::cout << "Macro nb : " << macro_s.nb << std::endl;
		std::cout << "Parenths space before : " << macro_s.space_before_parenth << std::endl;
		std::cout << "Parenths space after : " << macro_s.space_after_parenth << std::endl;
		std::cout << "Virgules : " << macro_s.virgule << std::endl;
		std::cout << "Virgules space before : " << macro_s.space_before_virgule << std::endl;
		std::cout << "Virgules space after : " << macro_s.space_after_virgule << std::endl;
		std::cout << std::endl;
	}

	if (point_virgule != 0) {
		std::cout << "Points Virgules : " << point_virgule << std::endl;
		std::cout << "Points Virgules space before : " << space_before_point_virgule << std::endl;
	}

	if (affectation != 0) {
		std::cout << "Affectations : " << affectation << std::endl;
		std::cout << "Affectations space before : " << space_before_affectation << std::endl;
		std::cout << "Affectations space after : " << space_after_affectation << std::endl;
		std::cout << "Affectations tab before : " << tab_before_affectation << std::endl;
		std::cout << "Affectations tab after : " << tab_after_affectation << std::endl;
	}

	if (comparaison != 0) {
		std::cout << "Comparaisons : " << comparaison << std::endl;
		std::cout << "Comparaisons space before : " << space_before_comparaison << std::endl;
		std::cout << "Comparaisons space after : " << space_after_comparaison << std::endl;
	}

	if (virgule != 0) {
		std::cout << "Virgules : " << virgule << std::endl;
		std::cout << "Virgules space before : " << space_before_virgule << std::endl;
		std::cout << "Virgules space after : " << space_after_virgule << std::endl;
	}

	//if (pointer != 0) {
	//	std::cout << "Pointeur : " << pointer << std::endl;
	//	// std::cout << "Affectation space before : " << style.space_before_affectation << std::endl;
	//	std::cout << "Pointeur space after: " << space_after_pointer << std::endl;
	//}
	std::cout << std::endl;
}

void Style::styleAppend(Style s2) {
	
	for_s.nb += s2.for_s.nb;
	for_s.space_before_parenth += s2.for_s.space_before_parenth;
	for_s.space_after_parenth += s2.for_s.space_after_parenth;
		

	for_s.accolade += s2.for_s.accolade;
	for_s.accolade_solo += s2.for_s.accolade_solo;
	

	for_s.affectation += s2.for_s.affectation;
	for_s.space_before_affectation += s2.for_s.space_before_affectation;
	for_s.space_after_affectation += s2.for_s.space_after_affectation;
	

	for_s.comparaison += s2.for_s.comparaison;
	for_s.space_before_comparaison += s2.for_s.space_before_comparaison;
	for_s.space_after_comparaison += s2.for_s.space_after_comparaison;
	

	for_s.virgule += s2.for_s.virgule;
	for_s.space_before_virgule += s2.for_s.space_before_virgule;
	for_s.space_after_virgule += s2.for_s.space_after_virgule;

	for_s.point_virgule += s2.for_s.point_virgule;
	for_s.space_before_point_virgule += s2.for_s.space_before_point_virgule;
	for_s.space_after_point_virgule += s2.for_s.space_after_point_virgule;

	if_s.nb += s2.if_s.nb;
	if_s.space_before_parenth += s2.if_s.space_before_parenth;
	if_s.space_after_parenth += s2.if_s.space_after_parenth;

	if_s.accolade += s2.if_s.accolade;
	if_s.accolade_solo += s2.if_s.accolade_solo;

	if_s.comparaison += s2.if_s.comparaison;
	if_s.space_before_comparaison += s2.if_s.space_before_comparaison;
	if_s.space_after_comparaison += s2.if_s.space_after_comparaison;

	while_s.nb += s2.while_s.nb;
	while_s.space_before_parenth += s2.while_s.space_before_parenth;
	while_s.space_after_parenth += s2.while_s.space_after_parenth;

	while_s.accolade += s2.while_s.accolade;
	while_s.accolade_solo += s2.while_s.accolade_solo;

	while_s.comparaison += s2.while_s.comparaison;
	while_s.space_before_comparaison += s2.while_s.space_before_comparaison;
	while_s.space_after_comparaison += s2.while_s.space_after_comparaison;


	function_s.nb += s2.function_s.nb;
	function_s.space_before_parenth += s2.function_s.space_before_parenth;
	function_s.space_after_parenth += s2.function_s.space_after_parenth;

	function_s.accolade += s2.function_s.accolade;
	function_s.accolade_solo += s2.function_s.accolade_solo;

	function_s.virgule += s2.function_s.virgule;
	function_s.space_before_virgule += s2.function_s.space_before_virgule;
	function_s.space_after_virgule += s2.function_s.space_after_virgule;

	struct_s.accolade += s2.struct_s.accolade;
	struct_s.accolade_solo += s2.struct_s.accolade_solo;

	point_virgule += s2.point_virgule;
	space_before_point_virgule += s2.space_before_point_virgule;
	
	affectation += s2.affectation;
	space_before_affectation += s2.space_before_affectation;
	space_after_affectation += s2.space_after_affectation;

	tab_after_affectation += s2.tab_after_affectation;
	tab_before_affectation += s2.tab_before_affectation;

	
	comparaison += s2.comparaison;
	space_before_comparaison += s2.space_before_comparaison;
	space_after_comparaison += s2.space_after_comparaison;
	
}
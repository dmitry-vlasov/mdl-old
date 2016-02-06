/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Formula.cpp                                */
/* Description:     abstract interfaces for del theory                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace interface {


	/***************************
	 *		Public members
	 ***************************/

	bool
	Formula :: isPreNormal() const
	{
		switch (getKind()) {
		case GENERAL_SUB_KIND : // c ⊑ d, general case
			return false;
		case SIMPLE_SUB_KIND :  // a ⊑ b, where a and b are primitive terms
		case CONJ_SUB_KIND :    // a_1 ⊓ ··· ⊓ a_n ⊑ b, where a_1,...,a_n and b are primitive terms
		case RIGHT_SUB_KIND :   // a ⊑ ∃r.b, where a and b are primitive terms
		case LEFT_SUB_KIND :    // ∃r.a ⊑ b, where a and b are primitive terms
			return true;
		case IDENTITY_EQ_KIND :   // c ≡ d
		case DEFINITION_EQ_KIND : // a ≡ d by definition, where a is a primitive term
			return false;
		case PRIMITIVE_EQ_KIND :  // a ≡ b, where a and b are primitive terms
			return true;
		}
	}

	/********************************
	 *		Public static members
	 ********************************/

	Formula :: Kind
	Formula :: getKind (const Term* term_1, const Term* term_2)
	{
		if (term_1->isDeep() || term_2->isDeep()) {
			return GENERAL_SUB_KIND;
		}
		const Term :: Kind kind_1 = term_1->getKind();
		const Term :: Kind kind_2 = term_2->getKind();
		switch (kind_1) {
		case Term :: TOP_KIND :
		case Term :: VARIABLE_KIND :
			switch (kind_2) {
			case Term :: TOP_KIND :
			case Term :: VARIABLE_KIND :
				return SIMPLE_SUB_KIND;
			case Term :: EXISTS_KIND :
				return RIGHT_SUB_KIND;
			case Term :: INTERSECT_KIND :
				return GENERAL_SUB_KIND;
			}
		case Term :: INTERSECT_KIND :
			switch (kind_2) {
			case Term :: TOP_KIND :
			case Term :: VARIABLE_KIND :
				return CONJ_SUB_KIND;
			case Term :: EXISTS_KIND :
				return GENERAL_SUB_KIND;
			case Term :: INTERSECT_KIND :
				return GENERAL_SUB_KIND;
			}
		case Term :: EXISTS_KIND :
			switch (kind_2) {
			case Term :: TOP_KIND :
			case Term :: VARIABLE_KIND :
				return LEFT_SUB_KIND;
			case Term :: EXISTS_KIND :
				return GENERAL_SUB_KIND;
			case Term :: INTERSECT_KIND :
				return GENERAL_SUB_KIND;
			}
		}
	}

	const char*
	Formula :: showKind (const Kind kind)
	{
		switch (kind) {
		case GENERAL_SUB_KIND : // c ⊑ d, general case
			return "general";
		case SIMPLE_SUB_KIND :  // a ⊑ b, where a and b are primitive terms
			return "simple";
		case CONJ_SUB_KIND :    // a_1 ⊓ ··· ⊓ a_n ⊑ b, where a_1,...,a_n and b are primitive terms
			return "conjunction";
		case RIGHT_SUB_KIND :   // a ⊑ ∃r.b, where a and b are primitive terms
			return "right exists";
		case LEFT_SUB_KIND :    // ∃r.a ⊑ b, where a and b are primitive terms
			return "left exists";
		case IDENTITY_EQ_KIND :   // c ≡ d
			return "eq";
		case DEFINITION_EQ_KIND : // a ≡ d by definition, where a is a primitive term
			return "def";
		case PRIMITIVE_EQ_KIND :  // a ≡ b, where a and b are primitive terms
			return "prim_eq";
		default :
			return "none";
		}
	}
	const char*
	Formula :: showType (const Type type)
	{
		switch (type) {
		case SUBSET_TYPE :  // c ⊑ d - subset
			return "subset";
		case EQUALITY_TYPE : // c ≡ d - equality
			return "equality";
		default :
			return "none";
		}
	}
}
}



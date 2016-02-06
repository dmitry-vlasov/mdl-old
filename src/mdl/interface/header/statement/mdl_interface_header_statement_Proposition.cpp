/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Proposition.cpp           */
/* Description:     abstract interface for proposition statement             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/header/statement/mdl_interface_header_statement_Statement.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proposition :: Proposition() :
	sortedIndex_ (index :: undefined :: ASSERTION) {
	}
	Proposition :: ~ Proposition() {
	}

	inline void
	Proposition :: setSortedIndex (const index :: Assertion sortedIndex) {
		sortedIndex_ = sortedIndex;
	}
	inline index :: Assertion
	Proposition :: getSortedIndex() const {
		return sortedIndex_;
	}


	/*********************************
	 *		Overloaded operators
	 *********************************/

	inline bool
	operator < (const Proposition& proposition_1, const Proposition& proposition_2)
	{
		if (proposition_1.getRate() < proposition_2.getRate()) {
			return true;
		} else if (proposition_1.getRate() == proposition_2.getRate()) {
			return (&proposition_1 < &proposition_2);
		} else {
			return false;
		}
	}
	inline bool
	operator <= (const Proposition& proposition_1, const Proposition& proposition_2)
	{
		if (proposition_1.getRate() <= proposition_2.getRate()) {
			return true;
		} else if (proposition_1.getRate() == proposition_2.getRate()) {
			return (&proposition_1 <= &proposition_2);
		} else {
			return false;
		}
	}
	inline bool
	operator > (const Proposition& proposition_1, const Proposition& proposition_2) {
		return operator < (proposition_2, proposition_1);
	}
	inline bool
	operator >= (const Proposition& proposition_1, const Proposition& proposition_2) {
		return operator <= (proposition_2, proposition_1);
	}
	inline bool
	operator == (const Proposition& proposition_1, const Proposition& proposition_2) {
		return (&proposition_1 == &proposition_2);
	}

	inline int
	compareByRate (Proposition* prop_1, Proposition* prop_2)
	{
		if (prop_1 == prop_2) {
			return 0;
		} else if (*prop_1 < *prop_2){
			return -1;
		} else {
			return 1;
		}
	}
	inline int
	compareByExpSize (Proposition* prop_1, Proposition* prop_2)
	{
		int size_1 = prop_1->getExperience()->getSize();
		int size_2 = prop_2->getExperience()->getSize();
		return size_1 - size_2;
	}
}
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Assertions.cpp                                  */
/* Description:     global container for assertions                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_ASSERTIONS_CPP_
#define MDL_MATH_ASSERTIONS_CPP_

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/math/mdl_math_Assertions.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertions :: Assertions () :
	Container_ (INITIAL_ASSERTION_VECTOR_CAPACITY),
	axiomVector_ (INITIAL_AXIOM_VECTOR_CAPACITY),
	definitionVector_ (INITIAL_DEFINITION_VECTOR_CAPACITY),
	theoremVector_ (INITIAL_ASSERTION_VECTOR_CAPACITY),
	problemVector_ (INITIAL_PROBLEM_VECTOR_CAPACITY),
	mutex_ () {
		 pthread_mutex_init (&mutex_, NULL);
	}
	Assertions :: ~ Assertions () {
	}

	inline index :: Assertion
	Assertions :: getSize() const {
		return Container_ :: getSize();
	}
	inline mdl :: Assertion*
	Assertions :: get (const index :: Assertion index) {
		return Container_ :: getForm (index);
	}
	mdl :: Assertion*
	Assertions :: get (const char* name)
	{
		form :: Identificator identificator (name);
		const index :: Assertion
			index = Math :: theories()->getRoot()->getIndex (&identificator);
		return Container_ :: getForm (index);
	}
	index :: Assertion
	Assertions :: add (mdl :: Assertion* assertion)
	{
		pthread_mutex_lock (&mutex_);
		switch (assertion->getKind()) {
		case mdl :: Assertion :: AXIOM :
			axiomVector_.add (assertion);
			break;
		case mdl :: Assertion :: DEFINITION :
			definitionVector_.add (assertion);
			break;
		case mdl :: Assertion :: THEOREM :
			theoremVector_.add (assertion);
			break;
		case mdl :: Assertion :: PROBLEM :
			problemVector_.add (assertion);
			break;
		default : break;
		}
		const index :: Assertion index = Container_ :: addForm (assertion);
		pthread_mutex_unlock (&mutex_);
		return index;
	}
	inline mdl :: Assertion*
	Assertions :: getAxiom (const index :: Assertion i) {
		return axiomVector_.getValue (i);
	}
	inline mdl :: Assertion*
	Assertions :: getDefinition (const index :: Assertion i) {
		return definitionVector_.getValue (i);
	}
	inline mdl :: Assertion*
	Assertions :: getTheorem (const index :: Assertion i) {
		return theoremVector_.getValue (i);
	}
	inline mdl :: Assertion*
	Assertions :: getProblem (const index :: Assertion i) {
		return problemVector_.getValue (i);
	}

	inline index :: Assertion
	Assertions :: getAxiomNumber() const {
		return axiomVector_.getSize();
	}
	inline index :: Assertion
	Assertions :: getDefinitionNumber() const {
		return definitionVector_.getSize();
	}
	inline index :: Assertion
	Assertions :: getTheoremNumber() const {
		return theoremVector_.getSize();
	}
	inline index :: Assertion
	Assertions :: getProblemNumber() const {
		return problemVector_.getSize();
	}
	inline index :: Assertion
	Assertions :: getAxiomaticNumber() const {
		return getAxiomNumber() + getDefinitionNumber();
	}
	inline index :: Assertion
	Assertions :: getProvableNumber() const {
		return getTheoremNumber() + getProblemNumber();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;
	
	// object :: Object implementation
	void
	Assertions :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertions :: getVolume() const
	{
		Size_t volume = 0;
		volume += Container_ :: getVolume();
		volume += axiomVector_.getVolume();
		volume += definitionVector_.getVolume();
		volume += theoremVector_.getVolume();
		volume += problemVector_.getVolume();
		return volume;
	}
	Size_t
	Assertions :: getSizeOf() const {
		return sizeof (Assertions);
	}
	void
	Assertions :: show (String& string) const
	{
		string << tab << "axioms: " << tab << axiomVector_.getSize() << endLine;
		string << tab << "definitions: " << tab << definitionVector_.getSize() << endLine;
		string << tab << "theorems: " << tab << theoremVector_.getSize() << endLine;
		string << tab << "problems: " << tab << problemVector_.getSize() << endLine;
	}
}
}

#endif /*MDL_MATH_ASSERTIONS_CPP_*/

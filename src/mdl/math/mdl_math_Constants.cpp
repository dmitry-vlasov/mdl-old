/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Constants.cpp                                   */
/* Description:     global container for constants                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_CONSTANTS_CPP_
#define MDL_MATH_CONSTANTS_CPP_

#include "mdl/auxiliary/mdl_auxiliary.hpp"
#include "mdl/math/mdl_math_Constants.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constants :: Constants () :
	Ancestor_ (INITIAL_CONSTANT_VECTOR_CAPACITY),
	constantSet_ (INITIAL_CONSTANT_VECTOR_CAPACITY),
	mutex_ () {
		 pthread_mutex_init (&mutex_, NULL);
	}
	Constants :: ~ Constants () {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	inline mdl :: Constant*
	Constants :: get (const index :: Constant index) {
		return Ancestor_ :: getForm (index);
	}
	index :: Constant
	Constants :: add (mdl :: Constant* constant)
	{
		pthread_mutex_lock (&mutex_);
		for (index :: Literal i = 0; i < constant->getSize(); ++ i) {
			const value :: Literal
				literal = constant->getValue (i);
			if (contain (literal)) {
				Error* error = new Error (Error :: SEMANTIC, "constant is already defined.\n");
				error->message() << tab << "literal:" << space << Table :: literals()->get (literal) << endLine;
				pthread_mutex_unlock (&mutex_);
				throw error;
			} else {
				constantSet_.add (literal);
			}
		}
		const index :: Constant result = Ancestor_ :: addForm (constant);
		pthread_mutex_unlock (&mutex_);
		return result;
	}
	inline bool
	Constants :: contain (const value :: Literal literal) {
		const index :: Constant
			index = constantSet_.find (literal);
		return (index != index :: undefined :: CONSTANT);
	}

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const
	{
		Size_t volume = 0;
		volume += constantSet_.getVolume();
		volume += Ancestor_ :: getVolume();
		return volume;
	}
	Size_t
	Constants :: getSizeOf() const {
		return sizeof (Constants);
	}
	void
	Constants :: show (String& string) const {
		string << tab << "constants:     " << tab;
		string << constantSet_.getSize() << endLine;
	}
}
}

#endif /*MDL_MATH_CONSTANTS_HPP_*/

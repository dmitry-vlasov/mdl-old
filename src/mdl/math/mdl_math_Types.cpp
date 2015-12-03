/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Types.cpp                                       */
/* Description:     global container for types                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_TYPES_CPP_
#define MDL_MATH_TYPES_CPP_

#include "mdl/math/mdl_math_Types.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Types :: Types () :
	Container_ (INITIAL_TYPE_VECTOR_CAPACITY),
	rootTypes_ (INITIAL_ROOT_TYPES_CAPACITY),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Types :: ~ Types() {
	}

	inline mdl :: Type*
	Types :: get (const index :: Type index) {
		return Container_ :: getForm (index);
	}
	index :: Type
	Types :: add (mdl :: Type* type)
	{
		pthread_mutex_lock (&mutex_);
		if (type->getSuperCount() == 0) {
			rootTypes_.add (type);
		}
		const index :: Type result = Container_ :: addForm (type);
		pthread_mutex_unlock (&mutex_);
		return result;
	}

	void
	Types :: mine() const
	{
		String mineOutput (INITIAL_MINE_OUTPUT_CAPACITY);
		mineOutput << "<!DOCTYPE russell_mining_output>" << endLine;
		mineOutput << "<type_system>" << endLine;
		for (value :: Integer i = 0; i < rootTypes_.getSize(); ++ i) {
			const mdl :: Type* const
				type = rootTypes_.getValue (i);
			type->mine (mineOutput, 1);
		}
		mineOutput << "</type_system>" << endLine;
		std :: cout << mineOutput << std :: endl;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Types :: commitSuicide() {
		delete this;
	}
	Size_t
	Types :: getVolume() const
	{
		Size_t volume = 0;
		volume += Container_ :: getVolume();
		volume += rootTypes_.getVolume();
		return volume;
	}
	Size_t
	Types :: getSizeOf() const {
		return sizeof (Types);
	}
	void
	Types :: show (String& string) const {
		string << tab << "types:       " << tab;
		Container_ :: show (string);
	}
}
}

#endif /*MDL_MATH_TYPES_CPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Rules.cpp                                       */
/* Description:     global container for syntactic grammar rules             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math_Rules.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Rules :: Rules () :
	Ancestor_ (INITIAL_RULE_VECTOR_CAPACITY),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Rules :: ~ Rules () {
	}

	inline mdl :: Rule*
	Rules :: get (const index :: Rule index) {
		return Ancestor_ :: getForm (index);
	}
	inline index :: Rule
	Rules :: add (mdl :: Rule* rule)
	{
		pthread_mutex_lock (&mutex_);
		const index :: Rule result = Ancestor_ :: addForm (rule);
		pthread_mutex_unlock (&mutex_);
		return result;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Rules :: commitSuicide() {
		delete this;
	}
	Size_t
	Rules :: getVolume() const  {
		return Ancestor_ :: getVolume();
	}
	Size_t
	Rules :: getSizeOf() const {
		return sizeof (Rules);
	}
	void
	Rules :: show (String& string) const {
		string << tab << "rules:       " << tab;
		Ancestor_ :: show (string);
	}
}
}



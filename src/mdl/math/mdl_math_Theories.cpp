/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Theories.cpp                                    */
/* Description:     global container for theories                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/mdl_form.hpp"
#include "mdl/math/mdl_math_Theories.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theories :: Theories () :
	Ancestor_ (INITIAL_THEORY_VECTOR_CAPACITY),
	root_ (new form :: Theory()),
	mutex_ ()
	{
		pthread_mutex_init (&mutex_, NULL);
		add (root_);
	}
	Theories :: ~ Theories () {
		deleteAggregateObject (root_);
	}

	inline mdl :: Theory*
	Theories :: get (const index :: Theory index) {
		return Ancestor_ :: getForm (index);
	}
	inline index :: Theory
	Theories :: add (mdl :: Theory* theory)
	{
		pthread_mutex_lock (&mutex_);
		const index :: Theory result = Ancestor_ :: addForm (theory);
		pthread_mutex_unlock (&mutex_);
		return result;
	}
	inline mdl :: Theory*
	Theories :: getRoot () {
		return root_;
	}

	void
	Theories :: mine() const
	{
		String mineOutput (INITIAL_MINE_OUTPUT_CAPACITY);
		mineOutput << "<!DOCTYPE russell_mining_output>" << endLine;
		mineOutput << "<structure>" << endLine;
		root_->mine (mineOutput);
		mineOutput << "</structure>" << endLine;
		std :: cout << mineOutput << std :: endl;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Theories :: commitSuicide() {
		delete this;
	}
	Size_t
	Theories :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += getAggregateVolume (root_);
		return volume;
	}
	Size_t
	Theories :: getSizeOf() const {
		return sizeof (Theories);
	}
	void
	Theories :: show (String& string) const
	{
		string << tab << "theories:      " << tab;
		string << Ancestor_ :: formVector_.getSize() - 1 << endLine;
	}
}
}



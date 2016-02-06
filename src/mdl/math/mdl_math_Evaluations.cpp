/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Evaluations.hpp                                 */
/* Description:     global container for evaluations                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Evaluations :: Evaluations () :
	evaluationVector_ (INITIAL_EVALUATION_VECTOR_CAPACITY),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Evaluations :: ~ Evaluations () {
	}

	inline index :: Assertion
	Evaluations :: getSize() const {
		return evaluationVector_.getSize();
	}
	inline mdl :: Evaluation*
	Evaluations :: get (const index :: Assertion index) {
		return evaluationVector_.getValue (index);
	}
	inline index :: Assertion
	Evaluations :: add (mdl :: Evaluation* proposition)
	{
		pthread_mutex_lock (&mutex_);
		const index :: Assertion index = evaluationVector_.getSize();
		evaluationVector_.add (proposition);
		pthread_mutex_unlock (&mutex_);
		return index;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;
	
	// object :: Object implementation
	void
	Evaluations :: commitSuicide() {
		delete this;
	}
	Size_t
	Evaluations :: getVolume() const
	{
		Size_t volume = 0;
		volume += evaluationVector_.getVolume();
		return volume;
	}
	Size_t
	Evaluations :: getSizeOf() const {
		return sizeof (Evaluations);
	}
	void
	Evaluations :: show (String& string) const {
		string << tab << "evaluations: " << tab << evaluationVector_.getSize() << endLine;
	}
}
}



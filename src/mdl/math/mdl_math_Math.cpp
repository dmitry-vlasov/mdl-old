/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Math.cpp                                        */
/* Description:     all global containers for mdl language                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_MATH_CPP_
#define MDL_MATH_MATH_CPP_

#include "mdl/math/mdl_math.hpp"

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline Assertions*
	Math :: assertions() {
		return assertions_;
	}
	inline Constants*
	Math :: constants() {
		return constants_;
	}
	inline Defiendums*
	Math :: defiendums() {
		return defiendums_;
	}
	inline Expressions*
	Math :: expressions() {
		return expressions_;
	}
	inline Evaluations*
	Math :: evaluations() {
		return evaluations_;
	}
	inline Proofs*
	Math :: proofs() {
		return proofs_;
	}
	inline Propositions*
	Math :: propositions() {
		return propositions_;
	}
	inline Rules*
	Math :: rules() {
		return rules_;
	}
	inline Statistics*
	Math :: statistics() {
		return statistics_;
	}
	inline Theories*
	Math :: theories () {
		return theories_;
	}
	inline Types*
	Math :: types() {
		return types_;
	}

	void
	Math :: clear()
	{
		release();
		init();
	}
	template<class S>
	void
	Math :: show (S& os)
	{
		enum {
			INITIAL_STRING_CAPACITY = 256
		};
		if (message_ == NULL) {
			message_ = new String (INITIAL_STRING_CAPACITY);
		} else {
			message_->clear();
		}
		show (*message_);
		os << *message_;
	}

using manipulator :: endLine;
	
	// nstd :: Static implementation
	void
	Math :: init()
	{
		if (assertions_ != NULL) {
			return;
		}
		assertions_   = new Assertions();
		constants_    = new Constants();
		defiendums_   = new Defiendums();
		expressions_  = new Expressions();
		evaluations_  = new Evaluations();
		proofs_       = new Proofs();
		propositions_ = new Propositions();
		rules_        = new Rules();
		statistics_   = new Statistics();
		theories_     = new Theories();
		types_        = new Types();
	}
	void
	Math :: release()
	{
		deleteAggregateObject (assertions_);
		deleteAggregateObject (constants_);
		deleteAggregateObject (defiendums_);
		deleteAggregateObject (expressions_);
		deleteAggregateObject (evaluations_);
		deleteAggregateObject (proofs_);
		deleteAggregateObject (propositions_);
		deleteAggregateObject (rules_);
		deleteAggregateObject (statistics_);
		deleteAggregateObject (theories_);
		deleteAggregateObject (types_);
		deleteAggregateObject (message_);
	}
	void
	Math :: show (String& string)
	{
		if (isInitialized()) {
			string << "math:" << endLine;
			string << "-------------------------" << endLine;
			string << *constants_;
			string << *rules_;
			string << *theories_;
			string << *types_;
			string << *defiendums_;
			//string << *expressions_;
			string << *evaluations_;
			string << *proofs_;
			string << *propositions_;
			string << *assertions_;
			string << endLine;
			string << *statistics_;
		}
	}
	Size_t
	Math :: getVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (assertions_);
		result += getAggregateVolume (constants_);
		result += getAggregateVolume (defiendums_);
		result += getAggregateVolume (expressions_);
		result += getAggregateVolume (evaluations_);
		result += getAggregateVolume (proofs_);
		result += getAggregateVolume (propositions_);
		result += getAggregateVolume (rules_);
		result += getAggregateVolume (statistics_);
		result += getAggregateVolume (theories_);
		result += getAggregateVolume (types_);
		result += getAggregateVolume (message_);
		return result;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/
	
	Assertions* 
		Math :: assertions_ = NULL;
	Constants* 
		Math :: constants_ = NULL;
	Defiendums*
		Math :: defiendums_ = NULL;
	Expressions*
		Math :: expressions_ = NULL;
	Evaluations*
		Math :: evaluations_ = NULL;
	Proofs*
		Math :: proofs_ = NULL;
	Propositions*
		Math :: propositions_ = NULL;
	Rules* 
		Math :: rules_ = NULL;
	Statistics*
		Math :: statistics_ = NULL;
	Theories* 
		Math :: theories_ = NULL;
	Types* 
		Math :: types_ = NULL;

	String*
		Math :: message_ = NULL;
}
}

#endif /*MDL_MATH_MATH_CPP_*/

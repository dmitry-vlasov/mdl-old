/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_function_Function.cpp                */
/* Description:     evaluation function for proposition                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_FUNCTION_FUNCTION_CPP_
#define MDL_FORM_EVALUATION_FUNCTION_FUNCTION_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace function {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Function :: Function
	(
		index :: Arity index,
		const mdl :: Proposition* proposition,
		mdl :: Evaluation* evaluation
	) :
	location_ (Indent (2)),
	index_ (index),
	term_ (NULL),

	evaluation_ (evaluation),
	proposition_ (dynamic_cast<const form :: header :: statement :: Proposition*>(proposition)) {
	}
	inline
	Function :: Function
	(
		const Location& location,
		index :: Arity index,
		Term_* term,
		mdl :: Theory* theory
	) :
	location_ (location),
	index_ (index),
	term_ (term),

	evaluation_ (NULL),
	proposition_ (NULL) {
		term_->setDepth();
	}
	Function :: ~ Function() {
		deleteAggregateObject (term_);
	}

	void
	Function :: setEvaluation (mdl :: Evaluation* evaluation) {
		evaluation_ = evaluation;
	}
	void
	Function :: setAssertion (const mdl :: Assertion* assertion)
	{
		proposition_ = dynamic_cast<const form :: header :: statement :: Proposition*>
			(assertion->getProposition (index_));
		const_cast<form :: header :: statement :: Proposition*>(proposition_)->addEvaluationFunction (this);
		term_->setProposition (proposition_);
	}

	// evaluation :: Term implementation
	Function :: Term_*
	Function :: getTerm() {
		return term_;
	}
	const Function :: Term_*
	Function :: getTerm() const {
		return term_;
	}
	mdl :: Evaluation*
	Function :: getEvaluation() {
		return evaluation_;
	}
	const mdl :: Evaluation*
	Function :: getEvaluation() const {
		return evaluation_;
	}

	// object :: Buildable implementation
	void
	Function :: build() {
		term_->build();
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Function :: translate (String&) const {
	}
	void
	Function :: replicate (String& string) const
	{
		/*
		 * Example:
		  prop 2 =
		  sum [0.2]
		  (
		      mult [0.2] (sub_cplx ()),
		      mult [0.4] (exp_cplx ()),
		      mult [0.2] (forking [15] ()),
		      mult [1.0] (const [0] ()) // trivial FRiS - NO
		  )
		 */
		string << location_.getIndent() << Token :: prop_ << space;
		string << (index_ + 1) << space << Token :: equality_ << endLine;
		term_->replicate (string);
	}

	// object :: Object implementation
	void
	Function :: commitSuicide() {
		delete this;
	}
	Size_t
	Function :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (term_);
		return volume;
	}
	Size_t
	Function :: getSizeOf() const {
		return sizeof (Function);
	}
	void
	Function :: show (String& string) const {
		replicate (string);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_FUNCTION_FUNCTION_CPP_*/

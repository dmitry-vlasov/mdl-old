/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Lexp.cpp                        */
/* Description:     FRiS evaluation function                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_FRIS_CPP_
#define MDL_FORM_EVALUATION_TERM_FRIS_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Lexp :: Lexp () :
	Term_(),
	location_ (),
	theory_ (NULL),
	caseVector_ (INITIAL_CASE_VECTOR_CAPACITY),
	fris_ (NULL) {
	}
	inline
	Lexp :: Lexp (const bool sign) :
	Term_(),
	location_ (),
	theory_ (NULL),
	caseVector_ (INITIAL_CASE_VECTOR_CAPACITY),
	fris_ (new Fris_ (sign)) {
	}
	inline
	Lexp :: Lexp
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	Term_(),
	location_ (location),
	theory_ (theory),
	caseVector_ (INITIAL_CASE_VECTOR_CAPACITY),
	fris_ (NULL) {
	}
	Lexp :: ~ Lexp() {
		deleteAggregateObject (fris_);
	}

	void
	Lexp :: addCase (mdl :: evaluation :: Case* _case) {
		caseVector_.add (_case);
	}
	void
	Lexp :: setConst (const bool sign)
	{
		deleteAggregateObject (fris_);
		fris_ = new Fris_ (sign);
		++ version_;
	}
	void
	Lexp :: setFris (Fris_* fris)
	{
		deleteAggregateObject (fris_);
		fris_ = fris;
		clearCaseVector();
		if (!fris_->isConst()) {
			initCaseVector();
		}
		++ version_;
	}

	// evaluation :: Term implementation
	value :: Real
	Lexp :: eval (const HeapNode_* node) const
	{
		value :: Real value = fris_->classify (node);
		return value;
	}

	// object :: Buildable implementation
	void
	Lexp :: build()
	{
		for (value :: Integer i = 0; i < caseVector_.getSize(); ++ i) {
			mdl :: evaluation :: Case* _case = caseVector_ [i];
			_case->build();
		}
		if (fris_ == NULL) {
			fris_ = new Fris_ (caseVector_);
		}
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Lexp :: replicate (String& string) const
	{
		/* Example:
		 *
		 lexp
		 [
			+ theorem xxx proof pr1 step 8
			+ theorem xxx.yyy.zzz proof pr1 step (15.23.4)
			- theorem xxx.yyy proof prf2 step (28.5)
			- theorem zzz.yyy proof 3 step 7
		 ] ()
		 */
		string << Indent (depth_ + 2) << Token :: lexp_ << space;
		if (fris_->isConst()) {
			string << Token :: openSqBracket_;
			string << (fris_->getSign() ? Token :: plus_ : Token :: minus_ );
			string << Token :: closeSqBracket_;
			string <<  Token :: openBracket_ << Token :: closeBracket_;
		} else {
			string << endLine << Indent (depth_ + 2);
			string << Token :: openSqBracket_ << endLine;

			for (value :: Integer i = 0; i < caseVector_.getSize(); ++ i) {
				string << Indent (depth_ + 3);
				const mdl :: evaluation :: Case* _case = caseVector_ [i];
				_case->replicate (string);
				string << endLine;
			}
			string << Indent (depth_ + 2) << Token :: closeSqBracket_;
			string <<  Token :: openBracket_ << Token :: closeBracket_;
		}
	}

	// object :: Object implementation
	void
	Lexp :: commitSuicide() {
		delete this;
	}
	Size_t
	Lexp :: getVolume() const
	{
		Size_t volume = 0;
		volume += caseVector_.getVolume();
		volume += getAggregateVolume (fris_);
		return volume;
	}
	Size_t
	Lexp :: getSizeOf() const {
		return sizeof (Lexp);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Lexp :: clearCaseVector()
	{
		for (value :: Integer i = 0; i < caseVector_.getSize(); ++ i) {
			mdl :: evaluation :: Case*& _case = caseVector_.getReference (i);
			_case->commitSuicide();
			_case = NULL;
		}
		caseVector_.clear();
	}
	void
	Lexp :: initCaseVector()
	{
		for (value :: Integer i = 0; i < fris_->getVector()->getSize(); ++ i) {
			mdl :: evaluation :: Case*
				_case = fris_->getVector()->getPoint (i)->createCase();
			caseVector_.add (_case);
		}
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_FRIS_CPP_*/

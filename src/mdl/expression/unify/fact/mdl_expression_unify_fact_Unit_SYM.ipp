/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unit_SYM.ipp                   */
/* Description:     pair of iterators for the symmetric unification algorithm*/
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_FACT_UNIT_SYM_IPP_
#define MDL_EXPRESSION_UNIFY_FACT_UNIT_SYM_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step level_1,
		const index :: Step level_2
	) :
	Pair_ (iterator_1, iterator_2),
	level_1_ (level_1),
	level_2_ (level_2),
	difference_1_ (0),
	difference_2_ (0),
	minDifference_1_ (minDifference_1),
	minDifference_2_ (minDifference_2) {
	}
	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step level_1,
		const index :: Step level_2,
		const value :: Integer difference_1,
		const value :: Integer difference_2
	) :
	Pair_ (iterator_1, iterator_2),
	level_1_ (level_1),
	level_2_ (level_2),
	difference_1_ (difference_1),
	difference_2_ (difference_2),
	minDifference_1_ (minDifference_1),
	minDifference_2_ (minDifference_2) {
	}
	template<class T_1, class T_2, int K>
	inline
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Unit (const Unit& unit) :
	Pair_ (unit),
	level_1_ (unit.level_1_),
	level_2_ (unit.level_2_),
	difference_1_ (unit.difference_1_),
	difference_2_ (unit.difference_2_),
	minDifference_1_ (unit.minDifference_1_),
	minDifference_2_ (unit.minDifference_2_) {
	}

	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: InverseUnit_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: inverse () const
	{
		return InverseUnit_
		(
			Pair_ :: getSecond(),
			Pair_ :: getFirst(),
			minDifference_2_,
			minDifference_1_,
			level_2_,
			level_1_,
			difference_2_,
			difference_1_
		);
	}

	template<class T_1, class T_2, int K>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: updateMinDifference() const
	{
		if ((minDifference_1_ == value :: undefined :: INTEGER) ||
			(minDifference_1_ > difference_1_)) {
			minDifference_1_ = difference_1_;
		}
		if ((minDifference_2_ == value :: undefined :: INTEGER) ||
			(minDifference_2_ > difference_2_)) {
			minDifference_2_ = difference_2_;
		}
		//swapMinDifference();
	}
	template<class T_1, class T_2, int K>
	inline value :: Integer
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getSourceDifference() const {
		return difference_1_;
	}
	template<class T_1, class T_2, int K>
	inline value :: Integer
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getTargetDifference() const {
		return difference_2_;
	}
	/*template<class T_1, class T_2, int K>
	inline value :: Integer
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getMinSourceDifference() {
		return minDifference_1_;
	}
	template<class T_1, class T_2, int K>
	inline value :: Integer
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getMinTargetDifference() {
		return minDifference_2_;
	}
	template<class T_1, class T_2, int K>
	inline value :: Integer
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getMinDifference() {
		return (minDifference_1_ + minDifference_2_);
	}*/

	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: isReacheable() const
	{
		return
			Pair_ :: getFirst()->isReacheable (level_1_) &&
			Pair_ :: getSecond()->isReacheable (level_2_);
	}
	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: isFixed() const
	{
		return
			Pair_ :: getFirst()->isFixed() &&
			Pair_ :: getSecond()->isFixed();
	}

	template<class T_1, class T_2, int K>
	bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: shift
	(
		const Term_1_* const term_1,
		const Term_2_* const term_2
	)
	{
		if (!checkTermTypes (term_1, term_2)) {
			return false;
		}
		Pair_ :: first() = term_1->getEnd();
		Pair_ :: second() = term_2->getEnd();
		if (!term_1->isReplaceable()) {
			difference_1_ += term_1->getComplexity();
		}
		if (!term_2->isReplaceable()) {
			difference_2_ += term_2->getComplexity();
		}
		if ((difference_1_ >= minDifference_1_) ||
			(difference_2_ >= minDifference_2_)) {
			return false;
		}
		return true;
	}

	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_1_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getSource() const {
		return Pair_ :: getFirst();
	}
	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_2_
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: getTarget() const {
		return Pair_ :: getSecond();
	}
		template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_1_&
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: source() {
		return Pair_ :: first();

	}
	template<class T_1, class T_2, int K>
	inline typename Unit<T_1, T_2, policy :: SYMMETRIC, K> :: Iterator_2_&
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: target() {
		return Pair_ :: second();
	}

using manipulator :: endLine;
using manipulator :: iterate;

	template<class T_1, class T_2, int K>
	void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show (String& string) const
	{
		string << "source node: " << endLine;
		Pair_ :: getFirst()->showBack (string);
		string << endLine;
		string << "source difference: " << difference_1_ << endLine;

		string << "target node: " << endLine;
		Pair_ :: getSecond()->showBack (string);
		string << endLine;
		string << "target difference: " << difference_2_ << endLine;
	}
	template<class T_1, class T_2, int K>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show (std :: ostream& os) const
	{
		String string (1024);
		show (string);
		os << string;
	}
	template<class T_1, class T_2, int K>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show () const	{
		show (std :: cout);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T_1, class T_2, int K>
	template<class T1, class T2>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: show
	(
		String& string,
		const T1* term,
		const T2* expression,
		const char* label
	) const
	{
		string << "term " << label << ":" << endLine;
		string << *term << endLine;
		string << "result " << label << ":" << endLine;
		string << *expression << endLine;
		//string << "subterms " << label << ":" << endLine;
		//expression->showTerms (string); string << endLine;
		string << endLine;
		//string << iterate << 5 << endLine;
	}

	template<class T_1, class T_2, int K>
	inline bool
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: checkTermTypes
	(
		const Term_1_* const term_1,
		const Term_2_* const term_2
	) const
	{
		const mdl :: Type* const
			termType_1 = term_1->getType();
		const mdl :: Type* const
			termType_2 = term_2->getType();
		return termType_2->isSuper (termType_1);
	}
	/*template<class T_1, class T_2, int K>
	inline void
	Unit<T_1, T_2, policy :: SYMMETRIC, K> :: swapMinDifference()
	{
		const value :: Integer minDifference_1 = minDifference_1_;
		InverseUnit_ :: minDifference_1_ = minDifference_2_;
		InverseUnit_ :: minDifference_2_ = minDifference_1;
	}*/

	/********************************
	 *		Private static members
	 ********************************/

	/*template<class T_1, class T_2, int K>
	value :: Integer
		Unit<T_1, T_2, policy :: SYMMETRIC, K> :: minDifference_1_ = value :: undefined :: INTEGER;
	template<class T_1, class T_2, int K>
	value :: Integer
		Unit<T_1, T_2, policy :: SYMMETRIC, K> :: minDifference_2_ = value :: undefined :: INTEGER;*/

	/*******************************
	 *		Overloaded operators
	 *******************************/

	template<class T_1, class T_2, int K>
	String&
	operator << (String& string, const Unit<T_1, T_2, policy :: SYMMETRIC, K>& unit)
	{
		unit.show (string);
		return string;
	}
	template<class T_1, class T_2, int K>
	std :: ostream&
	operator << (std :: ostream& os, const Unit<T_1, T_2, policy :: SYMMETRIC, K>& unit)
	{
		unit.show (os);
		return os;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_FACT_UNIT_SYM_IPP_*/

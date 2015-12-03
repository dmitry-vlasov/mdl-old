/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Vector.ipp                 */
/* Description:     most general  vector unifier module                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_PROD_VECTOR_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_PROD_VECTOR_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

	/****************************
	 *		Public members
	 ****************************/

	template<class M, class E, int P, int K, class A>
	Vector<M, E, P, K, A> :: Vector
	(
		const Matrix_* matrix,
		const index :: Arity dimension,
		Substitution_*& delta,
		Substitution_*& epsilon
	) :
	matrix_ (matrix),
	dimension_ (dimension),
	delta_ (delta),
	epsilon_ (epsilon),
	exprevector_ (NULL),
	itervector_ (dimension_),
	diffvector_ (dimension_) {
	}

	template<class M, class E, int P, int K, class A>
	inline bool
	Vector<M, E, P, K, A> :: unify (const Exprevector_* expressions)
	{
		exprevector_ = expressions;
		epsilon_ = NULL;
		while (true) {
			calculateDifference();
			if (diffvector_.getSize() == 0) {
				return true;
			}
			const Substiunit_*
			unit = findUnit();
			if (!useUnit (unit)) {
				return false;
			}
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	template<class M, class E, int P, int K, class A>
	void
	Vector<M, E, P, K, A> :: show (String& string) const
	{
		Mode mode (string);
		Mode m (mode);
		m << Mode :: SHOW_REPLACEABILITY;
		string << m;

		//string << "dimension_ = " << dimension_ << endLine;
		string << "exprevector_ = " << endLine;
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			const Expression_* expression = exprevector_->getValue (i);
			if (expression == NULL) {
				string << tab << "NULL" << endLine;
			} else {
				string << tab << *expression << endLine;
			}
		}
		string << "epsilon_ = ";
		if (epsilon_ == NULL) {
			string << "NULL" << endLine;
		} else {
			string << *epsilon_;
		}
		string << "delta_ = ";
		if (delta_ == NULL) {
			string << "NULL" << endLine;
		} else {
			string << *delta_;
		}
		string << "itervector_ = " << endLine;
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			Iterator_ iterator = itervector_.getValue (i);
			if (iterator.isNull()) {
				string << tab << "NULL" << endLine;
			} else {
				string << tab << *iterator << endLine;
			}
		}
		string << "diffvector_ = " << endLine;
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			const Term_* term = diffvector_.getValue (i);
			if (term == NULL) {
				string << tab << "NULL" << endLine;
			} else {
				string << tab << *term << endLine;
			}
		}
		string << mode;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class M, class E, int P, int K, class A>
	void
	Vector<M, E, P, K, A> :: calculateDifference()
	{
		diffvector_.clear();
		initItervector();
		while (true) {
			if (hasDifference()) {
				buildDifference();
				return;
			}
			if (!incItervector()) {
				return;
			}
		}
	}
	template<class M, class E, int P, int K, class A>
	inline bool
	Vector<M, E, P, K, A> :: initItervector()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			Iterator_&
				iterator = itervector_.getReference (i);
			const Expression_* const
				expression = exprevector_->getValue (i);
			if (expression != NULL) {
				#ifdef DEBUG
				expression->verifyIntegrity();
				#endif
				iterator = expression->getBegin();
			} else {
				iterator = Iterator_();
			}
		}
		return true;
	}
	template<class M, class E, int P, int K, class A>
	inline bool
	Vector<M, E, P, K, A> :: incItervector()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			Iterator_& iterator = itervector_.getReference (i);
			if (!iterator.isNull()) {
				++ iterator;
				if (iterator.isNull()) {
					return false;
				}
			}
		}
		return true;
	}
	template<class M, class E, int P, int K, class A>
	inline bool
	Vector<M, E, P, K, A> :: hasDifference() const
	{
		index :: Arity d = dimension_;
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			if (!itervector_.getValue(i).isNull()) {
				d = i;
				break;
			}
		}
		if (d == dimension_) {
			return false;
		}
		const Iterator_
			first = itervector_.getValue (d);
		for (index :: Arity i = d + 1; i < dimension_; ++ i) {
			const Iterator_
				arbitrary = itervector_.getValue (i);
			if (!arbitrary.isNull() && !(*first == *arbitrary)) {
				return true;
			}
		}
		return false;
	}
	template<class M, class E, int P, int K, class A>
	void
	Vector<M, E, P, K, A> :: buildDifference()
	{
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			const Iterator_ iterator = itervector_.getValue (i);
			if (!iterator.isNull()) {
				const Term_* const
					term = iterator->getTerms().getInitial().getTerm();
				#ifdef DEBUG
				if (term != NULL) {
					term->verifyIntegrity();
				}
				#endif
				diffvector_.add (term);
			} else {
				diffvector_.add (NULL);
			}
		}
	}

	template<class M, class E, int P, int K, class A>
	const typename Vector<M, E, P, K, A> :: Substiunit_*
	Vector<M, E, P, K, A> :: findUnit () const
	{
		const Substiunit_* unit = NULL;
		for (index :: Arity i = 0; i < dimension_ - 1; ++ i) {
			for (index :: Arity j = i + 1; j < dimension_; ++ j) {
				const bool
					isAdmited = Unit_ :: admit
					(
						diffvector_.getValue (i),
						diffvector_.getValue (j)
					);
				if (!isAdmited) {
					return NULL;
				}
				unit = Unit_ :: check
				(
					diffvector_.getValue (i),
					diffvector_.getValue (j)
				);
				if (unit != NULL) {
					return unit;
				}
			}
		}
		return NULL;
	}
	template<class M, class E, int P, int K, class A>
	bool
	Vector<M, E, P, K, A> :: useUnit (const Substiunit_* unit)
	{
		if (unit == NULL) {
			return false;
		}
		const Substitution_* const
			tau = new Substitution_ (unit->getVariable(), unit->getTerm(), NULL, true);
		delete unit;
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			Expression_* const
				expression = exprevector_->getValue (i);
			if (expression != NULL) {
				#ifdef DEBUG
				expression->verifyIntegrity();
				#endif
				expression->execute (epsilon_);
				#ifdef DEBUG
				expression->verifyIntegrity();
				#endif
				epsilon_ = epsilon_->compose (tau);
				delta_ = delta_->compose (tau);
			}
		}
		return true;
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class M, class E, int P, int K, class A>
	inline String&
	operator << (String& string, const Vector<M, E, P, K, A>& vector)
	{
		vector.show (string);
		return string;
	}
	template<class M, class E, int P, int K, class A>
	inline std :: ostream&
	operator << (std :: ostream& os, const Vector<M, E, P, K, A>& vector)
	{
		String str (1024);
		return os << (str << vector);
	}
}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_PROD_VECTOR_IPP_*/

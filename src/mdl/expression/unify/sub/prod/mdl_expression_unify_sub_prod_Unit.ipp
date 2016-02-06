/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Unit.ipp                   */
/* Description:     unit testing template class for vector unifier           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

	/****************************
	 *		Public members
	 ****************************/

	template<class E, class S, int P, int K>
	inline bool
	Unit<E, S, P, K> :: admit (const Term_* const, const Term_* const) {
		return true;
	}
	template<class E, class S, int K>
	inline bool
	Unit<E, S, policy :: DIRECT, K> :: admit
	(
		const Term_* const first,
		const Term_* const second
	)
	{
		if ((first == NULL) || (second == NULL)) {
			return false;
		}
		const bool
			firstIsReplaceable = first->isReplaceable();
		const bool
			secondIsReplaceable = second->isReplaceable();
		return (firstIsReplaceable || !secondIsReplaceable);
	}
	template<class E, class S, int K>
	inline bool
	Unit<E, S, policy :: INVERSE, K> :: admit
	(
		const Term_* const first,
		const Term_* const second
	)
	{
		if ((first == NULL) || (second == NULL)) {
			return false;
		}
		const bool
			firstIsReplaceable = first->isReplaceable();
		const bool
			secondIsReplaceable = second->isReplaceable();
		return (!firstIsReplaceable || secondIsReplaceable);
	}
	template<class E, class S, int P, int K>
	inline const typename Unit<E, S, P, K> :: Substiunit_*
	Unit<E, S, P, K> :: check
	(
		const Term_* const first,
		const Term_* const second
	)
	{
		const Substiunit_*
			unit = NULL;
		unit = make (first, second);
		if (unit != NULL) {
			return unit;
		}
		unit = make (second, first);
		if (unit != NULL) {
			return unit;
		}
		return NULL;
	}
	template<class E, class S, int K>
	inline const typename Unit<E, S, policy :: DIRECT, K> :: Substiunit_*
	Unit<E, S, policy :: DIRECT, K> :: check
	(
		const Term_* const first,
		const Term_* const second
	) {
		return make (first, second);
	}
	template<class E, class S, int K>
	inline const typename Unit<E, S, policy :: INVERSE, K> :: Substiunit_*
	Unit<E, S, policy :: INVERSE, K> :: check
	(
		const Term_* const first,
		const Term_* const second
	) {
		return make (second, first);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class E, class S, int P, int K>
	inline const typename Unit<E, S, P, K> :: Substiunit_*
	Unit<E, S, P, K> :: make
	(
		const Term_* const variable,
		const Term_* const term
	)
	{
		if ((variable == NULL) || (term == NULL)) {
			return NULL;
		}
		#ifdef DEBUG
		variable->verifyIntegrity();
		term->verifyIntegrity();
		#endif
		if (!variable->isReplaceable()) {
			return NULL;
		}
		if ((static_cast<kind :: Type>(kind_) == kind :: PLAIN) &&
			(!term->isReplaceable())) {
			return NULL;
		}
		const Symbol&
			symbol = *(variable->getBegin());
		if (term->contains (symbol)) {
			return NULL;
		}
		const mdl :: Type* const
			varType = variable->getType();
		const mdl :: Type* const
			termType = term->getType();
		if (!varType->isSuper (termType)) {
			return NULL;
		}
		const Expression_* exp = Expression_ :: createList (term);
		return new Substiunit_ (symbol, exp->getTerm());
	}
	template<class E, class S, int K>
	inline const typename Unit<E, S, policy :: DIRECT, K> :: Substiunit_*
	Unit<E, S, policy :: DIRECT, K> :: make
	(
		const Term_* const variable,
		const Term_* const term
	) {
		return Unit<E, S, policy :: SYMMETRIC, K> :: make (variable, term);
	}
	template<class E, class S, int K>
	inline const typename Unit<E, S, policy :: INVERSE, K> :: Substiunit_*
	Unit<E, S, policy :: INVERSE, K> :: make
	(
		const Term_* const variable,
		const Term_* const term
	) {
		return Unit<E, S, policy :: SYMMETRIC, K> :: make (variable, term);
	}
}
}
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Builder.ipp                         */
/* Description:     expression building routines                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_BUILD_BUILDER_IPP_
#define MDL_EXPRESSION_BUILD_BUILDER_IPP_

namespace mdl {
namespace expression {
namespace build {

	/****************************
	 *		Public members
	 ****************************/

	template<class E, class T, class V>
	inline
	Builder<E, T, V> :: Builder
	(
		const Term_2_* source,
		Value_ value
	) :
	source_ (source),
	absoluteBegin_ (Switch_ :: beginSource (source)),
	absoluteEnd_ (Switch_ :: endSource (source)),
	value_ (value) {
	}

using manipulator :: endLine;
using manipulator :: iterate;

	template<class E, class T, class V>
	typename Builder<E, T, V> :: Term_1_*
	Builder<E, T, V> :: build (Expression_*   target)
	{
		Iterator_1_
			targetBegin = Switch_ :: startTarget (target);
		Iterator_2_
			sourceBegin = Switch_ :: startSource (source_);
		Iterator_1_
			targetEnd = targetBegin;
		Iterator_2_
			sourceEnd = sourceBegin;

		Node_ :: manage (target, targetBegin, sourceEnd, value_);

		Term_1_* const
			result = addNode
			(
				target,
				targetBegin,   targetEnd,
				sourceBegin,   sourceEnd,
				Switch_ :: getTerms (sourceEnd),
				false
			);

		#ifdef DEBUG
			result->verifyIntegrity();
			source->verifyIntegrity();
			if (!source->coinsides (*result)) {
				Error* error = new Error (Error :: SEMANTIC);
				error->message() << "builder error" << endLine;
				error->message() << "source: " << *source << endLine;
				source->showTerms (error->message());
				error->message() << endLine;
				error->message() << "target: " << *result << endLine;
				result->showTerms (error->message());
				//std :: cout << error->message();

				if (!source->coinsides (*result)) {
					std :: cout << error->message();
				}

				throw error;
			}
		#endif /*DEBUG*/

		return result;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class E, class T, class V>
	typename Builder<E, T, V> :: Term_1_*
	Builder<E, T, V> :: addNode
	(
		Expression_* const target,
		const Iterator_1_ targetBegin,   Iterator_1_& targetEnd,
		const Iterator_2_ sourceBegin,   Iterator_2_& sourceEnd,
		const Terms_2_& sourceTerms,
		const bool initial,
		const int depth
	)
	{
		Node_ :: manage (target, targetEnd, sourceEnd, value_);

		if (initial && !Switch_ :: getTerms (sourceEnd).isEmpty()) {
			addNode
			(
				target,
				targetEnd,     targetEnd,
				sourceEnd,     sourceEnd,
				Switch_ :: getTerms (sourceEnd),
				false,
				depth + 1
			);
		}
		Term_1_* targetTerm = NULL;
		const Term_2_* sourceTerm = NULL;
		buildTerms
		(
			targetBegin, targetEnd,
			sourceEnd, targetTerm,
			sourceTerm,
			sourceTerms,
			depth
		);
		if (sourceTerm != NULL &&
			!Switch_ :: end (sourceTerm, sourceEnd)) {
			Switch_ :: inc (targetEnd, sourceEnd);
			return addNode
			(
				target,
				targetBegin,   targetEnd,
				sourceBegin,   sourceEnd,
				sourceTerms,
				true,
				depth
			);
		} else {
			return targetTerm;
		}
	}

	template<class E, class T, class V>
	void
	Builder<E, T, V> :: buildTerms
	(
		Iterator_1_  targetBegin,
		Iterator_1_& targetEnd,
		Iterator_2_& sourceEnd,
		Term_1_*& targetTerm,
		const Term_2_*& sourceTerm,
		const Terms_2_& sourceTerms,
		const int depth
	)
	{
		typedef
			typename Terms_2_ :: Node_
			Node;
		const Node*
			node = sourceTerms.getFirst();
		while (node != NULL) {
			sourceTerm = node->getValue();
			if (Switch_ :: end (sourceTerm, sourceEnd)) {
				if (Switch_ :: end (sourceTerm, absoluteEnd_)) {
					targetTerm = Switch_ :: newTerm
						(
							targetBegin,
							targetEnd,
							(depth == 0) ? source_->getType() : sourceTerm->getType()
						);
					break;
				} else {
					targetTerm = Switch_ :: newTerm
						(
							targetBegin,
							targetEnd,
							sourceTerm->getType()
						);
				}
			}
			node = node->getNext();
		}
	}
}
}
}

#endif /*MDL_EXPRESSION_BUILD_BUILDER_IPP_*/

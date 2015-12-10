/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Constraints.hpp                      */
/* Description:     constraints on proof search tree                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_
#define MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	inline value :: Integer
	Constraints :: maxComplexity() const {
		return maxComplexity_;
	}
	inline value :: Integer
	Constraints :: maxHeight() const {
		return maxHeight_;
	}

	inline void
	Constraints :: setMaxComplexity() {
		if (Math :: statistics() != NULL) {
			maxComplexity_ = Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).getMax();
		}
	}
	inline void
	Constraints :: setMaxComplexity (value :: Integer maxComplexity) {
		maxComplexity_ = maxComplexity;
	}
	inline void
	Constraints :: setMaxHeight()
	{
		if (Prover :: get() != NULL) {
			if (Prover :: get()->getTree() != NULL) {
				maxHeight_ = Prover :: get()->getTree()->getHeight();
			}
		}
	}
	inline void
	Constraints :: setMaxHeight (value :: Integer maxHeight) {
		maxHeight_ = maxHeight;
	}

	Constraints&
	Constraints :: get() {
		static Constraints constraints;
		return constraints;
	}

	// object :: Object implementation
	void
	Constraints :: commitSuicide() {
		delete this;
	}
	Size_t
	Constraints :: getVolume() const {
		return 0;
	}
	Size_t
	Constraints :: getSizeOf() const {
		return sizeof (Constraints);
	}
	void
	Constraints :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	inline
	Constraints :: Constraints() :
	maxComplexity_ (value :: undefined :: INTEGER),
	maxHeight_ (value :: undefined :: INTEGER) {
	}
	inline
	Constraints :: ~ Constraints() {
	}
}
}
}


#endif /*MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_*/

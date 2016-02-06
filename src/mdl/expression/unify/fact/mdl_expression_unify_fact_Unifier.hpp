/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unifier.hpp                    */
/* Description:     main unification algorithm. Static class                 */
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
namespace fact {

template
<
	class U,
	class A = allocator :: Heap,
	int P = policy :: SYMMETRIC
>
class Unifier {
public :
	typedef U Unit_;
	typedef A Allocator_;
	enum { policy_ = P };
	typedef Result<Unit_, allocator :: Stack> Result_;
	typedef
		typename Unit_ :: Iterator_1_
		Iterator_1_;
	typedef
		typename Unit_ :: Iterator_2_
		Iterator_2_;

	static Result_ proceed
	(
		const Iterator_1_,
		const Iterator_2_,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	);

private :
	typedef
		Replacer<Unifier, policy_, direction :: DIRECT>
		DirectReplacer_;
	typedef
		Replacer<Unifier, policy_, direction :: INVERSE>
		InverseReplacer_;
	friend class Policy<Unifier, policy_, direction :: DIRECT>;
	friend class Policy<Unifier, policy_, direction :: INVERSE>;
	template<class, class, int, int>
	friend class Unit;

	static Result_ unifyNode (Unit_);
	static Result_ tryFixed (Unit_);
	static Result_ unifyNext (Unit_);
};

}
}
}
}



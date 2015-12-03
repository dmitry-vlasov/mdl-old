/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unifier.hpp                     */
/* Description:     main unification algorithm. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_UNIFIER_HPP_
#define MDL_EXPRESSION_UNIFY_EXP_UNIFIER_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

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

	static Result_ proceed (const Iterator_1_, const Iterator_2_);
	static Result_ proceed (Unit_);

private :
	typedef
		Replacer<Unifier, policy_, direction :: DIRECT>
		DirectReplacer_;
	typedef
		Replacer<Unifier, policy_, direction :: INVERSE>
		InverseReplacer_;
	friend class Policy<Unifier, policy_, direction :: DIRECT>;
	friend class Policy<Unifier, policy_, direction :: INVERSE>;

	static Result_ unifyNode (Unit_);
	static Result_ tryUnit (Unit_);
	static Result_ tryFixed (Unit_);
	static Result_ unifyNext (Unit_);
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_UNIFIER_HPP_*/

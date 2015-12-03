/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Simifier.hpp                       */
/* Description:     main simification algorithm. Static class                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SIMIFY_SIMIFIER_HPP_
#define MDL_EXPRESSION_SIMIFY_SIMIFIER_HPP_

namespace mdl {
namespace expression {
namespace simify {

template
<
	class U,
	class A = allocator :: Heap
>
class Simifier {
public :
	typedef U Unit_;
	typedef A Allocator_;
	typedef Similarity<Unit_> Similarity_;
	typedef
		typename Unit_ :: Iterator_1_
		Iterator_1_;
	typedef
		typename Unit_ :: Iterator_2_
		Iterator_2_;

	static Similarity_ proceed
	(
		const Iterator_1_,
		const Iterator_2_,
		const index :: Step,
		const index :: Step
	);
	static Similarity_ proceed (Unit_);

private :
	typedef
		Simifier<Unit_, Allocator_>
		DirectSimifier_;
	typedef
		Simifier
		<
			typename Unit_ :: InverseUnit_,
			Allocator_
		>
		InverseSimifier_;
	typedef
		typename Unit_ :: Term_2_
		Term_;

	static Similarity_ simifyNode (Unit_);
	static Similarity_ simifyNext (Unit_);
	static Similarity_ tryFixed (Unit_);
	static Similarity_ tryReplaceable (Unit_);
	static Similarity_ tryTerm (Unit_, const Term_* const);
};

}
}
}

#endif /*MDL_EXPRESSION_SIMIFY_SIMIFIER_HPP_*/

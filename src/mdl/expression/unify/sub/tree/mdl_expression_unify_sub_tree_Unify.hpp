/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Unify.hpp                  */
/* Description:     wrapper for the multy Unifier class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFY_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFY_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

template
<
	class T,
	class A = allocator :: Stack
>
class Unify : public Scalar<A> {
public :
	typedef A Allocator_;
	typedef T Types_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Matrix_
		Input_;
	typedef
		typename expression :: Tree
		<
			const Evidence_*,
			storage :: ByValue,
			expression :: node :: container :: Set,
			Allocator_
		>
		Cell_;
	typedef Unit<Cell_, Allocator_> Unit_;
	typedef
		typename Unit_ :: Vector_
		Vector_;
	typedef
		typename Unit_ :: Matrix_
		Matrix_;
	typedef
		typename Unit_ :: Substitution_
		Substitution_;
	typedef Unifier<Unit_, Types_> Unifier_;

	Unify
	(
		const index :: Arity,
		Evidences_& evidences,
		const Substitution_* subInt
	);

	void operator () (const Input_&);

	void show (String&) const;
	void show () const;

private :
	typedef
		vector :: Vector
		<
			mdl :: Symbol,
			storage :: ByValue,
			Allocator_
		>
		VectorSymbol_;

	void unifyTrivial (const Input_&);
	void initVariables (const Input_&);
	void initMatrix (const Input_&);
	void fillCell
	(
		const Evidences_* evidences,
		const index :: Arity i, // variable (column)
		const Symbol& variable,
		Cell_* cell
	);

	const index :: Arity arity_;
	const Substitution_* subInt_;
	Evidences_& evidences_;

	Matrix_  matrix_;
	VectorSymbol_ variables_;
	value :: Integer boundary_;
};

}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFY_HPP_*/

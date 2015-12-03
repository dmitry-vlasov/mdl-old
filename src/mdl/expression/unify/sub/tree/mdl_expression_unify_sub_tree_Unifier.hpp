/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Unifier.hpp                */
/* Description:     multy unification algorithm. Static class                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

template<class U, class T>
class Unifier {
public :
	typedef U Unit_;
	typedef T Types_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Unit_ :: Iterator_
		Iterator_;
	typedef
		typename Unit_ :: Matrix_
		Matrix_;
	typedef
		typename Unit_ :: Substitution_
		Substitution_;
	typedef
		typename Substitution_ :: Term_
		Term_;
	typedef
		typename Iterator_ :: Node_
		Node_;
	typedef
		typename Node_ :: Terms_
		Terms_;

	Unifier
	(
		const index :: Arity,
		const Substitution_*,
		Evidences_&,
		const value :: Integer
	);

	void operator() (const Matrix_&);

private :
	void unifyNode (Unit_);
	void tryUnit (Unit_);
	void applyUnit (Unit_&);
	void applyTerm
	(
		Unit_&,
		const index :: Arity,
		const Term_*
	);
	bool tryReplace
	(
		Unit_,
		const index :: Arity,
		const index :: Arity
	);
	bool tryTerm
	(
		Unit_,
		const index :: Arity,
		const index :: Arity,
		const typename Unit_ :: Term_*
	);
	void unifyNext (Unit_);
	void unifyLast (Unit_);

	const index :: Arity dimension_;
	const Substitution_* substitutionInt_;
	Evidences_& evidences_;
	const value :: Integer boundary_;

	// debug stuff
	/*enum {
		DEBUG_DIM = 5
	};
	void showBranch (Unit_, const value :: Integer = 0);
	void hideBranch (Unit_, const value :: Integer = 0);
	bool flags_ [DEBUG_DIM];
	int  stop_  [DEBUG_DIM];
	int  count_ [DEBUG_DIM];*/

	typedef
		vector :: Vector<Unit_*, storage :: ByValue, allocator :: Standard>
		UnitVector_;

	static UnitVector_* units_;
};

}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_TREE_UNIFIER_HPP_*/

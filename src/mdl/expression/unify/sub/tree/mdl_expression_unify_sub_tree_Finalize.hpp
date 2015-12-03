/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Finalize.hpp               */
/* Description:     final procedure of a matrix unification                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_TREE_FINALIZE_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_TREE_FINALIZE_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

template<class U, class T>
class Finalize {
public :
	typedef U Unit_;
	typedef T Types_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	typedef
		typename Unit_ :: Substitution_
		Substitution_;
	typedef
		typename Unit_ :: Container_
		Container_;
	typedef Multyindex<Container_, Types_> Multyindex_;
	typedef
		typename Multyindex_ :: Matrix_
		Matrix_;

	Finalize
	(
		const Substitution_*,
		Evidences_&,
		const value :: Integer
	);

	void operator() (const Unit_&);

private :
	void proceedMultyindex (const Unit_&, const Multyindex_&);
	const Substitution_* createTheta (const Unit_&) const;
	const Substitution_* createTheta (const Unit_&, const Multyindex_&) const;

	const Substitution_* substitutionInt_;
	Evidences_& evidences_;
	const value :: Integer boundary_;
};

}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_TREE_FINALIZE_HPP_*/

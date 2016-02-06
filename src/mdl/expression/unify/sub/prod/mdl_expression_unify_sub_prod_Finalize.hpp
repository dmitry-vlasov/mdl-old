/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Finalize.hpp                */
/* Description:     scalar substitution unifier module                       */
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

template<class U, class T>
class Finalize : public Scalar<typename U :: Allocator_> {
public :
	typedef U Unifier_;
	typedef T Types_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	typedef
		typename Unifier_ :: Allocator_
		Allocator_;
	typedef
		typename Unifier_ :: Matrix_
		Matrix_;
	typedef
		typename Unifier_ :: Expression_
		Expression_;
	typedef
		typename Unifier_ :: Substitution_
		Substitution_;
	typedef
		typename Unifier_ :: Substivector_
		Substivector_;
	typedef
		typename Unifier_ :: Multyindex_
		Multyindex_;
	typedef
		typename Unifier_ :: InnerExpression_
		InnerExpression_;
	typedef
		typename Unifier_ :: InnerTerm_
		InnerTerm_;
	typedef
		typename Unifier_ :: InnerSubstitution_
		InnerSubstitution_;
	typedef
		typename Unifier_ :: InnerExprevector_
		InnerExprevector_;

	Finalize (Unifier_*);

	void operator() (const Multyindex_&);

private :
	InnerSubstitution_* createTheta();

	const index :: Arity dimension_;
	const Substitution_* substitutionInt_;
	Evidences_& evidences_;
	Matrix_* matrix_;
};

}
}
}
}
}



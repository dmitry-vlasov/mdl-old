/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_Finaly.hpp                      */
/* Description:     final procedure of a substitution unification            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_FINALY_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_FINALY_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {

template<class S, class T>
class Finaly {
public :
	typedef S Substitution_;
	typedef T Types_;
	typedef
		typename Types_ :: Allocator_
		Allocator_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	static void finalize
	(
		const Substitution_* substitutionInt,
		Evidences_& evidences,
		Evidence_* evidenceUp [],
		const value :: Integer arity
	);
	static void finalize
	(
		const Substitution_* theta,
		const value :: Integer compositionClosureBoundary,
		const Substitution_* substitutionInt,
		const Substitution_* delta,
		Evidences_& evidences,

		Evidence_* evidenceUp [],
		const value :: Integer arity
	);

private :
	static void doJob
	(
		const Substitution_* substitution,
		Evidences_& evidences,
		Evidence_* evidenceUp [],
		const value :: Integer arity
	);
	static Substitution_* createSubstitution
	(
		const value :: Integer boundary,
		const Substitution_* sb,
		const Substitution_* dl,
		const Substitution_* th,
		bool& success
	);
};

}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_FINALY_HPP_*/

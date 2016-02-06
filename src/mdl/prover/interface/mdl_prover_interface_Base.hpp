/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Base.hpp                            */
/* Description:     basic expression types for a prover                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Base {
public :
	typedef A Allocator_;
	typedef Node<Allocator_> Node_;
	typedef
		typename mdl :: proof :: Node
		Premise_;
	typedef
		typename expression :: List<Allocator_>
		Expression_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef
		expression :: Substitution<Term_>
		Substitution_;

	typedef
		typename expression :: Tree
		<
			Premise_*,
			storage :: ByValue,
#ifdef ALLOW_MULTIPLE_PREMISE
			expression :: node :: container :: List,
#else
			expression :: node :: container :: Singleton,
#endif
			Allocator_
		>
		PremiseTree_;

	typedef
		typename vector :: Vector
		<
			Premise_*,
			storage :: ByValue,
			Allocator_
		>
		PremiseVector_;

	typedef
		typename expression :: Tree
		<
			Node_*,
			storage :: ByValue,
			expression :: node :: container :: Singleton,
			Allocator_
		>
		ExpressionTree_;

	typedef
		typename set :: Set
		<
			const Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeSet_;
};

}
}
}



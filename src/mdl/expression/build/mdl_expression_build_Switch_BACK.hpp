/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Switch_BACK.hpp                     */
/* Description:     expression building routines                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_BUILD_SWITCH_BACK_HPP_
#define MDL_EXPRESSION_BUILD_SWITCH_BACK_HPP_

#include "mdl/expression/build/mdl_expression_build.dpp"

namespace mdl {
namespace expression {
namespace build {

template<class B>
struct Switch<B, BACK> {
	typedef B Builder_;
	typedef
		typename Builder_ :: Expression_
		Expression_;
	typedef
		typename Builder_ :: Allocator_
		Allocator_;
	typedef
		typename Builder_ :: Iterator_1_
		Iterator_1_;
	typedef
		typename Builder_ :: Iterator_2_
		Iterator_2_;
	typedef
		typename Builder_ :: Term_1_
		Term_1_;
	typedef
		typename Builder_ :: Term_2_
		Term_2_;
	typedef
		typename Builder_ :: Terms_1_
		Terms_1_;
	typedef
		typename Builder_ :: Terms_2_
		Terms_2_;
	typedef
		typename Builder_ :: Node_1_
		Node_1_;
	enum {
		FORTH_ = false,
		BACK_ = true
	};

	static const Terms_2_&
	getTerms (const Iterator_2_&);
	static void
	inc (Iterator_1_&, Iterator_2_&);
	static bool
	end (const Term_2_*, const Iterator_2_&);
	static Term_1_*
	newTerm
	(
		const Iterator_1_&,
		const Iterator_1_&,
		const mdl :: Type*
	);
	static Iterator_1_
	startTarget (Expression_* const);
	static Iterator_2_
	startSource (const Term_2_* const);

	static Iterator_2_
	beginSource (const Term_2_* const);
	static Iterator_2_
	endSource (const Term_2_* const);
};

}
}
}

#endif /*MDL_EXPRESSION_BUILD_SWITCH_BACK_HPP_*/

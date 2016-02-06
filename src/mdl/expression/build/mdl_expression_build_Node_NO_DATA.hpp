/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Node_NO_DATA.hpp                    */
/* Description:     manager for node data in expression building routines    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/build/mdl_expression_build.dpp"

namespace mdl {
namespace expression {
namespace build {

template<class B>
struct Node<B, NO_DATA> {
	typedef B Builder_;
	typedef
		typename Builder_ :: Expression_
		Expression_;
	typedef
		typename Builder_ :: Iterator_1_
		Iterator_1_;
	typedef
		typename Builder_ :: Iterator_2_
		Iterator_2_;
	typedef
		typename Builder_ :: Value_
		Value_;

	static void manage
	(
		Expression_* const target,
		Iterator_1_& targetEnd,
		Iterator_2_& sourceEnd,
		Value_
	);
};

}
}
}



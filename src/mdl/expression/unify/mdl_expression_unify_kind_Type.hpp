/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_kind_Type.hpp                       */
/* Description:     enum for unification kind                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_KIND_TYPE_HPP_
#define MDL_EXPRESSION_UNIFY_KIND_TYPE_HPP_

namespace mdl {
namespace expression {
namespace unify {
namespace kind {

	enum Type {
		COMMON,  // general (standard) unification
		PLAIN,   // variable replacement unification
		FACTOR   // factor-unification
	};
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_KIND_TYPE_HPP_*/

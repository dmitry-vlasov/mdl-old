/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_policy_Type.hpp                     */
/* Description:     enum for unification policy                              */
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
namespace policy {

	enum Type {
		DIRECT,    // unification in one direction (forth)
		INVERSE,   // unification in one direction (back)
		SYMMETRIC, // unification in both directions
	};
}
}
}
}



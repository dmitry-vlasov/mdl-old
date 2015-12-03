/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_direction_Linear.hpp                      */
/* Description:     linear iterator directions type                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_DIRECTION_LINEAR_HPP_
#define MDL_EXPRESSION_DIRECTION_LINEAR_HPP_

#include "mdl/expression/mdl_expression.dpp"

namespace mdl {
namespace expression {
namespace direction {

struct Linear {
	enum {
		LEFT,
		RIGHT,
		DEFAULT = RIGHT,
		MAXIMUM = RIGHT
	};
};

}
}
}

#endif /*MDL_EXPRESSION_DIRECTION_LINEAR_HPP_*/

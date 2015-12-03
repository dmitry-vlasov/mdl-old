/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_direction_Direction.hpp                   */
/* Description:     all iterator directions type                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_DIRECTION_DIRECTION_HPP_
#define MDL_EXPRESSION_DIRECTION_DIRECTION_HPP_

#include "mdl/expression/direction/mdl_expression_direction_Tree.hpp"

namespace mdl {
namespace expression {
namespace direction {

	enum Direction {
		LEFT    = Tree :: LEFT,
		RIGHT   = Tree :: RIGHT,
		UP      = Tree :: UP,
		DOWN    = Tree :: DOWN,
		DEFAULT = Tree :: DEFAULT
	};

}
	using direction :: Direction;
}
}

#endif /*MDL_EXPRESSION_DIRECTION_DIRECTION_HPP_*/

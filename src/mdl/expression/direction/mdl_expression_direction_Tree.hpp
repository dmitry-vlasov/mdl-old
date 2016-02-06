/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_direction_Tree.hpp                        */
/* Description:     tree (2 dimensional) iterator directions type            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/direction/mdl_expression_direction_Linear.hpp"

namespace mdl {
namespace expression {
namespace direction {

struct Tree : public Linear {
	enum {
		UP = Linear :: MAXIMUM + 1,
		DOWN,
		MAXIMUM = DOWN
	};
};

}
}
}



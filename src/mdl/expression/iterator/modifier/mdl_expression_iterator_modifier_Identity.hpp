/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Identity.hpp            */
/* Description:     identity modifier for iterator                           */
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
namespace iterator {
namespace modifier {

template<class I>
class Identity : public I {
public :
	typedef I Iterator_;

	Identity ();
	Identity (const Iterator_&);
	Identity (const Identity&);
};

}
}
}
}



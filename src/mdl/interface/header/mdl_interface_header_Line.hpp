/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_Line.hpp                            */
/* Description:     abstract interface for header line                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_LINE_HPP_
#define MDL_INTERFACE_HEADER_LINE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {

class Line :
	virtual public object :: Expressive,
	virtual public object :: Buildable {
};

}
}
}

#endif /*MDL_INTERFACE_HEADER_LINE_HPP_*/

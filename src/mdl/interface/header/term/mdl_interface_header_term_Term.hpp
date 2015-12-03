/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_term_Term.hpp                       */
/* Description:     abstract interface for general term                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_TERM_TERM_HPP_
#define MDL_INTERFACE_HEADER_TERM_TERM_HPP_

#include "mdl/interface/header/mdl_interface_header_Line.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace term {

class Term : virtual public Line {
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_TERM_TERM_HPP_*/

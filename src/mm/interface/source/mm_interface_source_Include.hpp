/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Include.hpp                          */
/* Description:     abstract interface for metamath inclusion                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_SOURCE_INCLUDE_HPP_
#define MM_INTERFACE_SOURCE_INCLUDE_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace source {

class Include : public object :: Verifiable {
public :
	virtual const Path& getPath() const = 0;
};

}
}
}

#endif /* MM_INTERFACE_SOURCE_INCLUDE_HPP_ */

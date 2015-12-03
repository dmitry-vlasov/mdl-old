/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Comments.hpp                         */
/* Description:     abstract interface for metamath comments                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_SOURCE_COMMENTS_HPP_
#define MM_INTERFACE_SOURCE_COMMENTS_HPP_

#include "interface/object/mm_interface_object.hpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace interface {
namespace source {

class Comments : public object :: Translatable {
public :
	typedef Lexer :: Comments_ :: Index_ Index_;
	virtual Index_ getSize() const = 0;
	virtual const String* getString (const Index_) const = 0;
	virtual bool isDate (const Index_) const = 0;
};

}
}
}

#endif /* MM_INTERFACE_SOURCE_COMMENTS_HPP_ */

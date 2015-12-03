/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Reference.hpp                        */
/* Description:     abstract interface for metamath reference in proof       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_SOURCE_REFERENCE_HPP_
#define MM_INTERFACE_SOURCE_REFERENCE_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace source {

class Reference : public object :: Writable {
public :
	virtual void operateCheck (Stack* const, const Assertion* const) const = 0;
	virtual const target :: Step* operateTranslate
	(
		Stack* const,
		const Assertion* const,
		const Proof* const
	) const = 0;
};

}
}
}

#endif /*MM_INTERFACE_SOURCE_REFERENCE_HPP_*/

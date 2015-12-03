/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_value.hpp                                       */
/* Description:     value typedefs                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_TYPES_VALUE_HPP_
#define MM_TYPES_VALUE_HPP_

namespace mm {
namespace value {

	typedef
		nstd :: U_int32_t
		Literal;
	typedef
		nstd :: U_int32_t
		Label;
}
}

#include "types/value/undefined/mm_types_value_undefined.hpp"

#endif /*MM_TYPES_VALUE_HPP_*/

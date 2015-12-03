/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_value.hpp                                      */
/* Description:     value typedefs                                           */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_VALUE_HPP_
#define SMM_TYPES_VALUE_HPP_

namespace smm {
namespace value {

	typedef
		nstd :: U_int32_t
		Literal;
	typedef
		nstd :: U_int32_t
		Index;
}
}

#include "smm/types/value/undefined/smm_types_value_undefined.hpp"

#endif /*SMM_TYPES_VALUE_HPP_*/

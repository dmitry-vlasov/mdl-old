/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_value_undefined.hpp                             */
/* Description:     undefined value constants                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace value {
namespace undefined {

	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Label
		LABEL = Undefined<Label> :: getValue();
}
}
}



/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_index_undefined.hpp                             */
/* Description:     constants for undefined indexes                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace index {
namespace undefined {

	const Literal
		FILE = Undefined<File> :: getValue();
	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Type
		TYPE = Undefined<Type> :: getValue();
	const Assertion
		ASSERTION = Undefined<Assertion> :: getValue();
	const Arity
		ARITY = Undefined<Arity> :: getValue();
	const Step
		STEP = Undefined<Step> :: getValue();
}
}
}



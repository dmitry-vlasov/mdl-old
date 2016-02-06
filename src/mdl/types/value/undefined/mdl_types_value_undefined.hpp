/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_value_undefined.hpp                            */
/* Description:     basic undefined values                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace value {
namespace undefined {

	const Integer
		INTEGER = Undefined<Integer> :: getValue();
	const Integer
		LONG = Undefined<Long> :: getValue();
	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Name
		NAME = Undefined<Name> :: getValue();
	const Kind
		KIND = Undefined<Kind> :: getValue();
}
}
}



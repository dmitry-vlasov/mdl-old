/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_value_undefined.hpp                            */
/* Description:     basic undefined values                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace value {
namespace undefined {

	const Integer
		INTEGER = Undefined<Integer> :: getValue();
	const Integer
		LONG = Undefined<Long> :: getValue();
	const Relation
		RELATION = Undefined<Relation> :: getValue();
	const Theory
		THEORY = Undefined<Theory> :: getValue();
	const Signature
		SIGNATURE = Undefined<Signature> :: getValue();
	const Variable
		VARIABLE = Undefined<Variable> :: getValue();
	const Symbol
		SYMBOL = Undefined<Symbol> :: getValue();
}
}
}



/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_value_undefined.hpp                            */
/* Description:     undefined value constants                                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace smm {
namespace value {
namespace undefined {

	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Index
		INDEX = Undefined<Index> :: getValue();
}
}
}



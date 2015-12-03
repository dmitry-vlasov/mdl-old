/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_index_undefined.hpp                            */
/* Description:     constants for undefined indexes                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_INDEX_UNDEFINED_HPP_
#define SMM_TYPES_INDEX_UNDEFINED_HPP_

namespace smm {
namespace index {
namespace undefined {

	const Literal
		FILE = Undefined<File> :: getValue();
	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Assertion
		ASSERTION = Undefined<Assertion> :: getValue();
	const Arity
		ARITY = Undefined<Arity> :: getValue();
	const Step
		STEP = Undefined<Step> :: getValue();
}
}
}

#endif /*SMM_TYPES_INDEX_UNDEFINED_HPP_*/

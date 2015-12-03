/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_index_undefined.hpp                            */
/* Description:     basic undefined indexes                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_INDEX_UDEFINED_HPP_
#define MDL_TYPES_INDEX_UDEFINED_HPP_

namespace mdl {
namespace index {
namespace undefined {

	const File
		FILE = Undefined<File> :: getValue();
	const Name
		NAME = Undefined<Name> :: getValue();
	const Literal
		LITERAL = Undefined<Literal> :: getValue();
	const Assertion
		ASSERTION = Undefined<Assertion> :: getValue();
	const Arity
		ARITY = Undefined<Arity> :: getValue();
	const Step
		STEP = Undefined<Step> :: getValue();
	const Type
		TYPE = Undefined<Type> :: getValue();
	const Rule
		RULE = Undefined<Rule> :: getValue();
	const Constant
		CONSTANT = Undefined<Constant> :: getValue();
	const Theory
		THEORY = Undefined<Theory> :: getValue();
	const Form
		FORM = Undefined<Form> :: getValue();
}
}
}

#endif /*MDL_TYPES_INDEX_UDEFINED_HPP_*/

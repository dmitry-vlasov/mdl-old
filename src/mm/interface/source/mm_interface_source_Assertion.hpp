/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Assertion.hpp                        */
/* Description:     abstract interface for metamath assertion                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/object/mm_interface_object.hpp"
#include "expression/mm_expression.hpp"

namespace mm {
namespace interface {
namespace source {

class Assertion :
	public object :: Expressive,
	public object :: Labeled,
	public object :: Verifiable {
public :
	virtual void applyCheck (Stack* const) const = 0;
	virtual const target :: Step* applyTranslate (Stack* const) const = 0;

	virtual bool areDisjoined (const value :: Literal, const value :: Literal) const = 0;
	virtual void checkDisjoined (const Assertion* const) const = 0;
	virtual bool newVariable (const value :: Literal) const = 0;

	virtual bool isAxiomatic() const = 0;
	virtual bool isProvable() const = 0;
	virtual bool isVerified() const = 0;
};

}
}
}



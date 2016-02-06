/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Hypothesis.hpp                       */
/* Description:     abstract interface for metamath hypothesis               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace source {

class Hypothesis :
	public object :: Expressive,
	public object :: Labeled,
	public object :: Translatable {
public :
	virtual bool isRelevant (const vector :: Literal&) const = 0;
	virtual void checkFloating (const Expression*, Substitution* const) const = 0;
	virtual void checkEssential (const stack :: Line*, const Substitution* const) const = 0;
	virtual void collectEssentialVariables (vector :: Literal&) const = 0;
	virtual void pushSelf (Stack* const, const stack :: Line* const = NULL) const = 0;
	virtual const target :: Step* needDeclaration
	(
		const Assertion* const,
		const Proof* const
	) const = 0;
	virtual const Hypothesis* getPrevious() const = 0;

	virtual bool isEssential() const = 0;
	virtual bool isFloating() const = 0;
};

}
}
}





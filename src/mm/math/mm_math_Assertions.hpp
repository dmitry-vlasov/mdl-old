/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Assertions.hpp                                   */
/* Description:     global metamath assertions container                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "math/mm_math.dpp"

namespace mm {
namespace math {

class Assertions :
	public object :: Object,
	public Scalar<Assertions> {
public :
	Assertions();
	virtual ~ Assertions();

	void add (const mm :: source :: Assertion* const);
	const mm :: source :: Assertion* get (const index :: Assertion) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	index :: Assertion axiomaticCount_;
	index :: Assertion provableCount_;

	vector :: source :: Assertion assertionVector_;
	enum {
		INITIAL_ASSERTION_VECTOR_CAPACITY = 1024 * 32
	};
};
}
}

#include "math/mm_math_Assertions.ipp"



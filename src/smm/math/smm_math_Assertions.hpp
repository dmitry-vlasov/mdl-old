/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Assertions.hpp                                  */
/* Description:     global smm assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.hpp"
#include "smm/math/smm_math.dpp"

namespace smm {
namespace math {

class Assertions :
	public object :: Object,
	public Scalar<Assertions> {
public :
	Assertions();
	virtual ~ Assertions();

	index :: Assertion add (const smm :: Assertion* const);
	const smm :: Assertion* get (const index :: Assertion) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	index :: Assertion axiomaticCount_;
	index :: Assertion provableCount_;

	vector :: Assertion assertionVector_;
	enum {
		INITIAL_ASSERTION_VECTOR_CAPACITY = 1024 * 32
	};
};
}
}

#include "smm/math/smm_math_Assertions.ipp"



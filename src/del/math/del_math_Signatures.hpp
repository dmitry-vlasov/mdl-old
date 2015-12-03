/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Signatures.hpp                                  */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_SIGNATURES_HPP_
#define DEL_MATH_SIGNATURES_HPP_

#include "del/interface/del_interface.hpp"
#include "del/math/del_math.dpp"

namespace del {
namespace math {

class Signatures :
	public Object,
	public Scalar<Signatures> {
public :
	Signatures();
	virtual ~ Signatures();

	index :: Signature add (const del :: Signature* const);
	const del :: Signature* get (const index :: Signature) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Signature signatureVector_;
	enum {
		INITIAL_SIGNATURE_VECTOR_CAPACITY = 64
	};
};
}
}

#include "del/math/del_math_Signatures.ipp"

#endif /*DEL_MATH_SIGNATURES_HPP_*/

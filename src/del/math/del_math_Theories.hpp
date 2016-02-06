/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Theories.hpp                                    */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/math/del_math.dpp"

namespace del {
namespace math {

class Theories :
	public Object,
	public Scalar<Theories> {
public :
	Theories();
	virtual ~ Theories();

	index :: Theory add (const del :: Theory* const);
	const del :: Theory* get (const index :: Theory) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Theory theoryVector_;
	enum {
		INITIAL_THEORY_VECTOR_CAPACITY = 64
	};
};
}
}

#include "del/math/del_math_Theories.ipp"



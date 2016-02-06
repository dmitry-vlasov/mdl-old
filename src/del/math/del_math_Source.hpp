/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Source.hpp                                      */
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

class Source :
	public Object,
	public Scalar<Source> {
public :
	Source();
	virtual ~ Source();

	void add (del :: Source* const);
	del :: Source* get() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	del :: Source* source_;
};
}
}

#include "del/math/del_math_Source.ipp"



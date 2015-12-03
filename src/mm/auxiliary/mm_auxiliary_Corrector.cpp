/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Corrector.cpp                               */
/* Description:     corrector for math.mm syntax irregularities              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_CORRECTOR_CPP_
#define MM_AUXILIARY_CORRECTOR_CPP_

#include <iostream>

#include "mm/lexer/mm_lexer.hpp"
#include "mm/auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	void
	Corrector :: release()
	{
		Grammar :: release();
		Symbol :: release();
	}
	const vector :: Literal*
	Corrector :: getExpression (const String& token) {
		return Grammar :: getExpression (token);
	}

	// nstd :: Static implementation
	void
	Corrector :: initRaw()
	{
		Symbol :: initRaw();
		Grammar :: initRaw();
	}
	void
	Corrector :: showRaw (String&) {
	}
	Size_t
	Corrector :: getRawVolume()
	{
		Size_t volume = 0;
		volume += Grammar :: getRawVolume();
		volume += Symbol :: getRawVolume();
		return volume;
	}
}
}

#endif /*MM_AUXILIARY_CORRECTOR_CPP_*/

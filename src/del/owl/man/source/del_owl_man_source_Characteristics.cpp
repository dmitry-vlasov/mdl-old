/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Characteristics.cpp                   */
/* Description:     manchester OWL characteristics source                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Characteristics :: Characteristics (const Location& location) :
	location_ (location) {
	}
	Characteristics :: ~ Characteristics() {
	}

	// object :: Object implementation
	void
	Characteristics :: commitSuicide() {
		delete this;
	}
	Size_t
	Characteristics :: getVolume() const {
		return 0;
	}
	Size_t
	Characteristics :: getSizeOf() const {
		return sizeof (Characteristics);
	}
	void
	Characteristics :: show (String&) const {
	}
}
}
}
}



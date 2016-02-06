/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_LimitReached.cpp                   */
/* Description:     limit reached exception                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {
namespace exception {

	/****************************
	 *		Public members
	 ****************************/

	inline
	LimitReached :: LimitReached() throw() :
	Exception ("limit reached") {
	}
	inline
	LimitReached :: LimitReached (const LimitReached& exception) throw() :
	Exception (exception) {
	}
	LimitReached :: ~ LimitReached() throw() {
	}
}
}
}



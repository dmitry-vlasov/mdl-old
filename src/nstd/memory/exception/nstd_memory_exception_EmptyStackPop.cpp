/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_EmptyStackPop.cpp                  */
/* Description:     exception at empty stack pop attempt                     */
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
	EmptyStackPop :: EmptyStackPop() throw() :
	Exception ("empty stack pop") {
	}
	inline
	EmptyStackPop :: EmptyStackPop (const EmptyStackPop& exception) throw() :
	Exception (exception) {
	}
	EmptyStackPop :: ~ EmptyStackPop() throw() {
	}
}
}
}



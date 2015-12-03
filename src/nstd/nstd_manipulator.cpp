/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_manipulator.cpp                                     */
/* Description:     nstd string manipulator class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MANIPULATOR_CPP_
#define NSTD_MANIPULATOR_CPP_

#include "nstd_chars.hpp"

namespace nstd {
namespace manipulator {

	/************************************
	 *		Manipulators implementation
	 ************************************/

	template<class A>
	inline String<A>&
	indent (String<A>& string)
	{
		if (!string.indentOn_) {
			string.indentOn_ = true;
		}
		return string;
	}
	template<class A>
	inline String<A>&
	identity (String<A>& string) {
		return string;
	}
	template<class A>
	inline String<A>&
	iterate (String<A>& string)
	{
		if (!string.modeOn_) {
			string.iterateOn_ = true;
		}
		return string;
	}
	template<class A>
	inline String<A>&
	mode (String<A>& string)
	{
		if (!string.iterateOn_) {
			string.modeOn_ = true;
		}
		return string;
	}
	template<class A>
	inline String<A>&
	endLine (String<A>& string) {
		return string << chars :: NEW_LINE;
	}
	template<class A>
	inline String<A>&
	endString (String<A>& string) {
		return string << chars :: NULL_CHAR;
	}
	template<class A>
	inline String<A>&
	space (String<A>& string) {
		return string << chars :: SPACE;
	}
	template<class A>
	inline String<A>&
	underline (String<A>& string) {
		return string << chars :: UNDERLINE;
	}
	template<class A>
	inline String<A>&
	tab (String<A>& string) {
		return string << chars :: TAB;
	}
	template<class A>
	inline String<A>&
	slash (String<A>& string) {
		return string << chars :: SLASH;
	}
	template<class A>
	inline String<A>&
	backSlash (String<A>& string) {
		return string << chars :: BACK_SLASH;
	}
}
}

#endif /*NSTD_MANIPULATOR_CPP_*/

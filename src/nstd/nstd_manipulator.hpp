/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_manipulator.hpp                                     */
/* Description:     nstd string manipulator class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd.dpp"

namespace nstd {
namespace manipulator {

	template<class A>
	String<A>& indent (String<A>&);
	template<class A>
	String<A>& identity (String<A>&);
	template<class A>
	String<A>& iterate (String<A>&);
	template<class A>
	String<A>& mode (String<A>&);
	template<class A>
	String<A>& endLine (String<A>&);
	template<class A>
	String<A>& endString (String<A>&);
	template<class A>
	String<A>& space (String<A>&);
	template<class A>
	String<A>& underline (String<A>&);
	template<class A>
	String<A>& tab (String<A>&);
	template<class A>
	String<A>& slash (String<A>&);
	template<class A>
	String<A>& backSlash (String<A>&);
}
}



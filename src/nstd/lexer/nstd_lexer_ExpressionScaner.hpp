/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_ExpressionScaner.hpp                          */
/* Description:     template for expression scaners                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/nstd_lexer_Source.hpp"

namespace nstd {
namespace lexer {

// E - expression scaner, T - token type
template<class E, class T, class S = Source<> >
class ExpressionScaner {
public :
	typedef S Source_;

	ExpressionScaner (Source_& source) :
	source_ (source) {
	}
	
	typename T :: Type scan ()
	{
		/*if (E :: isTerminal (source_.getChar())) {
			return T :: UNKNOWN;
		}*/
		while (!E :: isTerminal (source_.getChar()) &&
			!source_.getChar().isEOF()) {
			++ source_;
		}
		if (source_.getChar().isEOF()) {
			return T :: EOF_;
		} else {
			return E :: getTokenType();
		}
	}

private :
	Source_& source_;
};

}
}



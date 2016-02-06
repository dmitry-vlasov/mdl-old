/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_WhitespaceScaner.hpp                           */
/* Description:     smm whitespace scaner                                    */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/lexer/smm_lexer_CommentScaner.hpp"

namespace smm {
namespace lexer {

class WhitespaceScaner : public nstd :: Object {
public :
	WhitespaceScaner (Source&);
	virtual ~ WhitespaceScaner();

	void scan();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	bool commentBegins();

	Source& source_;
	CommentScaner commentScaner_;
};

}
}



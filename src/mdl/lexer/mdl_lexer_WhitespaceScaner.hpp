/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_WhitespaceScaner.hpp                           */
/* Description:     whitespace scaner                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer_CommentScaner.hpp"

namespace mdl {
namespace lexer {

class WhitespaceScaner : public object :: Object {
public :
	typedef
		CommentScaner :: Comments_
		Comments_;

	WhitespaceScaner (Source&);
	virtual ~ WhitespaceScaner();

	void scan();
	Comments_& comments();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	bool commentBegins();

	Source& source_;
	CommentScaner commentScaner_;
};

}
}



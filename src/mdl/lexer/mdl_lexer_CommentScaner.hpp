/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_CommentScaner.hpp                              */
/* Description:     comment scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_COMMENT_SCANER_HPP_
#define MDL_LEXER_COMMENT_SCANER_HPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"

namespace mdl {
namespace lexer {

class CommentScaner : public object :: Object {
public :
	typedef
		Comments<allocator :: Heap>
		Comments_;
	typedef
		Comments_ :: Comment_
		Comment_;

	CommentScaner (Source&);
	virtual ~ CommentScaner();

	void scan();
	Comments_& comments();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Source& source_;
	Comments_ comments_;
};

}
}

#endif /*MDL_LEXER_COMMENT_SCANER_HPP_*/

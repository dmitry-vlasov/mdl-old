/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_CommentScaner.hpp                              */
/* Description:     smm comment scaner                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_COMMENT_SCANER_HPP_
#define SMM_LEXER_COMMENT_SCANER_HPP_

#include "smm/lexer/smm_lexer.dpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace smm {
namespace lexer {

class CommentScaner :
	public nstd :: Object,
	public Scalar<CommentScaner> {
public :
	CommentScaner (Source&);
	virtual ~ CommentScaner();

	void scan();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Source& source_;
};

}
}

#endif /*SMM_LEXER_COMMENT_SCANER_HPP_*/

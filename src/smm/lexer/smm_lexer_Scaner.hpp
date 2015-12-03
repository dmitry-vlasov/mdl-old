/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_Scaner.hpp                                     */
/* Description:     smm scaner                                               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_SCANER_HPP_
#define SMM_LEXER_SCANER_HPP_

#include "smm/lexer/smm_lexer_LabelScaner.hpp"
#include "smm/lexer/smm_lexer_IndexScaner.hpp"
#include "smm/lexer/smm_lexer_LiteralScaner.hpp"
#include "smm/lexer/smm_lexer_PathScaner.hpp"
#include "smm/lexer/smm_lexer_WhitespaceScaner.hpp"

namespace smm {
namespace lexer {

class Scaner : public nstd :: Object {
public :
	Scaner (Source&);
	virtual ~ Scaner();

	Token :: Type scan();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Token :: Type scanSingleChar();
	Token :: Type scanPrefixChar();
	Token :: Type finalize (const Token :: Type);

	Source& source_;

	LiteralScaner literalScaner_;
	IndexScaner indexScaner_;
	LabelScaner labelScaner_;
	PathScaner pathScaner_;
	WhitespaceScaner whitespaceScaner_;

	bool inExpression_;
	bool inProof_;
	bool inInclude_;
	bool inLabel_;
	bool inIndex_;
};

}
}

#endif /*SMM_LEXER_SCANER_HPP_*/

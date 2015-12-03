/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_lexer.hpp                                      */
/* Description:     basic lexer types                                        */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_LEXER_HPP_
#define SMM_TYPES_LEXER_HPP_

namespace smm {
namespace lexer {

	typedef
		nstd :: lexer :: Buffer<>
		Buffer;
	using nstd :: lexer :: Comments;
	using nstd :: lexer :: ExpressionScaner;
	using nstd :: lexer :: Char;
	using nstd :: lexer :: Indent;
	typedef
		nstd :: lexer :: Location<>
		Location;
	using nstd :: lexer :: Position;
	typedef
		nstd :: lexer :: Source<>
		Source;
}
	using lexer :: Location;
}

#endif /*SMM_TYPES_LEXER_HPP_*/

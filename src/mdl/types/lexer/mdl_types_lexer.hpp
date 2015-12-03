/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_lexer.hpp                                      */
/* Description:     basic lexer types                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_LEXER_HPP_
#define MDL_TYPES_LEXER_HPP_

namespace mdl {
namespace lexer {

	typedef
		nstd :: lexer :: Buffer<>
		Buffer;
	typedef
		nstd :: lexer :: Source<>
		Source;
	typedef
		nstd :: lexer :: Location<>
		Location;

	using nstd :: lexer :: Comments;
	using nstd :: lexer :: ExpressionScaner;
	using nstd :: lexer :: Char;
	using nstd :: lexer :: Indent;
	using nstd :: lexer :: Position;

	using namespace nstd :: chars;
}
	using lexer :: Indent;
	using lexer :: Location;
}

#endif /*MDL_TYPES_LEXER_HPP_*/

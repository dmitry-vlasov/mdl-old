/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_lexer.hpp                                       */
/* Description:     basic lexer types                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
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

	using namespace nstd :: chars;
}
	using lexer :: Location;
}



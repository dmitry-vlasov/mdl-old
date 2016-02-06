/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_lexer.hpp                                      */
/* Description:     basic lexer types                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
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



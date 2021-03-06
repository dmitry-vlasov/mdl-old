/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_cut_auxiliary_Error.hpp                               */
/* Description:     mm source cutter error exception class                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/types/mm_types.hpp"
#include "mm/cut/auxiliary/mm_cut_auxiliary.dpp"
#include "mm/cut/lexer/mm_cut_lexer.dpp"

namespace mm {
namespace cut {
namespace auxiliary {

class Error :
	public nstd :: Error<allocator :: Heap, lexer :: Source>,
	public Scalar<Error> {
public :
	enum Type_ {
		NONE,
		LEXER,
		PARSER,
		SEMANTIC,
		CHECKER,
		TRANSLATOR,
		INPUT,
		OUTPUT,
		MISC
	};

	Error (const Location&, const Type_ type = NONE, const char* const = "");
	Error (const Type_ = NONE, const char* const = "");
	virtual ~ Error() throw();

	Type_ getType() const;

	// nstd :: Error interface
	Message_& message();
	void add (const Location_&, const char* = "");
	const char* what() const throw();
	void showMessage (Message_&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	typedef
		nstd :: Error<allocator :: Heap, lexer :: Source>
		Ancestor_;

	Error (const Error&);

	const Type_ type_;
};

}
}
}



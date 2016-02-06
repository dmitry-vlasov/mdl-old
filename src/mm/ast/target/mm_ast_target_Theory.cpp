/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Theory.cpp                                 */
/* Description:     mdl theory declaration                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {

	/****************************
	 *		Public members
	 ****************************/

	Theory :: Theory (const mm :: source :: Include* const include) :
	path_ (Config :: getTarget() /*include->getPath()*/) {
		const_cast<Path&> (path_).extension().clear();
	}
	Theory :: ~ Theory() {
	}

	// object :: Referable implementation
	void
	Theory :: writeReference (String& string) const
	{
		/*for (Path :: Index_ i = 0; i < path_.getDepth(); ++ i) {
			string << path_.getDirectory (i) << mdl :: Token :: dot_;
		}*/
		string << path_.getName();
	}
	void
	Theory :: writeIdentificator (String& string) const {
		string << path_.getName();
	}

	// object :: Targetive implementation
	void
	Theory :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Theory :: write (String& string) const
	{
		if (isDeclared_) {
			return;
		}
		string << mdl :: Token :: theory_ << space;
		string << path_.getName();
		string << mdl :: Token :: semicolon_ << endLine;
		string << endLine;
		isDeclared_ = true;
	}

	// object :: Object implementation
	void
	Theory :: commitSuicide() {
		delete this;
	}
	Size_t
	Theory :: getVolume() const {
		return path_.getVolume();
	}
	Size_t
	Theory :: getSizeOf() const {
		return sizeof (Theory);
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	bool Theory :: isDeclared_ = false;
}
}
}



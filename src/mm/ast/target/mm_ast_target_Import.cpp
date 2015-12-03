/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Import.cpp                                 */
/* Description:     mdl import                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_IMPORT_CPP_
#define MM_AST_TARGET_IMPORT_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

#include "mdl/auxiliary/config/mdl_auxiliary_config.hpp"

namespace mm {
namespace ast {
namespace target {

	/****************************
	 *		Public members
	 ****************************/

	Import :: Import (const mm :: source :: Include* const include) :
	path_ (include->getPath())
	{
		const Config :: Path_& sourcePath = Config :: getSource();
		for (Path :: Depth_ d = 0; d < sourcePath.getDepth(); ++ d) {
			Path :: String_* directory = path_.popDirectoryFirst();
			directory->commitSuicide();
		}
		const Config :: Path_& targetPath = Config :: getTarget();
		const Path :: Depth_ depth = targetPath.getDepth();
		for (Path :: Depth_ d = 0; d < depth; ++ d) {
			path_.pushDirectoryFirst (targetPath.getDirectory (depth - d - 1));
		}
		path_.prefix() = targetPath.getPrefix();
		path_.extension().clear();
		path_.extension() << mdl :: Config :: russellExtension();
	}
	Import :: ~ Import() {
	}

using manipulator :: iterate;
using manipulator :: space;

	// target :: Import implementation
	const Path&
	Import :: getPath() const {
		return path_;
	}
	void
	Import :: writeDescription (String& string) const
	{
		string << "File name:    " << path_.getName();
		string << chars :: DOT << path_.getExtension();
		char spaces = Target :: COMMENT_HEADER_WIDTH;
		spaces -= Target :: COMMENT_HEADER_INDENT;
		spaces -= path_.getName().getSize();
		spaces -= path_.getExtension().getSize();
		spaces -= 6;
		spaces = (spaces < 0) ? 0 : spaces;
		string << iterate << spaces << chars :: SPACE;
	}

	// object :: Targetive implementation
	void
	Import :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Import :: write (String& string) const
	{
		string << mdl :: Token :: import_ << space;
		Path reducedPath (path_);
		reducedPath.reduceUpDirectories();
		for (Path :: Index_ i = 0; i < reducedPath.getDepth(); ++ i) {
			string << reducedPath.getDirectory (i) << mdl :: Token :: dot_;
		}
		string << path_.getName();
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Import :: commitSuicide() {
		delete this;
	}
	Size_t
	Import :: getVolume() const {
		return path_.getVolume();
	}
	Size_t
	Import :: getSizeOf() const {
		return sizeof (Import);
	}
}
}
}

#endif /* MM_AST_TARGET_IMPORT_CPP_ */

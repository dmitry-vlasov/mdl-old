/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Target.cpp                                 */
/* Description:     mdl target - top AST node                                */
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

	Target :: Target
	(
		const bool isTop,
		const mm :: source :: Include* const include
	) :
	isTop_ (isTop),
	import_ (new ast :: target :: Import (include)),
	theory_ (new ast :: target :: Theory (include)),
	block_ (NULL),
	path_ (NULL),
	output_ (NULL)
	{
		if (Config :: deepTranslation()) {
			path_ = new Path (import_->getPath());
		} else {
			path_ = new Path (Config :: getTarget());
		}
		output_ = new Output (path_->getString());
	}
	Target :: ~ Target()
	{
		deleteAggregateObject (import_);
		deleteAggregateObject (theory_);
		deleteAggregateObject (block_);
		deleteAggregateObject (path_);
		deleteAggregateObject (output_);
	}

	// target :: Target implementation
	void
	Target :: addBlock (const object :: Targetive* const block) {
		block_ = block;
	}
	const mm :: object :: Referable*
	Target :: getTheory() const {
		return theory_;
	}

	// object :: Targetive implementation
	void
	Target :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Target :: write (String& string) const {
	}
	void
	Target :: write() const
	{
		if (!isTop_ && !Config :: deepTranslation()) {
			return;
		}
		path_->provideDirectory();
		output_->open();
		writeHeader (output_->buffer());
		block_->write (*output_);
		output_->buffer() << endLine;
		output_->close();
	}
	bool
	Target :: nothingToWrite() const {
		return true;
	}

	// object :: Object implementation
	void
	Target :: commitSuicide() {
		delete this;
	}
	Size_t
	Target :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (import_);
		volume += getAggregateVolume (theory_);
		volume += getAggregateVolume (block_);
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (output_);
		return volume;
	}
	Size_t
	Target :: getSizeOf() const {
		return sizeof (Target);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: iterate;

	void
	Target :: writeHeader (String& string) const
	{
		string << "/*****************************************************************************/" << endLine;
		string << "/* Project name: Russell language pure mathematics library                   */" << endLine;
		string << "/* "; import_->writeDescription (string); string << "*/" << endLine;
		string << "/* Description:  Russell language pure mathematics library                   */" << endLine;
		string << "/* Created:      automatically decompiled by mm program from metamath base   */" << endLine;
		string << "/* Email:        vlasov at academ.org                                        */" << endLine;
		string << "/* URL:          http://russellmath.org                                      */" << endLine;
		string << "/* License:      Creative Commons Public Domain Dedication                   */" << endLine;
		string << "/*****************************************************************************/" << endLine;
		string << endLine;
	}
}
}
}



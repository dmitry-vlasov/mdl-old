/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Source.cpp                                 */
/* Description:     metamath source                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_SOURCE_CPP_
#define MM_AST_SOURCE_SOURCE_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Source :: Source
	(
		const mm :: source :: Include* const include,
		mm :: source :: Block* const block
	) :
	isTop_ (block == NULL),
	include_ (include),
	block_ (block),
	target_ (NULL),
	output_ (new Output (include_->getPath().getString()))
	{
		if (block != NULL) {
			block->pushSource (this);
		}
	}
	Source :: ~ Source()
	{
		if (isTop_) {
			deleteAggregateObject (include_);
		}
		deleteAggregateObject (output_);
		deleteAggregateObject (block_);
	}

	// source :: Source implementation
	void
	Source  :: setBlock (const mm :: source :: Block* const block) {
		block_ = block;
	}

	// object :: Verifiable implementation
	void
	Source :: check() const {
		block_->check();
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Source :: translate() const
	{
		if (target_ != NULL) {
			return target_;
		}
		target_ = new ast :: target :: Target (isTop_, include_);
		const object :: Targetive* const
			block = block_->translate();
		target_->addBlock (block);
		return target_;
	}
	bool
	Source :: isBlock() const {
		return false;
	}
	bool
	Source :: isDisjoined() const {
		return false;
	}
	bool
	Source :: isFloating() const {
		return false;
	}
	bool
	Source :: isEssential() const {
		return false;
	}

	// object :: Writable implementation
	void
	Source :: write (String& string) const {
	}
	void
	Source :: write() const
	{
		output_->open();
		block_->write (*output_);
		output_->close();
	}
	bool
	Source :: nothingToWrite() const {
		return true;
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		if (isTop_) {
			volume += getAggregateVolume (include_);
		}
		volume += getAggregateVolume (block_);
		volume += getAggregateVolume (output_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
}
}
}

#endif /*MM_AST_SOURCE_SOURCE_CPP_*/

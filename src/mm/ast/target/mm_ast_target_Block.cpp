/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Block.cpp                                  */
/* Description:     mdl theory contents                                      */
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

	inline
	Block :: Block (const object :: Referable* const theory) :
	theory_ (theory),
	includeList_ (),
	componentList_ () {
	}
	Block :: ~ Block() {
		deleteAggregateObject (typeList_);
	}

	// mm :: Block implementation
	void
	Block :: addInclude (const object :: Targetive* const include) {
		includeList_.addLast (include);
	}
	void
	Block :: addComponent (const object :: Targetive* const component)
	{
		if (component == NULL) {
			return;
		}
		component->complete (this);
		componentList_.addLast (component);
	}
	void
	Block :: addType (const mm :: target :: Type* const type)
	{
		addComponent (type);
		if (typeList_ == NULL) {
			typeList_ = new list :: target :: Type();
		}
		typeList_->addLast (type);
	}
	const mm :: target :: Type*
	Block :: getType (const Symbol& symbol) const
	{
		if (typeList_ == NULL) {
			return NULL;
		}
		const list :: target :: Type :: Node_*
			node = typeList_->getFirst();
		const mm :: target :: Type*
			type = NULL;
		while (node != NULL) {
			type = node->getValue();
			if (type->getSymbol() == symbol) {
				return type;
			}
			node = node->getNext();
		}
		return NULL;
	}

	// object :: Targetive implementation
	void
	Block :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Block :: write (String& string) const
	{
		writeTo (string);
		writeInclusions();
	}
	void
	Block :: write (Output& output) const
	{
		writeTo (output.buffer());
		writeInclusions();
	}

	// object :: Object implementation
	void
	Block :: commitSuicide() {
		delete this;
	}
	Size_t
	Block :: getVolume() const
	{
		Size_t volume = 0;
		volume += includeList_.getVolume();
		volume += componentList_.getVolume();
		if (!staticVolumeCounted_) {
			volume += getAggregateVolume (typeList_);
			staticVolumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	Block :: getSizeOf() const {
		return sizeof (Block);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Block :: writeHeader (String& string) const
	{
		string << mdl :: Token :: contents_ << space;
		string << mdl :: Token :: of_ << space;
		theory_->writeReference (string);
		string << space << mdl :: Token :: openBrace_ << endLine;
		string << endLine;
	}
	void
	Block :: writeEnding (String& string) const
	{
		string << mdl :: Token :: closeBrace_ << endLine;
	}
	bool
	Block :: noWritableContent() const
	{
		const list :: object :: Writable :: Node_*
			node = componentList_.getFirst();
		while (node != NULL) {
			if (!node->getValue()->nothingToWrite()) {
				return false;
			}
			node = node->getNext();
		}
		return true;
	}
	void
	Block :: writeTo (String& string) const
	{
		bool hasInclusions = false;
		const list :: object :: Writable :: Node_*
			inode = includeList_.getFirst();
		while (inode != NULL) {
			hasInclusions = true;
			inode->getValue()->write (string);
			inode = inode->getNext();
		}
		if (noWritableContent()) {
			return;
		} else if (hasInclusions) {
			string << endLine;
		}
		theory_->write (string);
		writeHeader (string);
		const object :: Writable*
			writable = NULL;
		const list :: object :: Writable :: Node_*
			node = componentList_.getFirst();
		while (node != NULL) {
			writable = node->getValue();
			writable->write (string);
			node = node->getNext();
		}
		writeEnding (string);
	}
	void
	Block :: writeInclusions() const
	{
		const object :: Writable*
			writable = NULL;
		const list :: object :: Writable :: Node_*
			node = componentList_.getFirst();
		while (node != NULL) {
			writable = node->getValue();
			writable->write();
			node = node->getNext();
		}
	}

	/***********************************
	 *		Static private attributes
	 ***********************************/

	bool
		Block :: staticVolumeCounted_ = false;
	list :: target :: Type*
		Block :: typeList_ = NULL;
}
}
}



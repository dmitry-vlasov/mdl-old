/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Block.cpp                                  */
/* Description:     metamath block                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_BLOCK_CPP_
#define MM_AST_SOURCE_BLOCK_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Block :: Block
	(
		const Location& location,
		const mm :: source :: Source* const source
	) :
	location_ (location),
	source_ (source),
	parent_ (NULL),
	sibling_ (NULL),
	constants_(NULL),
	variables_(NULL),
	disjoined_(NULL),
	hypothesis_(NULL),
	includeList_ (),
	componentList_ (),
	verifiableList_ () {
	}
	Block :: Block
	(
		const Location& location,
		mm :: source :: Block* const parent,
		mm :: source :: Block* const sibling,
		const mm :: source :: Source* const source
	) :
	location_ (location),
	source_ ((source == NULL) ? parent->getSource() : source),
	parent_ (parent),
	sibling_ (sibling),
	constants_((parent == NULL) ? sibling->getConstants() : parent->getConstants()),
	variables_((parent == NULL) ? sibling->getVariables() : parent->getVariables()),
	disjoined_((parent == NULL) ? sibling->getDisjoined() : parent->getDisjoined()),
	hypothesis_((parent == NULL) ? sibling->getHypothesis() : parent->getHypothesis()),
	includeList_ (),
	componentList_ (),
	verifiableList_ ()
	{
		if (source == NULL) {
			parent->pushBlock (this);
		}
	}
	Block :: ~ Block() {
	}

	// source :: Block implementation
	const mm :: source :: Source*
	Block :: getSource() const {
		return source_;
	}
	const mm :: source :: Constants*
	Block :: getConstants() const {
		return constants_;
	}
	const mm :: source :: Variables*
	Block :: getVariables() const {
		return variables_;
	}
	const mm :: source :: Disjoined*
	Block :: getDisjoined() const {
		return disjoined_;
	}
	const mm :: source :: Hypothesis*
	Block :: getHypothesis() const {
		return hypothesis_;
	}

	void
	Block :: pushConstants (const mm :: source :: Constants* const constants) {
		constants_ = constants;
		componentList_.addLast (constants);
	}
	void
	Block :: pushVariables (const mm :: source :: Variables* const variables) {
		variables_ = variables;
		componentList_.addLast (variables);
	}
	void
	Block :: pushDisjoined (const mm :: source :: Disjoined* const disjoined) {
		disjoined_ = disjoined;
		componentList_.addLast (disjoined);
	}
	void
	Block :: pushHypothesis (const mm :: source :: Hypothesis* const hypothesis) {
		hypothesis_ = hypothesis;
		componentList_.addLast (hypothesis);
	}
	void
	Block :: pushAssertion (const mm :: source :: Assertion* const assertion) {
		verifiableList_.addLast (assertion);
		componentList_.addLast (assertion);
	}
	void
	Block :: pushBlock (const mm :: source :: Block* const block) {
		verifiableList_.addLast (block);
		componentList_.addLast (block);
	}
	void
	Block :: pushSource (const mm :: source :: Source* const source) {
		verifiableList_.addLast (source);
		componentList_.addLast (source);
	}
	void
	Block :: pushInclude (const mm :: source :: Include* const include) {
		includeList_.addLast (include);
	}

	void
	Block :: translateTo (mm :: target :: Block* const block) const
	{
		const list :: object :: Translatable :: Node_*
			inode = includeList_.getFirst();
		while (inode != NULL) {
			const object :: Translatable*
				include = inode->getValue();
 			const mm :: object :: Targetive* const
				component = include->translate();
 			block->addInclude (component);
			inode = inode->getNext();
		}
		const list :: object :: Translatable :: Node_*
			node = componentList_.getFirst();
		const object :: Translatable*
			translatable = NULL;
		while (node != NULL) {
			translatable = node->getValue();

			const bool isProper =
				!translatable->isFloating() &&
				!translatable->isEssential() &&
				!translatable->isDisjoined();

			if (translatable->isBlock()) {
				const mm :: source :: Block*
					innerBlock = dynamic_cast<const mm :: source :: Block*> (translatable);
					innerBlock->translateTo (block);
 			} else if (isProper) {
 				const mm :: object :: Targetive* const
					component = translatable->translate();
 				if (component != NULL) {
 					block->addComponent (component);
 				}
 			}
			node = node->getNext();
		}
	}

	// object :: Verifiable implementation
	void
	Block :: check() const
	{
		const list :: object :: Verifiable :: Node_*
			node = verifiableList_.getFirst();
		const object :: Verifiable*
			verifiable = NULL;
		while (node != NULL) {
			verifiable = node->getValue();
			verifiable->check();
			node = node->getNext();
		}
	}

	// object :: Translatable interface
	const object :: Targetive*
	Block :: translate () const
	{
		if ((parent_ != NULL) && !Config :: deepTranslation()) {
			return NULL;
		}
		const mm :: target :: Target* const
			target = dynamic_cast<const mm :: target :: Target*>(source_->translate());
		const mm :: object :: Referable* const
			theory = target->getTheory();
		mm :: target :: Block* const
			block = new ast :: target :: Block (theory);

		translateTo (block);
		return block;
	}
	bool
	Block :: isBlock() const {
		return true;
	}
	bool
	Block :: isDisjoined() const {
		return false;
	}
	bool
	Block :: isFloating() const {
		return false;
	}
	bool
	Block :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Block :: write (String& string) const
	{
		const list :: object :: Translatable :: Node_*
			inode = includeList_.getFirst();
		const object :: Translatable*
			include = NULL;
		while (inode != NULL) {
			include = inode->getValue();
			include->write (string);
			inode = inode->getNext();
		}
		if (parent_ != NULL) {
			string << mm :: Token :: blockBegin_ << endLine;
		}
		const list :: object :: Translatable :: Node_*
			node = componentList_.getFirst();
		const object :: Writable*
			writable = NULL;
		while (node != NULL) {
			writable = node->getValue();
			writable->write (string);
			node = node->getNext();
		}
		if (parent_ != NULL) {
			string << mm :: Token :: blockEnd_ << endLine;
		}
	}
	void
	Block :: write (Output& output) const
	{
		if (parent_ != NULL) {
			Writable :: write (output);
			return;
		}
		const list :: object :: Translatable :: Node_*
			inode = includeList_.getFirst();
		const object :: Translatable*
			include = NULL;
		while (inode != NULL) {
			include = inode->getValue();
			include->write (output);
			inode = inode->getNext();
		}
		const list :: object :: Translatable :: Node_*
			node = componentList_.getFirst();
		const object :: Writable*
			writable = NULL;
		while (node != NULL) {
			writable = node->getValue();
			writable->write (output);
			node = node->getNext();
		}
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
		volume += location_.getVolume();
		volume += includeList_.getVolume();
		volume += componentList_.getVolume();
		volume += verifiableList_.getVolume();
		return volume;
	}
	Size_t
	Block :: getSizeOf() const {
		return sizeof (Block);
	}
}
}
}

#endif /*MM_AST_SOURCE_BLOCK_CPP_*/

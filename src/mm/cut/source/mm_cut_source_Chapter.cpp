/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Chapter.cpp                                */
/* Description:     mm cutting chapter                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/lexer/mm_lexer_Token.hpp"
#include "mm/cut/source/mm_cut_source.hpp"

namespace mm {
namespace cut {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Chapter :: Chapter
	(
		const Source* const source,
		const Header* const header,
		const Content* const content
	) :
	source_ (source),
	header_ (header),
	content_ (content),
	sections_ (),
	directory_ (source->getDirectory()),
	name_ (header->getString()),
	path_ (),
	previous_ (NULL) {
		directory_ << name_ << nstd :: chars :: DIR_DELIMITER ;
		path_ << directory_ << name_ << "." << Config :: metamathExtension();
	}
	Chapter :: ~ Chapter()
	{
		deleteAggregateObject (header_);
		deleteAggregateObject (content_);
	}

	inline const String&
	Chapter :: getDirectory() const{
		return directory_;
	}
	inline const String&
	Chapter :: getName() const{
		return name_;
	}
	inline const String&
	Chapter :: getPath() const{
		return path_;
	}

	inline void
	Chapter :: addSection (const Section* section) {
		sections_.addLast (section);
	}
	void
	Chapter :: write() const
	{
		writeSelf();
		writeSections();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// cut :: Includable implementation
	void
	Chapter :: writeInclusion (String& string) const
	{
		string << mm :: Token :: inclusionBegin_ << space;
		string << path_ << space;
		string << mm :: Token :: inclusionEnd_ << endLine;
		string << endLine;
	}
	const Includable*
	Chapter :: getPrevious() const {
		return previous_;
	}
	void
	Chapter :: setPrevious (const Includable* previous) const {
		previous_ = previous;
	}

	// object :: Object implementation
	void
	Chapter :: commitSuicide() {
		delete this;
	}
	Size_t
	Chapter :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (header_);
		volume += getAggregateVolume (content_);
		volume += sections_.getVolume();
		volume += directory_.getVolume();
		volume += name_.getVolume();
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Chapter :: getSizeOf() const {
		return sizeof (Chapter);
	}
	void
	Chapter :: show (String& string) const
	{
		string << Token :: chapterBegin_ << endLine;
		string << tab; header_->show (string);
		string << Token :: chapterEnd_ << endLine;
		content_->show (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Chapter :: writeSelf() const
	{
		system :: createDirectory (directory_.c_str());
		Output output (path_);
		output.open();
		String& string = output.buffer();
		if (previous_ != NULL) {
			previous_->writeInclusion (string);
		}
		show (string);
		const Sections_ :: Node_*
			node = sections_.getFirst();
		while (node != NULL) {
			const Section*
				section = node->getValue();
			section->writeInclusion (string);
			node = node->getNext();
		}
		output.close();
	}
	void
	Chapter :: writeSections() const
	{
		const Sections_ :: Node_*
			node = sections_.getFirst();
		while (node != NULL) {
			const Section*
				section = node->getValue();
			section->write();
			node = node->getNext();
		}
	}
}
}
}



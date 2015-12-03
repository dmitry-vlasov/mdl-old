/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Section.cpp                                */
/* Description:     mm cutting section                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_SOURCE_SECTION_CPP_
#define MM_CUT_SOURCE_SECTION_CPP_

#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/cut/source/mm_cut_source.hpp"

namespace mm {
namespace cut {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Section :: Section
	(
		const Source* const source,
		const Chapter* const chapter,
		const Header* const header,
		const Content* const content
	) :
	source_ (source),
	chapter_ (chapter),
	header_ (header),
	content_ (content),
	directory_ ((chapter == NULL) ? source->getDirectory() : chapter->getDirectory()),
	name_ (header->getString()),
	path_ (),
	previous_ (NULL) {
		path_ << directory_ << name_ << "." << Config :: metamathExtension();
	}
	Section :: ~ Section()
	{
		deleteAggregateObject (header_);
		deleteAggregateObject (content_);
	}

	inline const String&
	Section :: getDirectory() const{
		return directory_;
	}
	inline const String&
	Section :: getName() const{
		return name_;
	}
	inline const String&
	Section :: getPath() const{
		return path_;
	}
	void
	Section :: write() const
	{
		Output output (path_);
		output.open();
		String& string = output.buffer();
		if (previous_ != NULL) {
			previous_->writeInclusion (string);
		}
		show (string);
		output.close();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// cut :: Includable implementation
	void
	Section :: writeInclusion (String& string) const
	{
		string << mm :: Token :: inclusionBegin_ << space;
		string << path_ << space;
		string << mm :: Token :: inclusionEnd_ << endLine;
		string << endLine;
	}
	const Includable*
	Section :: getPrevious() const {
		return previous_;
	}
	void
	Section :: setPrevious (const Includable* previous) const {
		previous_ = previous;
	}

	// object :: Object implementation
	void
	Section :: commitSuicide() {
		delete this;
	}
	Size_t
	Section :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (header_);
		volume += getAggregateVolume (content_);
		volume += directory_.getVolume();
		volume += name_.getVolume();
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Section :: getSizeOf() const {
		return sizeof (Section);
	}
	void
	Section :: show (String& string) const
	{
		string << Token :: sectionBegin_ << endLine;
		string << tab; header_->show (string);
		string << Token :: sectionEnd_ << endLine;
		content_->show (string);
	}
}
}
}

#endif /*MM_CUT_SOURCE_SECTION_CPP_*/

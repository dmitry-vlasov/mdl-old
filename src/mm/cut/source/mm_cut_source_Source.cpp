/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Source.cpp                                 */
/* Description:     mm cutting source file                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_SOURCE_SOURCE_CPP_
#define MM_CUT_SOURCE_SOURCE_CPP_

#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/cut/source/mm_cut_source.hpp"

namespace mm {
namespace cut {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source
	(
		const Header* const header,
		const Content* const content
	) :
	header_ (header),
	content_ (content),
	chapters_ (),
	sections_ (),
	directory_ (),
	name_ (header->getString()),
	path_ ()
	{
		if (Config :: getTarget().isUndefined()) {
			directory_ << name_ << chars :: DIR_DELIMITER;
			path_ << directory_ << name_ << "." << Config :: metamathExtension();
		} else {
			const Config :: Path_& path = Config :: getTarget();
			for (Config :: Path_ :: Index_ i = 0; i < path.getDepth(); ++ i) {
				directory_ << path.getDirectory (i) << chars :: DIR_DELIMITER;
			}
			path_ << directory_ << path.getName() << "." << Config :: metamathExtension();
		}
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (header_);
		deleteAggregateObject (content_);
	}

	inline const String&
	Source :: getDirectory() const{
		return directory_;
	}
	inline const String&
	Source :: getName() const{
		return name_;
	}
	inline const String&
	Source :: getPath() const{
		return path_;
	}

	inline void
	Source :: addChapter (const Chapter* chapter) {
		chapters_.addLast (chapter);
	}
	inline void
	Source :: addSection (const Section* section) {
		sections_.addLast (section);
	}
	void
	Source :: write() const
	{
		writeSelf();
		writeSections();
		writeChapters();
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
		volume += getAggregateVolume (header_);
		volume += getAggregateVolume (content_);
		volume += chapters_.getVolume();
		volume += sections_.getVolume();
		volume += directory_.getVolume();
		volume += name_.getVolume();
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String& string) const
	{
		string << "$(\n*********************" << endLine;
		string << tab; header_->show (string);
		string << "*********************\n$)" << endLine;
		content_->show (string);
	}

	void
	Source :: writeSelf() const
	{
		system :: createDirectory (directory_.c_str());
		Output output (path_);
		output.open();
		String& string = output.buffer();
		show (string);

		const Sections_ :: Node_*
			sNode = sections_.getFirst();
		while (sNode != NULL) {
			const Section*
				section = sNode->getValue();
			section->writeInclusion (string);
			sNode = sNode->getNext();
		}
		const Chapters_ :: Node_*
			cNode = chapters_.getFirst();
		while (cNode != NULL) {
			const Chapter*
				chapter = cNode->getValue();
			chapter->writeInclusion (string);
			cNode = cNode->getNext();
		}
		output.close();
	}
	inline void
	Source :: writeSections() const
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
	inline void
	Source :: writeChapters() const
	{
		const Chapters_ :: Node_*
			node = chapters_.getFirst();
		while (node != NULL) {
			const Chapter*
				chapter = node->getValue();
			chapter->write();
			node = node->getNext();
		}
	}
}
}
}

#endif /*MM_CUT_SOURCE_SOURCE_CPP_*/

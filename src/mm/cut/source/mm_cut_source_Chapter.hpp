/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Chapter.hpp                                */
/* Description:     mm cutting chapter                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_SOURCE_CHAPTER_HPP_
#define MM_CUT_SOURCE_CHAPTER_HPP_

#include "mm/cut/interface/mm_cut_interface.hpp"
#include "mm/cut/source/mm_cut_source.dpp"

namespace mm {
namespace cut {
namespace source {

class Chapter :
	public Includable,
	public Scalar<Chapter> {
public :
	Chapter
	(
		const Source* const,
		const Header* const,
		const Content* const
	);
	virtual ~ Chapter();

	const String& getDirectory() const;
	const String& getName() const;
	const String& getPath() const;

	void addSection (const Section*);
	void write() const;

	// cut :: Includable interface
	virtual void writeInclusion (String&) const;
	virtual const Includable* getPrevious() const;
	virtual void setPrevious (const Includable*) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		List
		<
			const Section,
			storage :: ByPointer,
			allocator :: Heap
		>
		Sections_;

	void writeSelf() const;
	void writeSections() const;

	const Source* const source_;
	const Header* const header_;
	const Content* const content_;
	Sections_ sections_;

	String directory_;
	String name_;
	String path_;
	mutable const Includable* previous_;
};

}
}
}

#endif /*MM_CUT_SOURCE_CHAPTER_HPP_*/

/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Source.hpp                                 */
/* Description:     mm cutting source file                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_SOURCE_SOURCE_HPP_
#define MM_CUT_SOURCE_SOURCE_HPP_

#include "mm/interface/mm_interface.hpp"
#include "mm/cut/source/mm_cut_source.dpp"

namespace mm {
namespace cut {
namespace source {

class Source :
	public object :: Object,
	public Scalar<Source> {
public :
	Source
	(
		const Header* const,
		const Content* const
	);
	virtual ~ Source();

	const String& getDirectory() const;
	const String& getName() const;
	const String& getPath() const;

	void addChapter (const Chapter*);
	void addSection (const Section*);
	void write() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		List
		<
			const Chapter,
			storage :: ByPointer,
			allocator :: Heap
		>
		Chapters_;
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
	void writeChapters() const;

	const Header* const header_;
	const Content* const content_;
	Chapters_ chapters_;
	Sections_ sections_;

	String directory_;
	String name_;
	String path_;
};

}
}
}

#endif /*MM_CUT_SOURCE_SOURCE_HPP_*/

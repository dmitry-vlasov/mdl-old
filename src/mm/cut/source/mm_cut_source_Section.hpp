/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Section.hpp                                */
/* Description:     mm cutting section                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/cut/interface/mm_cut_interface.hpp"
#include "mm/cut/source/mm_cut_source.dpp"

namespace mm {
namespace cut {
namespace source {

class Section :
	public Includable,
	public Scalar<Section> {
public :
	Section
	(
		const Source* const,
		const Chapter* const,
		const Header* const,
		const Content* const
	);
	virtual ~ Section();

	const String& getDirectory() const;
	const String& getName() const;
	const String& getPath() const;

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
	const Source* const source_;
	const Chapter* const chapter_;
	const Header* const header_;
	const Content* const content_;

	String directory_;
	String name_;
	String path_;
	mutable const Includable* previous_;
};

}
}
}



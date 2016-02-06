/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Content.hpp                                */
/* Description:     mm cutting block content                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/interface/mm_interface.hpp"
#include "mm/cut/source/mm_cut_source.dpp"

namespace mm {
namespace cut {
namespace source {

class Content :
	public object :: Object,
	public Scalar<Content> {
public :
	Content
	(
		const Location&,
		const String&
	);
	virtual ~ Content();

	void write (std :: ostream&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const Location location_;
	const String   string_;
};

}
}
}



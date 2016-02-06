/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_source_Header.hpp                                 */
/* Description:     mm cutting block header                                  */
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

class Header :
	public object :: Object,
	public Scalar<Header> {
public :
	Header
	(
		const Location&,
		const String&
	);
	virtual ~ Header();

	const String& getString() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void nomalize();

	const Location location_;
	String string_;

	enum {
		REPLACE_ARRAY_SIZE = 16
	};
	static const char range_ [REPLACE_ARRAY_SIZE];
	static const char image_ [REPLACE_ARRAY_SIZE];
};

}
}
}



/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Bit.hpp                                   */
/* Description:     bit container                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace container {

template<int D = 64, class T = U_int64_t>
class Bit {
public :
	enum {
		DIMENSION = D
	};
	typedef T Type_;
	Bit ();
	Bit (const Type_);
	Bit (const Bit&);
	~ Bit();

	bool getValue (const char) const;
	void setValue (const char, const bool = true);
	void set (const Type_);
	Type_ get () const;

	void operator = (const Bit&);
	bool operator == (const Bit&) const;
	bool operator != (const Bit&) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	typedef
		type :: Assert<DIMENSION <= sizeof(Type_) >
		_Check_;

	Type_ bits_;
};

}
}



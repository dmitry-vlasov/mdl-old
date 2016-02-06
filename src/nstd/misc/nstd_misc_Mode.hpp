/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Mode.hpp                                       */
/* Description:     class for the show modes                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace misc {

class Mode {
public :
	enum {
		CARDINALITY = 64 // number of bits in a mode
	};
	Mode ();
	template<class A>
	Mode (const String<A>&);
	Mode (const Mode&);

	bool isPlain() const;
	bool getValue (const char) const;
	void setValue (const char, const bool = true);

	void operator = (const Mode&);
	bool operator == (const Mode&) const;
	bool operator != (const Mode&) const;

	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class A>
	void show (String<A>&) const;

private :
	template<class A>
	friend String<A>&
	operator << (String<A>&, const Mode&);
	friend Mode&
	operator << (Mode&, const char);
	template<class A>
	friend Mode&
	operator << (Mode&, const String<A>&);

	typedef
		container :: Bit<CARDINALITY>
		Bits_;

	Bits_ bits_;
};

	template<class A>
	String<A>&
	operator << (String<A>&, const Mode&);
	Mode&
	operator << (Mode&, const char);
	template<class A>
	Mode&
	operator << (Mode&, const String<A>&);
}
}



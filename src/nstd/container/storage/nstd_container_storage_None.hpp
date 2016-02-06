/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_None.hpp                          */
/* Description:     speculative storage policy                               */
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
namespace storage {

template
<
	class T	// Stored type
>
class None {
public :
	typedef T Type_;
	typedef const T& Argument_;
	typedef T Value_;
	typedef T& Reference_;
	typedef const T& const_Reference_;

	None();
    None (Argument_);
    None (const None&);
    ~ None();

    bool operator == (const None&) const;
	bool operator != (const None&) const;
	void operator = (const None&);

    void undefine();
	void clear();
	void erase();
	void init();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;
};

	template<class T, class S>
	S&
	operator << (S&, const None<T>&);
}
}
}



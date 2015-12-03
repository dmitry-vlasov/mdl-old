/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_size.hpp                                            */
/* Description:     size (in bytes) constants                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_SIZE_HPP_
#define NSTD_SIZE_HPP_

namespace nstd {
namespace size {

	typedef nstd :: Size_t Size;

	const Size
		BYTE = 1;
	const Size
		KILOBYTE = BYTE * 1024;
	const Size
		MEGABYTE = KILOBYTE * 1024;
	const Size
		GIGABYTE = MEGABYTE * 1024;
	const Size
		TERABYTE = GIGABYTE * 1024;
}
	using size :: Size;
}

#endif /*NSTD_SIZE_HPP_*/

/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_storage.hpp                                     */
/* Description:     container storage policies                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_TYPES_STORAGE_HPP_
#define MM_TYPES_STORAGE_HPP_

namespace mm {
namespace storage {

	using nstd :: container :: storage :: ByValue;
	using nstd :: container :: storage :: ByPointer;
	using nstd :: container :: storage :: ByInheritance;
}
}

#endif /*MM_TYPES_STORAGE_HPP_*/
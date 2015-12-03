/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_storage.hpp                                    */
/* Description:     basic storage policies                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_STORAGE_HPP_
#define MDL_TYPES_STORAGE_HPP_

namespace mdl {
namespace storage {

	using nstd :: container :: storage :: ByValue;
	using nstd :: container :: storage :: ByPointer;
	using nstd :: container :: storage :: ByWeakPointer;
	using nstd :: container :: storage :: ByInheritance;
}
}

#endif /*MDL_TYPES_STORAGE_HPP_*/

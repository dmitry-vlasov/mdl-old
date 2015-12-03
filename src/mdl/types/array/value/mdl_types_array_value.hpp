/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_array_value.hpp                                */
/* Description:     basic types for arrays of values                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_ARRAY_VALUE_HPP_
#define MDL_TYPES_ARRAY_VALUE_HPP_

namespace mdl {
namespace array {
namespace value {

	typedef
		Array<mdl :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Array<mdl :: value :: Real, storage :: ByValue, allocator :: Heap>
		Real;
}
}
}

#endif /*MDL_TYPES_ARRAY_VALUE_HPP_*/

/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_set_value.hpp                                  */
/* Description:     basic types for sets of values                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_SET_VALUE_HPP_
#define MDL_TYPES_SET_VALUE_HPP_

namespace mdl {
namespace set {
namespace value {

	typedef
		Set<mdl :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Set<mdl :: value :: Literal, storage :: ByValue, allocator :: Heap>
		Literal;
	typedef
		Set<mdl :: value :: Name, storage :: ByValue, allocator :: Heap>
		Name;
	typedef
		Set<mdl :: value :: Kind, storage :: ByValue, allocator :: Heap>
		Kind;
}
}
}

#endif /*MDL_TYPES_SET_VALUE_HPP_*/

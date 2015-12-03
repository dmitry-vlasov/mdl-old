/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_vector_value.hpp                               */
/* Description:     basic types for vectors of values                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_VECTOR_VALUE_HPP_
#define MDL_TYPES_VECTOR_VALUE_HPP_

namespace mdl {
namespace vector {
namespace value {

	typedef
		Vector<bool, storage :: ByValue, allocator :: Heap>
		Bool;
	typedef
		Vector<mdl :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Vector<mdl :: value :: Literal, storage :: ByValue, allocator :: Heap>
		Literal;
	typedef
		Vector<mdl :: value :: Name, storage :: ByValue, allocator :: Heap>
		Name;
	typedef
		Vector<mdl :: value :: Kind, storage :: ByValue, allocator :: Heap>
		Kind;
	typedef
		Vector<mdl :: value :: Real, storage :: ByValue, allocator :: Heap>
		Real;
}
}
}

#endif /*MDL_TYPES_VECTOR_VALUE_HPP_*/

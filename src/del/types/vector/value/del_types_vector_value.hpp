/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_vector_value.hpp                               */
/* Description:     basic types for vectors of values                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_VECTOR_VALUE_HPP_
#define DEL_TYPES_VECTOR_VALUE_HPP_

namespace del {
namespace vector {
namespace value {

	typedef
		Vector<del :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Vector<del :: value :: Long, storage :: ByValue, allocator :: Heap>
		Long;
	typedef
		Vector<del :: value :: Relation, storage :: ByValue, allocator :: Heap>
		Relation;
	typedef
		Vector<del :: value :: Theory, storage :: ByValue, allocator :: Heap>
		Theory;
	typedef
		Vector<del :: value :: Signature, storage :: ByValue, allocator :: Heap>
		Signature;
	typedef
		Vector<del :: value :: Variable, storage :: ByValue, allocator :: Heap>
		Variable;
	typedef
		Vector<del :: value :: Symbol, storage :: ByValue, allocator :: Heap>
		Symbol;
}
}
}

#endif /*DEL_TYPES_VECTOR_VALUE_HPP_*/

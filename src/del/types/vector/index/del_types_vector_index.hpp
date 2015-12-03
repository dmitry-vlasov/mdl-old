/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_vector_index.hpp                               */
/* Description:     basic types for vectors of indexes                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_VECTOR_INDEX_HPP_
#define DEL_TYPES_VECTOR_INDEX_HPP_

namespace del {
namespace vector {
namespace index {

	typedef
		Vector<del :: value :: Relation, storage :: ByValue, allocator :: Heap>
		Relation;
	typedef
		Vector<del :: value :: Theory, storage :: ByValue, allocator :: Heap>
		Theory;
	typedef
		Vector<del :: value :: Variable, storage :: ByValue, allocator :: Heap>
		Variable;
}
}
}

#endif /*DEL_TYPES_VECTOR_INDEX_HPP_*/

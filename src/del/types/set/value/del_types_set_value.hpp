/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_set_value.hpp                                  */
/* Description:     basic types for sets of values                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_SET_VALUE_HPP_
#define DEL_TYPES_SET_VALUE_HPP_

namespace del {
namespace set {
namespace value {

	typedef
		Set<del :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Set<del :: value :: Long, storage :: ByValue, allocator :: Heap>
		Long;
	typedef
		Set<del :: value :: Relation, storage :: ByValue, allocator :: Heap>
		Relation;
	typedef
		Set<del :: value :: Theory, storage :: ByValue, allocator :: Heap>
		Theory;
	typedef
		Set<del :: value :: Variable, storage :: ByValue, allocator :: Heap>
		Variable;
}
}
}

#endif /*DEL_TYPES_SET_VALUE_HPP_*/

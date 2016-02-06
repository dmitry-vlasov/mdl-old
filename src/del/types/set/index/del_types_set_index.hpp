/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_set_index.hpp                                  */
/* Description:     basic types for sets of indexes                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace set {
namespace index {

	typedef
		Set<del :: value :: Theory, storage :: ByValue, allocator :: Heap>
		Theory;
	typedef
		Set<del :: value :: Relation, storage :: ByValue, allocator :: Heap>
		Relation;
	typedef
		Set<del :: value :: Integer, storage :: ByValue, allocator :: Heap>
		Integer;
	typedef
		Set<del :: value :: Variable, storage :: ByValue, allocator :: Heap>
		Variable;
}
}
}



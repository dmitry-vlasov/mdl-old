/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_value_pair.hpp                                 */
/* Description:     basic types for pairs of values                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_VALUE_PAIR_HPP_
#define DEL_TYPES_VALUE_PAIR_HPP_

#include "del/types/pair/del_types_pair.hpp"

namespace del {
namespace value {
namespace pair {

	// Basic type for pair of integer
	typedef
		del :: pair :: Pair<value :: Integer>
		Integer;

	// type for pair of 64 bit integer values
	typedef
		del :: pair :: Pair<value :: Long>
		Long;

	// Value type for pair of relation names
	typedef
		del :: pair :: Pair<value :: Relation>
		Relation;

	// Value type for pair of theory names
	typedef
		del :: pair :: Pair<value :: Theory>
		Theory;

	// Value type for pair of signature names
	typedef
		del :: pair :: Pair<value :: Signature>
		Signature;

	// Value type for pair of propositional variables
	typedef
		del :: pair :: Pair<value :: Variable>
		Variable;

	// Value type for pair of signature symbols
	typedef
		del :: pair :: Pair<value :: Symbol>
		Symbol;
}
}
}

#endif /*DEL_TYPES_VALUE_PAIR_HPP_*/

/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_mal_Iterator.cpp               */
/* Description:     symbol array iterator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_ITERATOR_CPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_ITERATOR_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Iterator :: Iterator
	(
		vector :: Symbol& symbolArray,
		const del :: Signature* delta
	) :
	dimension_ (0),
	symbolArray_ (symbolArray),
	delta_ (delta),
	inDelta_ (symbolArray.getSize()),
	signs_ (symbolArray.getSize())
	{
		for (value :: Integer i = 0; i < symbolArray.getSize(); ++ i) {
			const Symbol& symbol = symbolArray_ [i];
			if (delta_->containsSymbol (symbol)) {
				inDelta_.add (i);
				signs_.add (false);
				++ dimension_;
			}
		}
	}
	inline
	Iterator :: Iterator (const Iterator& array) :
	dimension_ (array.dimension_),
	symbolArray_ (array.symbolArray_),
	delta_ (array.delta_),
	inDelta_ (array.inDelta_),
	signs_ (array.signs_) {
	}
	Iterator :: ~ Iterator() {
	}

	bool
	Iterator :: isTrivial() const {
		return (dimension_ == 0);
	}
	const Symbol&
	Iterator :: getSymbol (const value :: Integer i) const {
		return symbolArray_ [i];
	}
	bool
	Iterator :: operator ++()
	{
		const bool result = increment();
		realizeSigns();
		return result;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Iterator :: commitSuicide() {
		delete this;
	}
	void
	Iterator :: show (String& s) const {
	}
	Size_t
	Iterator :: getVolume() const {
		return 0;
	}
	Size_t
	Iterator :: getSizeOf() const {
		return sizeof (Iterator);
	}

	/****************************
	 *		Protected members
	 ****************************/


	/****************************
	 *		Private members
	 ****************************/

	bool
	Iterator :: increment (const value :: Integer d)
	{
		if (d == dimension_) {
			return false;
		}
		if (!signs_ [d]) {
			signs_[d] = true;
			return true;
		} else {
			signs_ [d] = false;
			return increment (d + 1);
		}

		/*const value :: Integer
			index = indexVector_.getValue (d);
		const value :: Integer
			boundary = matrix_.getValue (d)->getSize();

		if (index < boundary - 1) {
			++ indexVector_.getReference (d);
			return false;
		} else {
			indexVector_.getReference (d) = 0;
			return increment (d + 1);
		}*/
	}
	void
	Iterator :: realizeSigns()
	{
		for (value :: Integer i = 0; i < dimension_; ++ i) {
			const value :: Integer index = inDelta_ [i];
			const bool sign = signs_ [i];
			symbolArray_[index].setAsterisk (sign);
		}
	}


	/*bool
	Iterator :: increment (const index :: Arity d)
	{
		const value :: Integer
			index = indexVector_.getValue (d);
		const value :: Integer
			boundary = matrix_.getValue (d)->getSize();

		if (index < boundary - 1) {
			++ indexVector_.getReference (d);
			return false;
		} else {
			indexVector_.getReference (d) = 0;
			return increment (d + 1);
		}
	}*/
}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_ITERATOR_CPP_*/

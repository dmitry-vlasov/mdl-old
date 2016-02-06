/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Pair.hpp                */
/* Description:     modifier for iterator decart product                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/modifier/mdl_expression_iterator_modifier_Memory.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I_1, class I_2>
class Pair {
public :
	typedef I_1 Iterator_1_;
	typedef I_2 Iterator_2_;
	typedef
		typename Iterator_1_ :: Node_
		Node_1_;
	typedef
		typename Iterator_2_ :: Node_
		Node_2_;
	typedef
		Pair<Iterator_2_, Iterator_1_>
		InversePair_;

	Pair();
	Pair (const Iterator_1_, const Iterator_2_);
	Pair (const Pair&);

	InversePair_ inverse() const;

	bool operator == (const Node_1_* const) const;
	bool operator != (const Node_1_* const) const;
	bool operator == (const Pair&) const;
	bool operator != (const Pair&) const;
	void operator = (const Pair&);

	bool isFinal() const;
	bool isTerminal() const;
	bool isEqual() const;

	void operator ++ ();
	void operator -- ();

	void operator + ();
	void operator - ();

	void recall();

	Iterator_1_ getFirst() const;
	Iterator_2_ getSecond() const;

	Iterator_1_& first();
	Iterator_2_& second();

protected :
	Memory<Iterator_1_> iterator_1_;
	Memory<Iterator_2_> iterator_2_;
};

}
}
}
}



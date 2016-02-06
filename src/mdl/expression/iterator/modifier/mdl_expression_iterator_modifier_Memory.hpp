/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Memory.hpp              */
/* Description:     memory modifier for recallable iterator                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I>
class Memory : public I {
	typedef I Iterator_;
	typedef
		typename Iterator_ :: Node_
		Node_;
public :
	Memory ();
	Memory (const Iterator_&);
	Memory (const Memory&);

	bool operator == (const Node_*) const;
	bool operator != (const Node_*) const;
	void operator = (const Node_*);

	void operator = (const Memory&);
	bool operator == (const Memory&) const;
	bool operator != (const Memory&) const;

	void remember();
	void recall();

private :
	Iterator_ back_;
};

}
}
}
}



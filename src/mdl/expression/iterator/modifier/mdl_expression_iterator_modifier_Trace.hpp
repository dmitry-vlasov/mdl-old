/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Trace.hpp               */
/* Description:     modifier for traceable iterator                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_HPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_HPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I>
class Trace : public I {
	typedef I Iterator_;
	typedef
		typename Iterator_ :: Node_
		Node_;
public :
	Trace ();
	Trace (const Iterator_&);
	Trace (const Trace&);

	bool operator == (const Node_*) const;
	bool operator != (const Node_*) const;
	void operator = (const Node_*);

	void operator = (const Trace&);
	bool operator == (const Trace&) const;
	bool operator != (const Trace&) const;

	void operator ++ ();
	void operator -- ();
	void operator + ();
	void operator - ();

	void shiftBack();

private :
	Iterator_ back_;
};

}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_TRACE_HPP_*/

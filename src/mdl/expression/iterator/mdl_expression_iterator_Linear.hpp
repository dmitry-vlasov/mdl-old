/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_Linear.hpp                       */
/* Description:     linear iterator                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_LINEAR_HPP_
#define MDL_EXPRESSION_ITERATOR_LINEAR_HPP_

#include "mdl/expression/direction/mdl_expression_direction.hpp"
#include "mdl/expression/iterator/mdl_expression_iterator_Singleton.hpp"

namespace mdl {
namespace expression {
namespace iterator {

template<class N>
class Linear : public Singleton<N> {
	typedef
		Singleton<N>
		Ancestor_;
public :
	typedef
		typename Ancestor_ :: Node_
		Node_;

	Linear ();
	Linear (Node_*);
	Linear (const Linear&);

	void operator ++();
	void operator --();

	void dump() const;
};

}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_LINEAR_HPP_*/

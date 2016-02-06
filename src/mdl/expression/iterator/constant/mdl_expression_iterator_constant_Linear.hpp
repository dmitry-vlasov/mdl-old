/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Linear.hpp              */
/* Description:     linear const iterator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/constant/mdl_expression_iterator_constant_Singleton.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

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
	Linear (const Node_*);
	Linear (const typename iterator :: Linear<N>&);
	Linear (const Linear&);

	void operator ++();
	void operator -- ();

	void dump() const;
};

}
}
}
}



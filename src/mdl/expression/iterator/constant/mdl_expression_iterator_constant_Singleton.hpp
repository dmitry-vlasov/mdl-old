/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Singleton.hpp           */
/* Description:     singleton (0-dimensional) const iterator                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/mdl_expression.dpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

template<class N>
class Singleton {
public :
	typedef N Node_;

	Singleton ();
	Singleton (const Node_*);
	Singleton (const typename iterator :: Singleton<N>&);
	Singleton (const Singleton&);

	bool operator == (const Node_*) const;
	bool operator != (const Node_*) const;

	bool operator == (const Singleton&) const;
	bool operator != (const Singleton&) const;
	bool operator == (const typename iterator :: Singleton<N>&) const;
	bool operator != (const typename iterator :: Singleton<N>&) const;
	void operator = (const Singleton&);

	const Node_& operator * () const;
	const Node_* operator -> () const;
	const Node_* getNode() const;
	bool isNull() const;

	template<Direction>
	bool isTerminal () const;
	void setNull();

	void dump() const;
	void show (String&) const;

protected :
	friend class iterator :: Singleton<N>;
	const Node_* node_;
};

	template<class N>
	String&
	operator << (String&, const Singleton<N>&);
}
}
}
}



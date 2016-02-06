/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Pair.hpp                         */
/* Description:     a positive node - pair of concepts                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/model/node/positive/del_model_node_positive_Positive.hpp"

namespace del {
namespace model {
namespace node {
namespace positive {

template<class A>
class Pair :
	public Positive<A>,
	public Scalar<Pair<A>, A> {
public :
	typedef A Allocator_;
	typedef Positive<A> Positive_;

	Pair();
	Pair
	(
		Model*,
		const Symbol,
		const Symbol,
		const value :: Integer
	);
	Pair
	(
		Model*,
		const Symbol,
		const Symbol,
		const Node* = NULL,
		const Formula* = NULL
	);
	template<class A1>
	Pair (const Pair<A1>&, Model*);
	virtual ~ Pair();

	bool isEqual (const Symbol, const Symbol) const;
	template<class A1>
	void operator = (const Pair<A1>&);

	bool operator == (const Pair&) const;
	bool operator != (const Pair&) const;
	bool operator < (const Pair&) const;
	bool operator > (const Pair&) const;

	Symbol getFirst() const;
	Symbol getSecond() const;

	void setFirst (const Symbol);
	void setSecond (const Symbol);

	// del :: model :: Positive interface
	virtual Symbol getVariable() const;
	virtual pair :: Symbol getPair() const;

	// del :: model :: Node interface
	virtual bool isEqual (const Node*, const Formula*) const;
	virtual bool isEqual (const Node* [], const value :: Integer, const Formula*) const;
	virtual bool fitsUntheory (const del :: set :: Formula*) const;
	virtual void showSuccessBranch (set :: Node*) const;
	virtual const Term* evalInterpolant (const Signature*) const;
	virtual Node* clone (Model*) const;
	virtual bool isEqual (const Node*, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Pair;

	Symbol variable_1_;
	Symbol variable_2_;
};

}
}
}
}



/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Singleton.hpp                    */
/* Description:     a positive node - singleton (concept)                    */
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
class Singleton :
	public Positive<A>,
	public Scalar<Singleton<A>, A> {
public :
	typedef A Allocator_;
	typedef Positive<A> Positive_;

	Singleton ();
	Singleton (Model*, const Symbol, const value :: Integer);
	Singleton
	(
		Model*,
		const Symbol,
		const Node*,
		const Formula*
	);
	Singleton
	(
		Model*,
		const Symbol,
		const Node* [],
		const value :: Integer,
		const Formula*
	);
	template<class A1>
	Singleton (const Singleton<A1>&, Model*);
	virtual ~ Singleton();

	bool isEqual (const Symbol) const;

	bool operator == (const Singleton&) const;
	bool operator != (const Singleton&) const;
	bool operator < (const Singleton&) const;
	bool operator > (const Singleton&) const;
	bool operator <= (const Singleton&) const;
	bool operator >= (const Singleton&) const;

	bool operator == (const Symbol) const;
	bool operator != (const Symbol) const;
	bool operator < (const Symbol) const;
	bool operator > (const Symbol) const;
	bool operator <= (const Symbol) const;
	bool operator >= (const Symbol) const;

	void setSymbol (const Symbol);

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
	friend class Singleton;

	Symbol variable_;
};

}
}
}
}



/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_Negative.hpp                     */
/* Description:     a negative node container                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_NEGATIVE_HPP_
#define DEL_MODEL_NODE_NEGATIVE_NEGATIVE_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace node {
namespace negative {

template<class A>
class Negative : public del :: model :: Negative {
public :
	typedef A Allocator_;
	typedef
		typename del :: model :: Negative
		Negative_;

	Negative (Model*);
	Negative (Model*, const Formula*, const value :: Integer);
	Negative (Model*, const Node*, const Formula*);
	Negative (Model*, const Node* [], const value :: Integer, const del :: Formula*);
	template<class A1>
	Negative (const Negative<A1>&, Model*);
	virtual ~ Negative();

	void add (const Node*);

	bool operator == (const Negative&) const;
	bool operator != (const Negative&) const;

	// del :: model :: Negative interface
	virtual const del :: Formula* getFormula() const;

	// del :: model :: Node interface
	virtual bool isEqual (const Node*, const Formula*) const;
	virtual bool isEqual (const Node* [], const value :: Integer, const Formula*) const;
	virtual bool fitsUntheory (const del :: set :: Formula*) const;
	virtual void showSuccessBranch (set :: Node*) const;
	virtual const Term* evalInterpolant (const Signature*) const = 0;
	virtual Node* clone (Model*) const = 0;
	virtual bool isEqual (const Node*, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;
	virtual void show (String&) const;

protected :
	template<class>
	friend class Negative;

	typedef
		del :: vector :: Vector
		<
			const Node*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	void cloneNodeVector (Model*) const;

	const Formula* formula_;
	NodeVector_ nodeVector_;
};

}
}
}
}

#endif /*DEL_MODEL_NODE_NEGATIVE_NEGATIVE_HPP_*/

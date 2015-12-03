/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_node_negative_Conjunction.hpp                 */
/* Description:     a negative node container of type: conjunction           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_CONJUNCTION_HPP_
#define DEL_MODEL_NODE_NEGATIVE_CONJUNCTION_HPP_

#include "del/model/node/negative/del_model_node_negative_Negative.hpp"

namespace del {
namespace model {
namespace node {
namespace negative {

template<class A>
class Conjunction :
	public Negative<A>,
	public Scalar<Conjunction<A>, A> {
public :
	typedef A Allocator_;
	typedef Negative<Allocator_> Negative_;

	Conjunction (Model*);
	Conjunction (Model*, const Formula*, const value :: Integer);
	Conjunction (Model*, const Node*, const Formula*);
	Conjunction (Model*, const Node* [], const value :: Integer, const Formula*);
	template<class A1>
	Conjunction (const Conjunction<A1>&, Model*);
	virtual ~ Conjunction();

	// del :: model :: Node interface
	virtual const Term* evalInterpolant (const Signature*) const;
	virtual Node* clone (Model*) const;
	virtual bool isEqual (const Node*, const bool show = false) const;

	//virtual void show (std :: ostream&) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;
	virtual void show (String&) const;
};

}
}
}
}

#endif /*DEL_MODEL_NODE_NEGATIVE_CONJUNCTION_HPP_*/

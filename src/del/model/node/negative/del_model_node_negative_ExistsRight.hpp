/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_ExistsRight.hpp                  */
/* Description:     a negative node container of type: right exists          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_EXISTS_RIGHT_HPP_
#define DEL_MODEL_NODE_NEGATIVE_EXISTS_RIGHT_HPP_

#include "del/model/node/negative/del_model_node_negative_Negative.hpp"

namespace del {
namespace model {
namespace node {
namespace negative {

template<class A>
class ExistsRight :
	public Negative<A>,
	public Scalar<ExistsRight<A>, A> {
public :
	typedef A Allocator_;
	typedef Negative<Allocator_> Negative_;

	ExistsRight (Model*);
	ExistsRight (Model*, const Formula*, const value :: Integer);
	ExistsRight (Model*, const Node*, const Formula*);
	ExistsRight (Model*, const Node* [], const value :: Integer, const del :: Formula*);
	template<class A1>
	ExistsRight (const ExistsRight<A1>&, Model*);
	virtual ~ ExistsRight();

	// del :: model :: Node interface
	virtual const Term* evalInterpolant (const Signature*) const;
	virtual Node* clone (Model*) const;
	virtual bool isEqual (const Node*, const bool show = false) const;

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

#endif /*DEL_MODEL_NODE_NEGATIVE_EXISTS_RIGHT_HPP_*/

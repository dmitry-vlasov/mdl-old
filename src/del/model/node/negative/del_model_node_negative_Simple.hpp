/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_Simple.hpp                       */
/* Description:     a negative node container of type: simple                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/model/node/negative/del_model_node_negative_Negative.hpp"

namespace del {
namespace model {
namespace node {
namespace negative {

template<class A>
class Simple :
	public Negative<A>,
	public Scalar<Simple<A>, A> {
public :
	typedef A Allocator_;
	typedef Negative<Allocator_> Negative_;

	Simple (Model*);
	Simple (Model*, const Formula*, const value :: Integer);
	Simple (Model*, const Node*, const Formula*);
	Simple (Model*, const Node* [], const value :: Integer, const Formula*);
	template<class A1>
	Simple (const Simple<A1>&, Model*);
	virtual ~ Simple();

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



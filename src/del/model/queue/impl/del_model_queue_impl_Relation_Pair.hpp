/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Relation_Pair.hpp                   */
/* Description:     pair of concepts as elements of relations                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue{
namespace impl {

template<class A>
class Relation<A> :: Pair :
	public Object,
	public Scalar<Pair>{
public :
	Pair ();
	Pair (const value :: Variable, const value :: Variable);
	Pair (const Pair&);
	virtual ~ Pair();

	bool operator < (const Pair&) const;
	bool operator > (const Pair&) const;
	bool operator == (const Pair&) const;
	void operator = (const Pair&);

	// del :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;

	value :: Variable x_;
	value :: Variable y_;
};

}
}
}
}



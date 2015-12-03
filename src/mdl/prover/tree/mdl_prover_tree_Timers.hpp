/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Timers.hpp                               */
/* Description:     timers for proving process                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_TIMERS_HPP_
#define MDL_PROVER_TREE_TIMERS_HPP_

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace prover {
namespace tree {

template<class A>
class Timers :
	public object :: Object,
	public Scalar<Timers<A>, A> {
public :
	typedef A Allocator_;

	Timers();
	virtual ~ Timers();

	bool refresh();
	bool timeIsOver() const;

	void start();
	void mark();
	void stop();
	void recount();

	void switchOff();
	void switchOn();

	void setLimit (const Time timeLimit);

	Time limit() const;

	Timer& growUp();
	Timer& growDown();

	const Timer& prove() const;
	const Timer& refresh() const;
	const Timer& growUp() const;
	const Timer& growDown() const;

	bool wasRefreshed() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	bool isOn_;
	Time  limitFirst_;
	Time  limitSecond_;

	mutable Timer prove_;
	Timer refresh_;
	Timer growUp_;
	Timer growDown_;

	bool  recounted_;
	bool  refreshed_;
};

	template<class A>
	String&
	operator << (String&, const Timers<A>&);
}
}
}

#endif /*MDL_PROVER_TREE_TIMERS_HPP_*/

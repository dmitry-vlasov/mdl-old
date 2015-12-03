/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_domain_Simple.hpp                       */
/* Description:     simple domain element                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_DOMAIN_SIMPLE_HPP_
#define DEL_MODEL_QUEUE_DOMAIN_SIMPLE_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue {
namespace domain {

template<class A = allocator :: Heap>
class Simple :
	public Domain,
	public Scalar<Simple<A>, A> {
public :
	typedef A Allocator_;

	Simple
	(
		const del :: Formula*,
		const value :: Variable
	);
	Simple (const Simple&);
	virtual ~ Simple();

	// queue :: Domain interface
	virtual Type getType() const;
	virtual value :: Relation getRelation() const;
	virtual value :: Variable getConcept() const;

	// queue :: Element interface
	virtual const del :: Formula* getFormula() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Simple;

	const del :: Formula*   formula_;
	const value :: Variable concept_;
};

}
}
}
}

#endif /*DEL_MODEL_QUEUE_DOMAIN_SIMPLE_HPP_*/

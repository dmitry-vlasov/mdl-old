/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_range_Exists.hpp                        */
/* Description:     exists range element                                     */
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
namespace queue {
namespace range {

template<class A = allocator :: Heap>
class Exists :
	public Range,
	public Scalar<Exists<A>, A> {
public :
	typedef A Allocator_;

	Exists
	(
		const del :: Formula*,
		const value :: Relation,
		const value :: Variable
	);
	Exists (const Exists&);
	virtual ~ Exists();

	// queue :: Domain interface
	virtual Type getType() const;
	virtual value :: Integer getSize() const;
	virtual value :: Variable getConcept (const value :: Integer = 0) const;
	virtual value :: Relation getRelation() const;

	// queue :: Element interface
	virtual const del :: Formula* getFormula() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Exists;

	const del :: Formula* formula_;
	const value :: Relation relation_;
	const value :: Variable concept_;
};

}
}
}
}



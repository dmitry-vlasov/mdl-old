/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Expansion.hpp                                 */
/* Description:     signature class                                          */
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
namespace source {

template<class A>
class Expansion :
	public del :: Expansion,
	public Scalar<Expansion<A>, A> {
public :
	typedef A Allocator_;
	Expansion (const del :: Signature* const);
	Expansion (const Expansion&);
	virtual ~ Expansion();

	// del :: Expansion interface
	virtual void clear();
	virtual del :: Symbol addPostfixToSymbol (const del :: Symbol&) const;

	// del :: Cloneable interface
	virtual del :: Expansion* clone() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		map :: Scalar
		<
			del :: Symbol,
			del :: Symbol,
			Allocator_
		>
		Map_;

	const del :: Signature* const delta_;
	mutable Map_ map_;

	enum {
		INITIAL_MAP_CAPACITY = 256
	};
};

}
}



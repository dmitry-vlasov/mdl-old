/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_expression_unify_sub_Multyindex.hpp                  */
/* Description:     vector of evidence indexes                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/prover/interface/mdl_prover_interface.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace sub {

template<class C, class T>
class Multyindex {
public :
	typedef C Container_;
	typedef T Types_;
	typedef
		mdl :: vector :: Vector
		<
			const Container_*,
			storage :: ByValue,
			allocator :: Stack
		>
		Matrix_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	Multyindex
	(
		const index :: Arity,
		const Matrix_&
	);

	index :: Arity getDimension() const;
	bool operator ++();
	Evidence_* getValue (const index :: Arity) const;
	value :: Integer getSearchVolume() const;;

	template<class S>
	void show (S&) const;
	void dump() const;

protected :
	typedef
		mdl :: vector :: Vector
		<
			value :: Integer,
			storage :: ByValue,
			allocator :: Stack
		>
		IndexVector_;

	bool increment (const index :: Arity = 0);

	const index :: Arity dimension_;
	const Matrix_& matrix_;
	IndexVector_ indexVector_;
};

	template<class S, class C, class T>
	S&
	operator << (S&, const Multyindex<C, T>&);
	template<class C, class T>
	std :: ostream&
	operator << (std :: ostream&, const Multyindex<C, T>&);
}
}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Unit.ipp                           */
/* Description:     pair of iterators for the simification algorithm         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace simify {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2>
	inline
	Unit<T_1, T_2> :: Unit
	(
		const _Iterator_1_ iterator_1,
		const _Iterator_2_ iterator_2,
		const index :: Step level_1,
		const index :: Step level_2
	) :
	Pair_
	(
		Lengthirator_1_ (iterator_1),
		Lengthirator_2_ (iterator_2)
	),
	level_1_ (level_1),
	level_2_ (level_2) {
	}
	template<class T_1, class T_2>
	inline
	Unit<T_1, T_2> :: Unit (const Unit& unit) :
	Pair_ (unit),
	level_1_ (unit.level_1_),
	level_2_ (unit.level_2_) {
	}

	template<class T_1, class T_2>
	inline typename Unit<T_1, T_2> :: InverseUnit_
	Unit<T_1, T_2> :: inverse () const
	{
		return
			InverseUnit_
			(
				Pair_ :: getSecond(),
				Pair_ :: getFirst(),
				level_2_,
				level_1_
			);
	}

	template<class T_1, class T_2>
	inline bool
	Unit<T_1, T_2> :: isReacheable() const
	{
		return
			Pair_ :: getFirst()->isReacheable (level_1_) &&
			Pair_ :: getSecond()->isReacheable (level_2_);
	}
	template<class T_1, class T_2>
	inline bool
	Unit<T_1, T_2> :: isReplaceable() const {
		return Pair_ :: getFirst()->isReplaceable();
	}
	template<class T_1, class T_2>
	inline bool
	Unit<T_1, T_2> :: isFixed() const
	{
		return
			Pair_ :: getFirst()->isFixed() &&
			Pair_ :: getSecond()->isFixed();
	}

	template<class T_1, class T_2>
	inline void
	Unit<T_1, T_2> :: operator = (const Unit& unit)
	{
		Pair_ :: operator = (unit);
		level_1_ = unit.level_1_;
		level_2_ = unit.level_2_;
	}

using manipulator :: endLine;

	template<class T_1, class T_2>
	inline void
	Unit<T_1, T_2> :: show (String& string) const
	{
		string << "source node: " << endLine;
		Pair_ :: getFirst().show (string);
		string << endLine;

		string << "target node: " << endLine;
		Pair_ :: getSecond().show (string);
		string << endLine;
	}

	template<class T_1, class T_2>
	inline void
	Unit<T_1, T_2> :: show () const
	{
		String string (1000);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T_1, class T_2>
	String&
	operator << (String& string, const Unit<T_1, T_2>& unit)
	{
		unit.show (string);
		return string;
	}
}
}
}



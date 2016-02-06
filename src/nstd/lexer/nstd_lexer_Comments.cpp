/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Comments.cpp                                  */
/* Description:     container for comments                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Comments<A> :: Comments() :
	vector_ (INITIAL_VECTOR_CAPACITY)
	{
		for (Index_ i = 0; i < INITIAL_VECTOR_CAPACITY; ++ i) {
			vector_.add (new Comment_ (INITIAL_COMMENT_CAPACITY));
		}
		vector_.clear();
	}
	template<class A>
	Comments<A> :: ~ Comments() {
	}

	template<class A>
	inline typename Comments<A> :: Comment_*
	Comments<A> :: push()
	{
		Comment_* comment = vector_.push();
		comment->clear();
		return comment;
	}
	template<class A>
	inline const typename Comments<A> :: Comment_*
	Comments<A> :: get (const Index_ i) const {
		return vector_.getValue (i);
	}
	template<class A>
	inline void
	Comments<A> :: clear()
	{
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			vector_ [i]->clear();
		}
		vector_.clear();
	}
	template<class A>
	inline typename Comments<A> :: Index_
	Comments<A> :: getSize() const {
		return vector_.getSize();
	}
	template<class A>
	inline bool
	Comments<A> :: isEmpty() const {
		return vector_.isEmpty();
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// nstd :: Object implementation
	template<class A>
	void
	Comments<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Comments<A> :: getVolume() const {
		return vector_.getVolume();
	}
	template<class A>
	Size_t
	Comments<A> :: getSizeOf() const {
		return sizeof (Comments);
	}
	template<class A>
	void
	Comments<A> :: show (String<>& string) const
	{
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			string << "comment: "<< i << endLine;
			string << *vector_.getValue (i);
		}
	}
}
}



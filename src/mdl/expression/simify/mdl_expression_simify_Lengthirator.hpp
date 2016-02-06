/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Lengthirator.hpp                   */
/* Description:     length measuring iterator                                */
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

template<class T>
class Lengthirator : public T :: const_Iterator_ {
public :
	typedef T Term_;
	typedef
		typename Term_ :: const_Iterator_
		Iterator_;

	Lengthirator (const Iterator_&);
	Lengthirator (const Lengthirator&);

	void operator ++ ();
	void operator -- ();
	void operator += (const Term_* const);

	value :: Integer getLength() const;

private :
	value :: Integer length_;
};

}
}
}



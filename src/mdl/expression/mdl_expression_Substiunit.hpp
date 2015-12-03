/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Substiunit.hpp                            */
/* Description:     substitution unit class                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SUBSTIUNIT_HPP_
#define MDL_EXPRESSION_SUBSTIUNIT_HPP_

#include "mdl/expression/mdl_expression_Symbol.hpp"

namespace mdl {
namespace expression {

template<class T>
class Substiunit {
public :
	typedef T Term_;
	typedef
		typename Term_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Term_ :: Iterator_
		Iterator_;

	Substiunit();
	Substiunit (const Symbol&, const Term_*, const bool = false);
	~ Substiunit();

	void inverse();

	bool isUndefined() const;
	bool isTrivial() const;
	bool isGoodMgu() const;

	bool isEqualLiteraly (const Substiunit&) const;
	bool operator == (const Substiunit&) const;
	bool operator != (const Substiunit&) const;
	void operator = (const Substiunit&);
	bool isEqual (const Substiunit&) const;

	value :: Integer getLength() const;
	const Symbol& getVariable() const;
	const Term_* getTerm() const;

	void verifyIntegrity() const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	template<class>
	friend class Substitution;

	Substiunit (const Substiunit&);

	Symbol variable_;
	mutable const Term_* term_;
	bool ownsTerm_;
};

	template<class T>
	String&
	operator << (String&, const Substiunit<T>&);
	template<class T>
	std :: ostream&
	operator << (std :: ostream&, const Substiunit<T>&);
}
}


#endif /*MDL_EXPRESSION_SUBSTIUNIT_HPP_*/

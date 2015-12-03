/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Disjointed.hpp                           */
/* Description:     disjointed variable restriction                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_DISJOINTED_HPP_
#define MDL_FORM_HEADER_DISJOINTED_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace header {

class Disjointed :
	public mdl :: header :: Disjointed,
	public Scalar<Disjointed> {
public :
	Disjointed
	(
		const vector :: value :: Literal&,
		mdl :: Theory*
	);
	Disjointed
	(
		value :: Literal,
		value :: Literal,
		mdl :: Theory*
	);
	virtual ~ Disjointed();

	// mdl :: header :: Disjointed interface
	virtual bool noRestriction() const;
	virtual void check
	(
		const array :: Substitution*,
		const mdl :: Assertion*
	) const;
	virtual bool check
	(
		const list :: Substitution*,
		const mdl :: Assertion*
	) const;
	virtual bool contains (const value :: Literal) const;

	virtual bool isMoreRestrictive (const mdl :: header :: Disjointed*) const;
	virtual bool isLessRestrictive (const mdl :: header :: Disjointed*) const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	// verification routines
	void checkPair
	(
		const array :: Substitution*,
		const mdl :: Assertion*,
		const value :: Literal,
		const value :: Literal
	) const;
	void checkTerms
	(
		const array :: Term*,
		const array :: Term*,
		const mdl :: Assertion*
	) const;
	void checkSymbols
	(
		const Symbol&,
		const Symbol&,
		const array :: Term*,
		const array :: Term*,
		const mdl :: Assertion*
	) const;

	// prover routines
	bool checkPair
	(
		const list :: Substitution*,
		const mdl :: Assertion*,
		const value :: Literal,
		const value :: Literal
	) const;
	template<class T>
	bool checkTerms
	(
		const mdl :: Assertion*,
		const T* const,
		const T* const
	) const;
	bool checkSymbols
	(
		const mdl :: Assertion*,
		const Symbol&,
		const Symbol&
	) const;

	vector :: value :: Literal literalVector_;
};

}
}
}

#endif /*MDL_FORM_HEADER_DISJOINTED_HPP_*/

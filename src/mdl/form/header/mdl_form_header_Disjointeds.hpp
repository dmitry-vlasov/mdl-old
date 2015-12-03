/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Disjointeds.hpp                          */
/* Description:     disjointed variables restrictions                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_DISJOINTEDS_HPP_
#define MDL_FORM_HEADER_DISJOINTEDS_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace header {

class Disjointeds :
	public mdl :: Disjointeds,
	public Scalar<Disjointeds> {
public :
	Disjointeds();
	Disjointeds
	(
		const vector :: parser :: Disjointed&,
		mdl :: Theory*
	);
	virtual ~ Disjointeds();

	// mdl :: Disjointeds interface
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
	virtual bool check (const Symbol&, const Symbol&) const;

	virtual bool isMoreRestrictive (const mdl :: Disjointeds*) const;
	virtual bool isLessRestrictive (const mdl :: Disjointeds*) const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	bool newPair (const value :: Literal, const value :: Literal) const;
	bool isLessRestrictive (const mdl :: header :: Disjointed*, const mdl :: Disjointeds*) const;

	vector :: header :: Disjointed disjointedVector_;
	bool hardcoded_;
};

}
}
}

#endif /*MDL_FORM_HEADER_DISJOINTEDS_HPP_*/

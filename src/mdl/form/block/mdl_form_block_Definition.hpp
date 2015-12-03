/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Definition.hpp                            */
/* Description:     definition class                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_DEFINITION_HPP_
#define MDL_FORM_BLOCK_DEFINITION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"

namespace mdl {
namespace form {
namespace block {

class Definition :
	public mdl :: Definition,
	virtual public form :: block :: Assertion
	<
		mdl :: Hypothesis,
		mdl :: statement :: Definition
	>,
	public Scalar<Definition> {
public :
	Definition
	(
		const Location&,
		const mdl :: Comments*,
		lexer :: Indent,
		value :: Name,
		mdl :: Variables*,
		mdl :: Disjointeds*,
		mdl :: term :: Definition*,
		mdl :: term :: Definition*,
		const vector :: parser :: Hypothesis&,
		const vector :: parser :: Definition&,
		mdl :: Theory*
	);
	virtual ~ Definition();

	// mdl :: Definition interface
	virtual mdl :: term :: Definition* getDefiendum();
	virtual mdl :: term :: Definition* getDefiniens();
	virtual const mdl :: term :: Definition* getDefiendum() const;
	virtual const mdl :: term :: Definition* getDefiniens() const;

	// mdl :: Assertion interface
	virtual mdl :: Assertion :: Kind getKind() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	//virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		form :: block :: Assertion
		<
			mdl :: Hypothesis,
			mdl :: statement :: Definition
		>
		Ancestor_;

	mdl :: term :: Definition* defiendum_;
	mdl :: term :: Definition* definiens_;
};

}
}
}

#endif /*MDL_FORM_BLOCK_DEFINITION_HPP_*/

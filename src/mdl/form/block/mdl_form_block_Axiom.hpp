/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Axiom.hpp                                 */
/* Description:     axiom class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"
#include "mdl/form/block/mdl_form_block_Assertion.hpp"

namespace mdl {
namespace form {
namespace block {

class Axiom :
	virtual public form :: block :: Assertion
	<
		mdl :: Hypothesis,
		mdl :: statement :: Axiomatic
	>,
	public Scalar<Axiom> {
public :
	Axiom
	(
		const Location&,
		const mdl :: Comments*,
		lexer :: Indent,
		value :: Name,
		mdl :: Variables*,
		mdl :: Disjointeds*,
		const vector :: parser :: Hypothesis&,
		const vector :: parser :: Axiomatic&,
		mdl :: Theory*
	);
	virtual ~ Axiom();

	// mdl :: Assertion interface
	virtual mdl :: Assertion :: Kind getKind() const;

	// object :: Verifiable interface
	/*virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;*/

	// object :: Buildable interface
	//virtual void build();

	// object :: Writable interface
	virtual void replicate (String& string) const;

	// object :: Object interface
	virtual void commitSuicide();

private :
	typedef
		form :: block :: Assertion
		<
			mdl :: Hypothesis,
			mdl :: statement :: Axiomatic
		>
		Ancestor_;
};

}
}
}



/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Rule.hpp                            */
/* Description:     syntax rule term class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/mdl_form_header_Line.hpp"

namespace mdl {
namespace form {
namespace header {
namespace term {

class Rule :
	public mdl :: term :: Rule,
	public Line,
	public Line :: Counter,
	public Scalar<Rule> {
public :
	Rule
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Rule();

	// mdl :: term :: Rule interface
	virtual void setRule (mdl :: Rule*);
	virtual index :: Assertion getTargetIndex() const;

	// object :: Expressive interface
	//virtual mdl :: Type* getType();
	//virtual array :: Expression* getExpression();
	//virtual const mdl :: Type* getType() const;
	//virtual const array :: Expression* getExpression() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	void checkSemantics() const;
	void checkVariable (const index :: Literal) const;

	mdl :: Rule* rule_;
};

}
}
}
}



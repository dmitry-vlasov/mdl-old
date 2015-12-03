/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Definition.hpp                      */
/* Description:     definition term class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_DEFINITION_HPP_
#define MDL_FORM_HEADER_TERM_DEFINITION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/mdl_form_header_Line.hpp"

namespace mdl {
namespace form {
namespace header {
namespace term {

class Definition :
	public mdl :: term :: Definition,
	public Line {
public :
	Definition
	(
		const Location&,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Definition();

	// term :: Definition interface
	virtual void setDefinition (mdl :: Definition*);

	// object :: Expressive interface
	virtual mdl :: Type* getType();
	virtual array :: Expression* getExpression();
	virtual const mdl :: Type* getType() const;
	virtual const array :: Expression* getExpression() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	mdl :: Definition* definition_;
};

}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_DEFINITION_HPP_*/

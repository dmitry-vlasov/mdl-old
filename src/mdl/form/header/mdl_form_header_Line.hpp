/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Line.hpp                                 */
/* Description:     header line                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace header {

class Line : virtual public mdl :: header :: Line {
public :
	Line
	(
		const Location&,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Line();

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
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

	const Location& getLocation() const;

	class Counter {
	public :
		void setIndex() const;
		index :: Assertion getIndex() const;
	protected :
		Counter ();
		const index :: Assertion index_;
	private :
		static index :: Assertion counter_;
	};

protected :
	const Location location_;
	mdl :: Identificator* identificator_;
	mdl :: Type* type_;
	array :: Expression* expression_;
};

}
}
}



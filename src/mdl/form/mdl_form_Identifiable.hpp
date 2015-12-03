/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Identifiable.hpp                                */
/* Description:     base class for identifiable objects                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_IDENTIFIABLE_HPP_
#define MDL_FORM_IDENTIFIABLE_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {

class Identifiable :
	virtual public object :: Identifiable {
public :
	Identifiable ();
	Identifiable
	(
		const value :: Name,
		mdl :: Theory*,
		bool unique = true
	);
	Identifiable
	(
		const Location&,
		const mdl :: Comments*,
		const value :: Name,
		mdl :: Theory*
	);
	virtual ~ Identifiable();

	const mdl :: Comments* getComments() const;
	value :: Integer getDepth() const;

	// object :: Identifiable interface
	virtual const Location& getLocation() const;
	virtual value :: Name getName() const;

	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	virtual mdl :: Theory* getTheory();
	virtual mdl :: Identificator* getIdentificator();
	virtual const mdl :: Theory* getTheory() const;
	virtual const mdl :: Identificator* getIdentificator() const;

	// object :: Verifiable interface
	virtual void mine (String&) const;

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
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

protected :
	const Location location_;
	const mdl :: Comments* comments_;
	value :: Name name_;
	mdl :: Identificator* identificator_;
	mdl :: Theory* theory_;
};

}
}

#endif /*MDL_FORM_IDENTIFIABLE_HPP_*/

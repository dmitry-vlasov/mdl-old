/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Theory.hpp                                      */
/* Description:     theory class                                             */
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

namespace mdl {
namespace form {

class Theory :
	public mdl :: Theory,
	public Identifiable,
	public Scalar<Theory> {
public :
	Theory ();
	Theory
	(
		const Location&,
		const mdl :: Comments*,
		const value :: Name,
		mdl :: Theory*
	);
	virtual ~ Theory();

	// mdl :: Theory interface
	virtual void checkUnused (const value :: Name) const;
	virtual index :: Form checkUsed (const mdl :: Identificator*) const;
	virtual void addComponent (object :: Verifiable*);
	virtual void addName (const index :: Form, const value :: Name);

	virtual index :: Form getIndex (const mdl :: Identificator*) const;
	virtual index :: Form getIndexUp (const mdl :: Identificator*) const;
	virtual index :: Form getIndexDown (const mdl :: Identificator*) const;

	virtual mdl :: Identificator* getPath();
	virtual const mdl :: Identificator* getPath() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Verifiable interface
	virtual void mine (String&) const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	bool isRoot() const;

	enum {
		INITIAL_FORM_MAP_CAPACITY = 512
	};

	typedef
		map :: Scalar
		<
			value :: Name,
			index :: Form,
			allocator :: Heap
		>
		FormMap;

	mdl :: Identificator* path_;
	FormMap formMap_;

	typedef
		vector :: Vector
		<
			object :: Verifiable*,
			storage :: ByValue,
			allocator :: Heap
		>
		Components_;

	enum {
		INITIAL_COMPONENTS_CAPACITY = 32
	};

	Components_ components_;
};

}
}



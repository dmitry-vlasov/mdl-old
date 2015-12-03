/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Import.hpp                                      */
/* Description:     import class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_IMPORT_HPP_
#define MDL_FORM_IMPORT_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {

class Import :
	public mdl :: Import,
	public Scalar<Import> {
public :
	Import (const Location&, mdl :: Identificator*);
	virtual ~ Import();

	// mdl :: Import interface
	virtual Path* getPath();
	virtual const Path* getPath() const;

	// object :: Verifiable interface
	virtual bool isVerified() const;
	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual void mine (String&) const;

	// object :: Buildable interface
	virtual void build();

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
	Location location_;
	mdl :: Identificator* pathComponents_;
	Path sourcePath_;
	Path targetPath_;
};

}
}

#endif /*MDL_FORM_IMPORT_HPP_*/

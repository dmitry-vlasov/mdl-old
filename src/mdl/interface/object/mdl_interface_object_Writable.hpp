/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Writable.hpp                        */
/* Description:     abstract interface for writable objects                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/auxiliary/mdl_auxiliary.dpp"

namespace mdl {
namespace interface {
namespace object {

class Writable : virtual public Object {
public :
	virtual void translate (String&) const { };
	virtual void replicate (String&) const { };

	virtual void show (String&) const;
	virtual void write (Output&) const;
	virtual void write() const;

	// Lookup an object, located by
	// --line, --column options.
	virtual bool lookup() const;

	// Find an object, located by
	// --line, --column options.
	virtual Writable* find();
	virtual const Writable* find() const;
};

}
}
}



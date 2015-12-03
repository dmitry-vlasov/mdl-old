/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_object_Object.hpp                          */
/* Description:     abstract interface for general smm object                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_INTERFACE_OBJECT_OBJECT_HPP_
#define SMM_INTERFACE_OBJECT_OBJECT_HPP_

#include "smm/interface/smm_interface.dpp"
#include "smm/types/smm_types.hpp"

namespace smm {
namespace interface {
namespace object {

class Object : virtual public nstd :: Object {
public :
	virtual void show (String&) const = 0;

	static void release();
	static Size_t getStringVolume();

	// nstd :: Object interface
	virtual Size_t getVolume() const = 0;
	virtual Size_t getSizeOf() const = 0;
	virtual void show (nstd :: String<>&) const;

private :
	friend std :: ostream&
	operator << (std :: ostream&,  const Object&);
	static String* string_;
};

	String&
	operator << (String&,  const Object&);
	std :: ostream&
	operator << (std :: ostream&,  const Object&);
}
}
}

#endif /*SMM_INTERFACE_OBJECT_OBJECT_HPP_*/

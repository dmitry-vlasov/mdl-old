/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Object.hpp                          */
/* Description:     abstract interface for objects                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_OBJECT_HPP_
#define MDL_INTERFACE_OBJECT_OBJECT_HPP_

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/auxiliary/mdl_auxiliary.dpp"

namespace mdl {
namespace interface {
namespace object {

class Object : virtual public nstd :: Object {
public :
	void dump() const;
	static void release();
	static Size_t getStringVolume();

	// nstd :: Object interface
	virtual Size_t getVolume() const = 0;
	virtual Size_t getSizeOf() const = 0;
#ifndef USE_STANDARD_HEAP
	virtual void show (String&) const = 0;
	virtual void show (nstd :: String<>&) const;
	virtual void show (std :: ostream&) const;
#endif

protected :
	friend std :: ostream&
	operator << (std :: ostream&,  const Object&);
#ifndef USE_STANDARD_HEAP
	static String* string_;
#endif
};
	String&
	operator << (String&,  const Object&);
	std :: ostream&
	operator << (std :: ostream&,  const Object&);
}
}
}

#endif /*MDL_INTERFACE_OBJECT_OBJECT_HPP_*/

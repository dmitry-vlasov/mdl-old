/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_object_Object.hpp                          */
/* Description:     abstract interface for objects                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_OBJECT_HPP_
#define DEL_INTERFACE_OBJECT_HPP_

#include "del/interface/del_interface.dpp"
#include "del/auxiliary/del_auxiliary.dpp"

namespace del {
namespace interface {

class Object : public nstd :: Object {
public :
	virtual void show (String&) const = 0;

	static void init();
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

#endif /*DEL_INTERFACE_OBJECT_HPP_*/

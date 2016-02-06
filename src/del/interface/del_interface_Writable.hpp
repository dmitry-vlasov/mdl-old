/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_object_Writable.hpp                        */
/* Description:     abstract interface for writable objects                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/auxiliary/del_auxiliary.dpp"

namespace del {
namespace interface {

class Writable : virtual public Object {
public :
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;

	virtual void show (String&) const;
	virtual void write (Output&) const;
	virtual void write (String&) const;
	virtual void write() const;
};

}
}



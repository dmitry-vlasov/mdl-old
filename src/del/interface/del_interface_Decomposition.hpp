/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Decomposition.hpp                          */
/* Description:     abstract interface for answer class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Decomposition : virtual public Writable {
public :
	virtual bool verify() const = 0;
	virtual void addComponent (const value :: Symbol) = 0;
	virtual bool isEqual (const Decomposition*) const = 0;
	virtual value :: Integer getSize() const = 0;
	virtual value :: Symbol getComponent (const value :: Integer) const = 0;
	virtual void replicateCompletely (String&) const = 0;
};

}
}



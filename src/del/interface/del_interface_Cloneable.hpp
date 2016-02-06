/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_object_Cloneable.hpp                       */
/* Description:     abstract interface for cloneable objects                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.dpp"

namespace del {
namespace interface {

template<class T>
class Cloneable {
public :
	virtual T* clone() const = 0;
};

}
}



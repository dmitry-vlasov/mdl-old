/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Expansion.hpp                              */
/* Description:     abstract interfaces for del signature                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_EXPANSION_HPP_
#define MDL_INTERFACE_EXPANSION_HPP_

#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Expansion :
	public Object,
	public Cloneable<Expansion> {
public :
	virtual void clear() = 0;
	virtual Symbol addPostfixToSymbol (const Symbol&) const = 0;
};

}
}

#endif /*MDL_INTERFACE_EXPANSION_HPP_*/

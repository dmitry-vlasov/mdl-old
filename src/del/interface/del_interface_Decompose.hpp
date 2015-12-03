/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Decompose.hpp                              */
/* Description:     abstract interface for identificators                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_DECOMPOSE_HPP_
#define MDL_INTERFACE_DECOMPOSE_HPP_

#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Decompose : virtual public Writable {
public :
	virtual const Theory* getMinimalTheory() const = 0;
	virtual const Theory* getNormalTheory() const = 0;
	virtual const Theory* getPrimitiveTheory() const = 0;
	virtual const Theory* getDecomposedTheory() const = 0;
	virtual const Theory* getAssembledTheory() const = 0;

	virtual const Expansion* getDeltaExpansion() const = 0;
	virtual const Theory* getDeltaTheory() const = 0;
	virtual const Model* getDeltaModel() const = 0;
	virtual const Decomposition* decompose() const = 0;
};

}
}

#endif /*MDL_INTERFACE_DECOMPOSE_HPP_*/

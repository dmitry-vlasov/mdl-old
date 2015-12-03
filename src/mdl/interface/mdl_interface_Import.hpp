/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Import.hpp                                 */
/* Description:     abstract interface for import class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_IMPORT_HPP_
#define MDL_INTERFACE_IMPORT_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {

class Import : virtual public object :: Verifiable {
public :
	virtual Path* getPath() = 0;
	virtual const Path* getPath() const = 0;
};

}
}

#endif /*MDL_INTERFACE_IMPORT_HPP_*/

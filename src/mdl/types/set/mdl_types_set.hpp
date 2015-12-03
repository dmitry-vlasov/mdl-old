/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_set.hpp                                        */
/* Description:     basic set types                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_SET_HPP_
#define MDL_TYPES_SET_HPP_

#include "mdl/types/storage/mdl_types_storage.hpp"
#include "mdl/types/value/mdl_types_value.hpp"

namespace mdl {
namespace set {

	using nstd :: container :: Set;
}
}

#include "mdl/types/set/index/mdl_types_set_index.hpp"
#include "mdl/types/set/value/mdl_types_set_value.hpp"

#endif /*MDL_TYPES_SET_HPP_*/


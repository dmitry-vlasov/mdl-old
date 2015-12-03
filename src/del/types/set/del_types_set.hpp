/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_set.hpp                                        */
/* Description:     basic set types                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_SET_HPP_
#define DEL_TYPES_SET_HPP_

#include "types/storage/del_types_storage.hpp"
#include "types/value/del_types_value.hpp"

namespace del {
namespace set {

	using nstd :: container :: Set;
}
}

#include "types/set/index/del_types_set_index.hpp"
#include "types/set/value/del_types_set_value.hpp"

#endif /*DEL_TYPES_SET_HPP_*/


/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Selector.hpp                                   */
/* Description:     type selector metafunction                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_SELECTOR_HPP_
#define NSTD_TYPE_SELECTOR_HPP_

#include "type/nstd_type.dpp"

namespace nstd {
namespace type {

template<class X, class Y>
class Selector<true, X, Y> {
public :
	typedef X Result_;
};

template<class X, class Y>
class Selector<false, X, Y> {
public :
	typedef Y Result_;
};

}
}

#endif /*NSTD_TYPE_SELECTOR_HPP_*/
